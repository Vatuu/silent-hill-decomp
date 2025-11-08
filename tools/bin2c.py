#!/usr/bin/env python3
"""
bin2c: Decompiles binary data into C struct initializers.
Parses C struct definitions from .h / ctx.c file and generates initializers from raw bytes.

Usage:
 - tools/m2ctx.py src/maps/...
 - tools/bin2c.py -s ctx.c -b assets/VIN/MAP0_S00.BIN -o 0x4 -t s_MapOverlayHeader --use-cpp
 - That will parse structs from ctx.c, read from assets/VIN/MAP0_S00.BIN, and emit an initializer for s_MapOverlayHeader based on the data at offset 0x4
"""

# TODO:
# - build_struct_internal still uses Int32 as pointer (and default for unknown data), ignoring pointer_size
# - inner-structs might have issues with `self.struct_field_types`?
# - make Q conversion an option (right now it's always enabled for qX_X types)
# - multi-dimension arrays aren't emitted properly

import sys
import argparse
import re
import math
from io import StringIO
from pycparser import c_parser, c_ast, parse_file
from construct import *

# ---------- FP converter ----------
def to_signed(val, bits=32):
    """Convert unsigned int to signed (two's complement)."""
    if val & (1 << (bits - 1)):
        val -= 1 << bits
    return val

def process_fp(val, qval = 12):
    scale = (1 << qval)

    float_val = val / scale;

    # Try to find the shortest rounded representation that still matches
    for digits in range(1, 12):  # up to 12 decimal places
        rounded = round(float_val, digits)
        if float_val < 0:
            reconverted = int(math.ceil(rounded * scale))
        else:
            reconverted = int(math.floor(rounded * scale))
        if reconverted == val:
            # Good enough – this rounded value still maps to the same fixed integer
            float_val = rounded
            break

    return f"Q{qval}({float_val}f)"

class StructParser:
    def __init__(self, alignment=4, verbose=False, union_choices=None):
        self.parser = c_parser.CParser()
        self.structs = {}  # name -> construct format
        self.struct_asts = {}  # name -> AST for reference
        self.union_asts = {}  # name -> union AST
        self.type_aliases = {}  # typedef aliases: q11_4 -> s16, etc.
        self.alignment = alignment  # Default alignment (4 bytes for PSX/32-bit)
        self.verbose = verbose  # Debug output
        self.union_choices = union_choices or {}  # Dict: "StructName.unionField" -> "memberName"
        self.enum_values = {}
        self.struct_sizes = {}  # name -> size in bytes
        self.union_sizes = {}   # union name -> size in bytes
        self.struct_field_types = {} # e.g. {'MyStruct': {'field_a': 'u32', 'field_b': 'pointer'}}
        self.union_members = {}  # union name -> dict of member name -> (construct, field_types)
        self.pointer_size = 4   # 32-bit pointers (PSX)
        self.sym_addrs = {} # sym.txt address -> name mappings
        self.unnamed_values = False
        self.numbers_hex = False
        self.single_line_values = False
        
        # Basic type mappings to construct
        self.type_map = {
            'u8': Int8ul,
            'u16': Int16ul,
            'u32': Int32ul,
            'u64': Int64ul,
            's8': Int8sl,
            's16': Int16sl,
            's32': Int32sl,
            's64': Int64sl,
            'uint8_t': Int8ul,
            'uint16_t': Int16ul,
            'uint32_t': Int32ul,
            'uint64_t': Int64ul,
            'int8_t': Int8sl,
            'int16_t': Int16sl,
            'int32_t': Int32sl,
            'int64_t': Int64sl,
            'char': Int8sl,
            'unsigned char': Int8ul,
            'signed char': Int8sl,
            'short': Int16sl,
            'signed short': Int16sl,
            'unsigned short': Int16ul,
            'int': Int32sl,
            'signed int': Int32sl,
            'unsigned int': Int32ul,
            'long': Int32sl,
            'signed long': Int32sl,
            'unsigned long': Int32ul,
            'long long': Int64sl,
            'signed long long': Int64sl,
            'unsigned long long': Int64ul,
        }
        
        # Size of each type in bytes
        self.type_sizes = {
            'u8': 1, 'u16': 2, 'u32': 4, 'u64': 8,
            's8': 1, 's16': 2, 's32': 4, 's64': 8,
            'uint8_t': 1, 'uint16_t': 2, 'uint32_t': 4, 'uint64_t': 8,
            'int8_t': 1, 'int16_t': 2, 'int32_t': 4, 'int64_t': 8,
            'char': 1, 
            'unsigned char': 1,
            'signed char': 1,
            'short': 2,
            'signed short': 2,
            'unsigned short': 2,
            'int': 4,
            'signed int': 4,
            'unsigned int': 4,
            'long': 4,
            'signed long': 4,
            'unsigned long': 4,
            'long long': 8,
            'signed long long': 8,
            'unsigned long long': 8,
            'void': 0,  # void has no size, but void* is a pointer
        }
        # Used to determine if a bitfield base type is signed
        self.signed_types_set = {
            's8', 's16', 's32', 's64',
            'int8_t', 'int16_t', 'int32_t', 'int64_t',
            'char', 'signed char',
            'short', 'signed short',
            'int', 'signed int',
            'long', 'signed long',
            'long long', 'signed long long',
        }
    
    def resolve_type(self, type_info):
        """Resolve type aliases to their base types."""
        if type_info in self.type_aliases:
            return self.resolve_type(self.type_aliases[type_info])
        return type_info
    
    def get_type_size(self, type_info):
        """Get the size of a type in bytes."""
        # Resolve aliases first
        type_info = self.resolve_type(type_info)
        
        if type_info == 'pointer':
            return self.pointer_size
        elif isinstance(type_info, tuple) and type_info[0] == 'array':
            _, base_type, count = type_info
            return self.get_type_size(base_type) * count
        elif isinstance(type_info, tuple) and type_info[0] == 'union':
            _, union_name = type_info
            return self.union_sizes.get(union_name, 4)  # Default to 4 if unknown
        elif type_info in self.type_sizes:
            return self.type_sizes[type_info]
        elif type_info in self.struct_sizes:
            return self.struct_sizes[type_info]
        else:
            # Unknown type - assume it's a pointer to an opaque/incomplete type
            return self.pointer_size
    
    def get_type_alignment(self, type_info):
        """Get the alignment requirement of a type."""
        # Resolve aliases first
        type_info = self.resolve_type(type_info)
        
        if type_info == 'pointer':
            return self.pointer_size
        elif isinstance(type_info, tuple) and type_info[0] == 'array':
            _, base_type, _ = type_info
            return self.get_type_alignment(base_type)
        elif isinstance(type_info, tuple) and type_info[0] == 'union':
            # Unions align to their largest member's alignment (typically 4 bytes)
            return self.alignment
        elif type_info in self.type_sizes:
            # Basic types align to their size (but max at alignment)
            return min(self.type_sizes[type_info], self.alignment)
        elif type_info in self.struct_sizes:
            # Structs align to alignment boundary
            return self.alignment
        else:
            # Unknown type - assume pointer alignment
            return self.pointer_size
    
    def calculate_padding(self, current_offset, next_alignment):
        """Calculate padding needed to align to next_alignment."""
        if next_alignment == 0:
            return 0
        remainder = current_offset % next_alignment
        if remainder == 0:
            return 0
        return next_alignment - remainder
    
    def parse_type(self, type_node, check_bitfield=False):
        """Extract type name from AST node."""
        if isinstance(type_node, c_ast.TypeDecl):
            return self.parse_type(type_node.type, check_bitfield)
        elif isinstance(type_node, c_ast.PtrDecl):
            # Pointer to any type - treat as u32 (4 bytes on PSX)
            return 'pointer'
        elif isinstance(type_node, c_ast.FuncDecl):
            # Function pointer - treat as u32 (4 bytes)
            return 'pointer'
        elif isinstance(type_node, c_ast.IdentifierType):
            return ' '.join(type_node.names)
        elif isinstance(type_node, c_ast.Struct):
            return type_node.name
        elif isinstance(type_node, c_ast.Union):
            # Return tuple to indicate this is a union
            return ('union', type_node.name)
        elif isinstance(type_node, c_ast.ArrayDecl):
            # Handle multi-dimensional arrays
            base_type = self.parse_type(type_node.type)
            size = self.eval_array_size(type_node.dim)
            
            # If base is already an array, this is multi-dimensional
            if isinstance(base_type, tuple) and base_type[0] == 'array':
                _, inner_type, inner_size = base_type
                # Flatten to single array with total element count
                return ('array', inner_type, size * inner_size)
            else:
                return ('array', base_type, size)
        return None

    def build_union(self, union_name, union_decl):
        """Build all possible interpretations of a union."""
        if self.verbose:
            print(f"\n=== Building union {union_name} ===", file=sys.stderr)
        
        union_members = {}
        max_size = 0
        
        # Build each union member as a separate struct
        for member_decl in union_decl.decls:
            member_name = member_decl.name
            
            if self.verbose:
                print(f"  Union member: {member_name}", file=sys.stderr)
            
            # Check if this member is an anonymous struct
            member_type = self.parse_type(member_decl.type)
            
            # Resolve the type first to handle typedefs
            resolved_type = self.resolve_type(member_type)
            
            if isinstance(member_decl.type, c_ast.TypeDecl) and isinstance(member_decl.type.type, c_ast.Struct):
                # Anonymous struct within union
                anon_struct = member_decl.type.type
                member_construct, member_field_types = self.build_struct_internal(f"{union_name}.{member_name}", anon_struct)
                member_size = member_construct.sizeof()
            elif resolved_type in self.type_map:
                # Simple type member (including typedefs that resolve to basic types)
                # Note: member_name is used as the field name in the construct definition
                member_construct = Struct("_union_value" / self.type_map[resolved_type])
                member_field_types = {"_union_value": member_type}  # Store original type, not resolved
                member_size = self.type_sizes[resolved_type]
            else:
                # Unknown/complex type - store as raw bytes based on alignment
                # For safety, let's try to calculate size if it's a known struct/type
                member_size = self.get_type_size(member_type)
                if member_size == self.pointer_size and member_type not in self.struct_sizes:
                     # Default to pointer size if type is not recognized/incomplete
                    member_size = self.pointer_size
                
                member_construct = Struct(member_name / Bytes(member_size))
                member_field_types = {member_name: member_type}
            
            union_members[member_name] = (member_construct, member_field_types)
            max_size = max(max_size, member_size)
            
            if self.verbose:
                print(f"    Size: {member_size} bytes", file=sys.stderr)
        
        self.union_members[union_name] = union_members
        self.union_sizes[union_name] = max_size
        
        if self.verbose:
            print(f"  Total union size: {max_size} bytes\n", file=sys.stderr)
        
        # Return a construct that reads the union as raw bytes
        # We'll interpret it later based on union_choices
        return Bytes(max_size)

    def decode_bitfields(self, data_bytes, bitfield_info):
        """Manually decode C-style bitfields from raw bytes (LSB-first packing)"""
        # Convert bytes to integer (little-endian)
        value = int.from_bytes(data_bytes, byteorder='little')
        
        results = {}
        bit_pos = 0
        
        for bf_name, bf_bits, is_signed, bf_type in bitfield_info:
            # Extract bits from LSB side
            mask = (1 << bf_bits) - 1
            field_value = (value >> bit_pos) & mask
            
            # Handle signed values
            if is_signed and (field_value & (1 << (bf_bits - 1))):
                field_value -= (1 << bf_bits)
            
            results[bf_name] = field_value
            bit_pos += bf_bits
        
        return results

    def build_struct_internal(self, struct_name, struct_decl):
        """Internal struct builder that returns both construct and field types."""
        fields = []
        offset = 0
        field_types = {}

        if self.verbose:
            print(f"\n=== Building struct {struct_name} (alignment={self.alignment}) ===", file=sys.stderr)
        
        # Track bitfields for packing
        bitfield_buffer = []  # List of (name, bitsize, type_info)
        bitfield_bit_offset = 0    # Total bits accumulated in the current byte group
        
        for i, decl in enumerate(struct_decl.decls):
            field_name = decl.name
            type_info = self.parse_type(decl.type)

            # Store the resolved type info for this field (using the C name, not the internal Construct name)
            # Anonymous structs inside unions will have their fields stored under their internal union/member name
            field_types[field_name] = type_info

            # Check if this is an inline/anonymous union
            if isinstance(type_info, tuple) and type_info[0] == 'union':
                _, union_name = type_info
                
                if union_name is None:
                    # Anonymous union - build it inline
                    # Get the c_ast.Union node
                    union_decl = decl.type.type if isinstance(decl.type, c_ast.TypeDecl) else decl.type
                    # Create an internal, unique name for the anonymous union
                    union_name = f"{struct_name}_{field_name}_union" 
                    
                    # Build and store the union members. build_union returns the Bytes(max_size) construct
                    union_construct = self.build_union(union_name, union_decl) 
                    
                    # Update the field type to the new internal name for later lookup
                    field_types[field_name] = ('union', union_name)
                else:
                    # Named union reference
                    if union_name not in self.union_members:
                        # Attempt to build it if it hasn't been built yet (e.g., forward-declared)
                        if union_name in self.union_asts:
                            self.build_union(union_name, self.union_asts[union_name])
                        else:
                            # If still not found, throw error
                            raise ValueError(f"Union '{union_name}' not defined before use")
                            
                    # Get the raw bytes construct for the union's max size
                    union_construct = Bytes(self.union_sizes[union_name])
                
                # Add padding before union
                field_alignment = self.get_type_alignment(field_types[field_name])
                padding_needed = self.calculate_padding(offset, field_alignment)
                if padding_needed > 0:
                    if self.verbose:
                        print(f"  Adding padding: {padding_needed} bytes", file=sys.stderr)
                    fields.append(f"_pad_{offset}" / Padding(padding_needed))
                    offset += padding_needed
                
                # Add union as raw bytes
                union_size = self.union_sizes[union_name]
                if self.verbose:
                    print(f"\nField: {field_name} (union {union_name}, {union_size} bytes)", file=sys.stderr)
                # Use a specific prefix for unions so we can identify them later in to_initializer
                fields.append(f"_union_{field_name}" / union_construct) 
                offset += union_size
                continue

            # Check for bitfield flush condition
            bitwidth = decl.bitsize.value if decl.bitsize else None

            is_last_field = (i == len(struct_decl.decls) - 1)
            is_normal_field = bitwidth is None
            
            if bitfield_buffer and (is_normal_field or is_last_field):
                # Flush bitfields
                num_bytes = (bitfield_bit_offset + 7) // 8
                
                if self.verbose:
                    print(f"\n  --- Flushing Bitfield Group ({bitfield_bit_offset} bits) ---", file=sys.stderr)
                
                field_alignment = min(num_bytes, self.alignment)
                padding_needed = self.calculate_padding(offset, field_alignment)
                if padding_needed > 0:
                    if self.verbose:
                        print(f"  Adding padding: {padding_needed} bytes", file=sys.stderr)
                    fields.append(f"_pad_{offset}" / Padding(padding_needed))
                    offset += padding_needed
                
                # Read as raw bytes first, then manually extract bitfields
                # Store the bitfield info for later extraction
                bitfield_info = []
                for bf_name, bf_bits, bf_type in bitfield_buffer:
                    resolved_type = self.resolve_type(bf_type)
                    is_signed = resolved_type in self.signed_types_set
                    bitfield_info.append((bf_name, bf_bits, is_signed, bf_type))
                    
                    if self.verbose:
                        print(f"  Bitfield: {bf_name} ({bf_bits} bits, signed: {is_signed})", file=sys.stderr)
                
                # Store bitfield group as raw bytes - we'll decode manually
                fields.append(f"_bitfields_{offset}" / Bytes(num_bytes))
                
                # Store metadata for manual decoding
                if not hasattr(self, 'bitfield_metadata'):
                    self.bitfield_metadata = {}
                self.bitfield_metadata[f"{struct_name}._bitfields_{offset}"] = bitfield_info
                
                offset += num_bytes
                
                if self.verbose:
                    print(f"  Bitfield size: {num_bytes} bytes\n", file=sys.stderr)

                bitfield_buffer = []
                bitfield_bit_offset = 0

            # Process current field
            if self.verbose:
                print(f"\nField: {field_name}", file=sys.stderr)
            
            if bitwidth:
                bitwidth = int(bitwidth)
                if self.verbose:
                    print(f"  Bitfield: {bitwidth} bits", file=sys.stderr)
                
                bitfield_buffer.append((field_name, bitwidth, type_info))
                bitfield_bit_offset += bitwidth
                continue
            
            # Normal field processing
            resolved_type = self.resolve_type(type_info)
            if self.verbose and resolved_type != type_info:
                print(f"  Resolved: {resolved_type}", file=sys.stderr)
            
            field_alignment = self.get_type_alignment(type_info)
            padding_needed = self.calculate_padding(offset, field_alignment)
            
            if padding_needed > 0:
                if self.verbose:
                    print(f"  Adding padding: {padding_needed} bytes", file=sys.stderr)
                fields.append(f"_pad_{offset}" / Padding(padding_needed))
                offset += padding_needed
            
            field_size = self.get_type_size(type_info)
            if self.verbose:
                print(f"  Size: {field_size}, Offset: {offset}", file=sys.stderr)
            
            # Get construct element
            element = None
            if isinstance(type_info, tuple) and type_info[0] == 'array':
                _, base_type, size = type_info
                resolved_base = self.resolve_type(base_type)
                
                if resolved_base == 'pointer':
                    element_type = Int32ul
                elif resolved_base in self.type_map:
                    element_type = self.type_map[resolved_base]
                elif resolved_base in self.structs:
                    element_type = self.structs[resolved_base]
                else:
                    element_type = Int32ul
                
                element = Array(size, element_type)
            elif type_info == 'pointer':
                element = Int32ul
            elif resolved_type in self.type_map:
                element = self.type_map[resolved_type]
            elif resolved_type in self.structs:
                element = self.structs[resolved_type]
            else:
                element = Int32ul
            
            fields.append(field_name / element)
            offset += field_size
        
        # Final bitfield flush
        # TODO: dedupe this bitfield code, it's mostly already repeated above
        if bitfield_buffer:
            # Flush bitfields
            num_bytes = (bitfield_bit_offset + 7) // 8
            
            if self.verbose:
                print(f"\n  --- Flushing Bitfield Group ({bitfield_bit_offset} bits) ---", file=sys.stderr)
            
            field_alignment = min(num_bytes, self.alignment)
            padding_needed = self.calculate_padding(offset, field_alignment)
            if padding_needed > 0:
                if self.verbose:
                    print(f"  Adding padding: {padding_needed} bytes", file=sys.stderr)
                fields.append(f"_pad_{offset}" / Padding(padding_needed))
                offset += padding_needed
            
            # Read as raw bytes first, then manually extract bitfields
            # Store the bitfield info for later extraction
            bitfield_info = []
            for bf_name, bf_bits, bf_type in bitfield_buffer:
                resolved_type = self.resolve_type(bf_type)
                is_signed = resolved_type in self.signed_types_set
                bitfield_info.append((bf_name, bf_bits, is_signed, bf_type))
                
                if self.verbose:
                    print(f"  Bitfield: {bf_name} ({bf_bits} bits, signed: {is_signed})", file=sys.stderr)
            
            # Store bitfield group as raw bytes - we'll decode manually
            fields.append(f"_bitfields_{offset}" / Bytes(num_bytes))
            
            # Store metadata for manual decoding
            if not hasattr(self, 'bitfield_metadata'):
                self.bitfield_metadata = {}
            self.bitfield_metadata[f"{struct_name}._bitfields_{offset}"] = bitfield_info
            
            offset += num_bytes
        
        # Final padding
        final_padding = self.calculate_padding(offset, self.alignment)
        if final_padding > 0:
            if self.verbose:
                print(f"\nFinal padding: {final_padding} bytes", file=sys.stderr)
            fields.append(f"_pad_end" / Padding(final_padding))
            offset += final_padding
        
        if self.verbose:
            print(f"\nTotal size: {offset} bytes\n", file=sys.stderr)
        
        return Struct(*fields), field_types

    def build_struct(self, struct_name, struct_decl):
        """Build a construct Struct from a c_ast.Struct node."""
        struct_construct, field_types = self.build_struct_internal(struct_name, struct_decl)
        self.struct_field_types[struct_name] = field_types
        return struct_construct

    def parse_sym_addrs(self, content):
        lines = content.strip().splitlines()
        for line in lines:
            # Strip leading/trailing spaces and ignore empty lines
            line = line.strip()
            if not line or line.startswith('//'):
                continue  # Skip empty lines and full-line comments

            # Split by '='
            parts = line.split('=')
            if len(parts) != 2:
                continue  # Skip lines that don't have exactly one '='

            # Get function name and value
            func_name = parts[0].strip()
            value_part = parts[1].split('//')[0].strip()  # Ignore anything after a comment

            # Ensure value is a valid hex number
            if value_part.startswith("0x"):
                try:
                    if value_part.endswith(";"):
                        value_part = value_part[:-1]
                    value = int(value_part, 16)  # Convert hex string to integer
                    self.sym_addrs[value] = func_name
                except ValueError:
                    continue  # Skip invalid hex values
            else:
                continue  # Skip lines without a valid hex value
    
    def parse_definitions(self, c_code):
        """Parse C code and build construct definitions."""
        fake_includes = """
        typedef unsigned char u8;
        typedef unsigned short u16;
        typedef unsigned int u32;
        typedef unsigned long long u64;
        typedef signed char s8;
        typedef signed short s16;
        typedef signed int s32;
        typedef signed long long s64;
        """
        
        cleaned_code = self.preprocess_code(c_code)
        full_code = fake_includes + cleaned_code
        ast = self.parser.parse(full_code)
        
        for node in ast.ext:
            # Handle Typedefs
            if isinstance(node, c_ast.Typedef):
                if isinstance(node.type.type, c_ast.IdentifierType):
                            base_type = ' '.join(node.type.type.names)
                            self.type_aliases[node.name] = base_type
                        
            # Handle Enums
            if (isinstance(node, c_ast.Decl) and isinstance(node.type, c_ast.Enum) or
                    isinstance(node, c_ast.Typedef) and isinstance(node.type.type, c_ast.Enum)):
                
                if isinstance(node, c_ast.Typedef):
                    enum_name = node.name
                    enum_decl = node.type.type
                else:
                    enum_name = node.name
                    enum_decl = node.type

                # Skip declaration-only enums
                if enum_decl is None:
                    continue
                    
                current_value = 0
                if enum_decl.values:
                    for enum_constant in enum_decl.values.enumerators:
                        if enum_constant.value:
                            # Evaluate the expression for the enum value
                            current_value = self.eval_expr(enum_constant.value)
                        
                        self.enum_values[enum_constant.name] = current_value
                        current_value += 1
                        
            # Handle Structs
            if (isinstance(node, c_ast.Decl) and isinstance(node.type, c_ast.Struct) or
                    isinstance(node, c_ast.Typedef) and isinstance(node.type.type, c_ast.Struct)):
                
                if isinstance(node, c_ast.Typedef):
                    struct_name = node.name
                    struct_decl = node.type.type
                else:
                    struct_name = node.name
                    struct_decl = node.type

                # Skip declaration-only structs
                if struct_decl.decls is None:
                    continue
                    
                self.struct_asts[struct_name] = struct_decl

                struct_def = self.build_struct(struct_name, struct_decl)
                self.structs[struct_name] = struct_def
                self.struct_sizes[struct_name] = struct_def.sizeof()

            # Handle Unions
            if (isinstance(node, c_ast.Decl) and isinstance(node.type, c_ast.Union) or
                    isinstance(node, c_ast.Typedef) and isinstance(node.type.type, c_ast.Union)):

                if isinstance(node, c_ast.Typedef):
                    union_name = node.name
                    union_decl = node.type.type
                else:
                    union_name = node.name
                    union_decl = node.type
                
                # Store AST for potential lazy building if forward-declared
                self.union_asts[union_name] = union_decl
                
                # Only build the union immediately if it has declarations
                if union_decl.decls:
                    self.build_union(union_name, union_decl)

    def eval_expr(self, node):
        """Recursively evaluate a constant expression (e.g., math, enums, sizeof)."""
        if isinstance(node, c_ast.Constant):
            return int(node.value, 0)
        
        if isinstance(node, c_ast.ID):
            if node.name in self.enum_values:
                return self.enum_values[node.name]
            # If not in enum_values, it's an unresolved identifier
            raise ValueError(f"Unknown identifier in array size expression: {node.name}")
        
        if isinstance(node, c_ast.BinaryOp):
            left = self.eval_expr(node.left)
            right = self.eval_expr(node.right)
            op = node.op
            
            if op == '+': return left + right
            if op == '-': return left - right
            if op == '*': return left * right
            if op == '/': return left // right # Integer division
            if op == '%': return left % right
            if op == '<<': return left << right
            if op == '>>': return left >> right
            if op == '|': return left | right
            raise ValueError(f"Unsupported binary operator in expression: {node.op}")

        if isinstance(node, c_ast.UnaryOp) and node.op == 'sizeof':
            # Handle sizeof(type) or sizeof(expression)
            
            # sizeof(type)
            if isinstance(node.expr, c_ast.Typename):
                type_name = self.parse_type(node.expr.type)
                size = self.get_type_size(type_name)
                # Check for types that resolve to pointer size but aren't explicitly defined structs
                if size == self.pointer_size and type_name not in self.struct_sizes and type_name not in self.type_sizes and not isinstance(type_name, tuple):
                    raise ValueError(f"Cannot determine size of unknown type for sizeof: {type_name}")
                return size
            
            # sizeof(expression) (e.g., sizeof(arr[0])) - NOT IMPLEMENTED
            # Fallback to general expression evaluation if not a typename (unlikely for array size)
            raise ValueError(f"Unsupported sizeof expression type: {node.expr}")

        if isinstance(node, c_ast.UnaryOp) and node.op == '-':
            expr = self.eval_expr(node.expr)
            return -expr

        # If it reaches here, it's an unsupported C AST node for array dimension
        print(node)
        raise ValueError(f"Unsupported C AST node for array dimension: {node.__class__.__name__}")
        
    def eval_array_size(self, dim_node):
        """Evaluate array dimension (supports constants, enums, and simple math)."""
        if dim_node is None:
            # Flexible array member or incomplete array
            return 0 
        
        try:
            return self.eval_expr(dim_node)
        except Exception as e:
            # Re-raise with context
            raise ValueError(f"Failed to evaluate array dimension expression: {e}")

    def preprocess_code(self, c_code):
        """Remove preprocessor directives and keep only struct/typedef definitions."""
        """Not perfect: --use-cpp helps make this work better"""
        lines = []
        defines = {}
        in_multiline_comment = False
        
        for line in c_code.split('\n'):
            stripped = line.strip()
            
            if '/*' in line:
                in_multiline_comment = True
            if '*/' in line:
                in_multiline_comment = False
                continue
            if in_multiline_comment:
                continue
            
            if stripped.startswith('#define'):
                parts = stripped.split(None, 2)
                if len(parts) >= 3:
                    macro_name = parts[1]
                    macro_value = parts[2]
                    if macro_value.isdigit() or (macro_value.startswith('0x') and 
                                                   all(c in '0123456789abcdefABCDEFx' for c in macro_value)):
                        defines[macro_name] = macro_value
                continue
            
            if stripped.startswith('#'):
                continue
            
            if stripped.startswith('//'):
                continue
            
            for macro_name, macro_value in defines.items():
                line = re.sub(r'\b' + re.escape(macro_name) + r'\b', macro_value, line)
            
            line = re.sub(r'\bvolatile\s+', '', line)
            line = re.sub(r'\bconst\s+', '', line)
            
            lines.append(line)
        
        return '\n'.join(lines)
    
    def parse_data(self, struct_name, data):
        """Parse binary data using the specified struct."""
        if struct_name not in self.structs:
            raise ValueError(f"Struct '{struct_name}' not found")
        
        return self.structs[struct_name].parse(data)

    def append_line(self, lines, line):
        # TODO: This should also handle self.unnamed_values somehow.
        if not self.single_line_values:
            lines.append(line)
        else:
            lines[-1] += line
    
    def to_initializer(self, parsed_data, struct_name, indent=0):
        """Convert parsed data to C initializer format."""
        indent_str = "  " * indent
        
        if isinstance(parsed_data, Container):
            lines = ["{"]
            # Get field types for the current struct/union member being processed
            current_field_types = self.struct_field_types.get(struct_name, {})
            
            for key, value in parsed_data.items():
                
                if key.startswith("_union_"):
                    # The name of the field in the C struct is after "_union_"
                    actual_field_name = key[7:] 
                    field_type = current_field_types.get(actual_field_name) 
                    
                    if isinstance(field_type, tuple) and field_type[0] == 'union':
                        _, union_name = field_type
                        
                        # Check if user specified which member to use
                        union_key = f"{struct_name}.{actual_field_name}"
                        chosen_member = self.union_choices.get(union_key)
                        
                        if chosen_member and union_name in self.union_members and chosen_member in self.union_members[union_name]:
                            # Get the chosen member's construct definition
                            member_construct, member_field_types = self.union_members[union_name][chosen_member]
                            
                            try:
                                # Re-parse the raw byte value using the chosen member's construct
                                parsed_union = member_construct.parse(value)
                            
                                # Check if this is a simple type (contains single field named _union_value)
                                if isinstance(parsed_union, Container) and "_union_value" in parsed_union:
                                    # Simple type - just output the value directly
                                    field_value = parsed_union["_union_value"]
                                    field_type = member_field_types.get("_union_value")
                                    formatted_value = self.format_value(field_value, field_type, union_key)
                                    if self.single_line_values:
                                        if not self.unnamed_values:
                                            self.append_line(lines, f"{indent_str}  .{actual_field_name} = {{  .{chosen_member} = {formatted_value} }}")
                                        else:
                                            self.append_line(lines, f"{indent_str}  {{ {formatted_value} }},")
                                    else:
                                        if not self.unnamed_values:
                                            self.append_line(lines, f"{indent_str}  .{actual_field_name} = {{")
                                            self.append_line(lines, f"{indent_str}    .{chosen_member} = {formatted_value}")
                                            self.append_line(lines, f"{indent_str}  }},")
                                        else:
                                            self.append_line(lines, f"{indent_str}  {{")
                                            self.append_line(lines, f"{indent_str}    {formatted_value}")
                                            self.append_line(lines, f"{indent_str}  }},")
                                else:
                                    # Recurse with the chosen member's internal name for correct type lookups
                                    union_init = self.to_initializer(parsed_union, f"{union_name}.{chosen_member}", indent + 1)
                                    
                                    union_lines = union_init.splitlines()
                                    
                                    # Prepend an extra two spaces to every line *after* the opening brace.
                                    body_lines_fixed = '\n'.join([
                                        '  ' + line for line in union_lines[1:]
                                    ])
                                    
                                    # Recombine: First line + newline + fixed body
                                    if not self.single_line_values:
                                        adjusted_union_init = union_lines[0] + '\n' + body_lines_fixed
                                    else:
                                        adjusted_union_init = union_lines[0] + body_lines_fixed

                                    if self.single_line_values:
                                        if not self.unnamed_values:
                                            self.append_line(lines, f"{indent_str}  .{actual_field_name} = {{  .{chosen_member} = {adjusted_union_init} }}")
                                        else:
                                            self.append_line(lines, f"{indent_str}  {{ {adjusted_union_init} }},")
                                    else:
                                        if not self.unnamed_values:
                                            # Output the nested C initializer using the chosen member's name
                                            # The output of to_initializer for a nested struct/bitfield group starts with '{'
                                            self.append_line(lines, f"{indent_str}  .{actual_field_name} = {{")
                                            self.append_line(lines, f"{indent_str}    .{chosen_member} = {adjusted_union_init}")
                                            self.append_line(lines, f"{indent_str}  }},")
                                        else:
                                            self.append_line(lines, f"{indent_str}  {{")
                                            self.append_line(lines, f"{indent_str}    {adjusted_union_init}")
                                            self.append_line(lines, f"{indent_str}  }},")
                            except Exception as e:
                                # Fallback to raw hex on parsing failure
                                hex_str = "".join(f"{b:02X}" for b in value)
                                if not self.unnamed_values:
                                    self.append_line(lines, f"{indent_str}  .{actual_field_name} = {{ /* ERROR parsing '{chosen_member}': 0x{hex_str} */ }},")
                                else:
                                    self.append_line(lines, f"{indent_str}  {{ /* ERROR parsing '{chosen_member}': 0x{hex_str} */ }},")
                        else:
                            # No choice specified - output as comment with hex
                            hex_str = "".join(f"{b:02X}" for b in value)
                            if not self.unnamed_values:
                                self.append_line(lines, f"{indent_str}  .{actual_field_name} = {{ /* union: 0x{hex_str} */ }},")
                            else:
                                self.append_line(lines, f"{indent_str}  {{ /* union: 0x{hex_str} */ }},")
                    
                    continue # Union field processed, move to next item
                
                # Handle bitfields (already present, keep it)
                if key.startswith("_bitfields_"):
                    # Manually decode the bitfield bytes
                    metadata_key = f"{struct_name}.{key}"
                    if metadata_key not in self.bitfield_metadata:
                        continue
                    
                    bitfield_info = self.bitfield_metadata[metadata_key]
                    decoded = self.decode_bitfields(value, bitfield_info)
                    
                    for bf_name, bf_value in decoded.items():
                        bf_type = current_field_types.get(bf_name)
                        if not self.unnamed_values:
                            self.append_line(lines, f"{indent_str}  .{bf_name} = {self.format_value(bf_value, bf_type, bf_name)},")
                        else:
                            self.append_line(lines, f"{indent_str}  {self.format_value(bf_value, bf_type, bf_name)},")
                    
                    continue

                if key.startswith("_"):
                    continue # Skip other internal fields like _pad_

                # Normal field processing
                field_type = current_field_types.get(key)
                if isinstance(value, Container):
                    # For nested structs (not bitfields)
                    nested = self.to_initializer(value, field_type, indent + 1)
                    if not self.unnamed_values:
                        self.append_line(lines, f"{indent_str}  .{key} = {nested},")
                    else:
                        self.append_line(lines, f"{indent_str}  {nested},")
                elif isinstance(value, list) or isinstance(value, ListContainer):
                    # For arrays
                    # Array type is stored as ('array', base_type, count)
                    array_base_type = field_type[1] if isinstance(field_type, tuple) else None
                    array_str = self.format_array(value, array_base_type, indent + 1)
                    if not self.unnamed_values:
                        self.append_line(lines, f"{indent_str}  .{key} = {array_str},")
                    else:
                        self.append_line(lines, f"{indent_str}  {array_str},")
                else:
                    # For basic types and pointers
                    if not self.unnamed_values:
                        self.append_line(lines, f"{indent_str}  .{key} = {self.format_value(value, field_type, f"{struct_name}.{key}")},")
                    else:
                        self.append_line(lines, f"{indent_str}  {self.format_value(value, field_type, f"{struct_name}.{key}")},")
            
            self.append_line(lines, f"{indent_str}}}")
            return "\n".join(lines)
        else:
            return str(parsed_data) # Should not happen for a top-level struct
    
    def format_array(self, array, base_type, indent=0):
        """Format an array for C output."""
        indent_str = "  " * indent
        
        if array and isinstance(array[0], Container):
            lines = ["{"]
            for item in array:
                nested = self.to_initializer(item, base_type, indent + 1)
                self.append_line(lines, f"{indent_str}  {nested},")
            self.append_line(lines, f"{indent_str}}}")
            return "\n".join(lines)
        else:
            values = [self.format_value(v, base_type, "") for v in array]
            if len(values) <= 8:
                return "{ " + ", ".join(values) + " }"
            lines = ["{"]
            for i in range(0, len(values), 8):
                chunk = values[i:i+8]
                self.append_line(lines, f"{indent_str}  " + ", ".join(chunk) + ",")
            self.append_line(lines, f"{indent_str}}}")
            return "\n".join(lines)
    
    def format_value(self, value, field_type, field_key):
        """Format a value for C output."""
        if isinstance(value, int):
            is_pointer = (field_type == 'pointer')
            
            if value == 0 and is_pointer:
                return "NULL"
            elif is_pointer:
                # Return symbol name if value exists inside sym_addrs, else return pointer as hex
                return self.sym_addrs[value] if value in self.sym_addrs else f"0x{value:X}"
            else:
                # silent-hill-decomp value customizations
                if field_type in ("q19_12", "q20_12"):
                    return process_fp(value, 12)
                elif field_type in ("q0_8", "q7_8", "q23_8", "q8_8"):
                    return process_fp(value, 8)
                elif field_type in ("q11_4", "q12_4", "q27_4", "q28_4"):
                    return process_fp(value, 4)
                elif field_key == "s_AnimInfo.status_4" or field_key == "s_AnimInfo.status_6":
                    return f"ANIM_STATUS({value // 2}, {'true' if value % 2 == 1 else 'false'})" if value != 255 else "NO_VALUE"
                elif field_key == "s_AnimInfo.hasVariableDuration_5" and (value == 0 or value == 1):
                    return 'true' if value == 1 else 'false'
                elif value == -1 and (field_key == "s_AnimInfo.startKeyframeIdx_C" or field_key == "s_AnimInfo.endKeyframeIdx_E"):
                    return "NO_VALUE"

                return f"0x{value:X}" if self.numbers_hex else str(value)
        
        # Handle raw byte data from unions that weren't parsed
        if isinstance(value, bytes):
            hex_str = "".join(f"{b:02X}" for b in value)
            return f"/* raw bytes: 0x{hex_str} */"
        
        return str(value)


def main():
    parser = argparse.ArgumentParser(
        description='Decompile binary data into C struct initializers',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Parse a struct from binary file
  %(prog)s -s structs.h -b data.bin -t StructName
  
  # Parse a struct from offset 0x100
  %(prog)s -s structs.h -b data.bin -o 0x100 -t StructName
  
  # Specify union member to use when union is encountered
  %(prog)s -s ctx.c -b data.bin -t s_MapPoint2d -u "s_MapPoint2d.data=spawnInfo"
  
  # Multiple union choices
  %(prog)s -s ctx.c -b data.bin -t MyStruct -u "MyStruct.field1=option1" -u "MyStruct.field2=option2"
  
  Recommend using --use-cpp to handle preprocessing header before parsing.
        """
    )
    
    parser.add_argument('-s', '--structs', required=True,
                        help='Header file containing struct definitions')
    parser.add_argument('-b', '--binary', required=True,
                        help='Binary file to read')
    parser.add_argument('-t', '--type', required=True,
                        help='Struct type name to parse')
    parser.add_argument('-o', '--offset', type=str, default='0',
                        help='Offset in binary file to start reading (hex or decimal, default: 0)')
    parser.add_argument('-c', '--count', type=int, default=1,
                        help='Number of array elements to parse (default: 1)')
    parser.add_argument('-a', '--alignment', type=int, default=4,
                        help='Struct alignment in bytes (default: 4 for 32-bit/PSX)')
    parser.add_argument('--pointer-size', type=int, default=4,
                        help='Pointer size in bytes (default: 4 for 32-bit) - note: currently ignored')
    parser.add_argument('-n', '--name', type=str, default='myData',
                        help='Variable name for the initializer (default: myData)')
    parser.add_argument('--size', type=str,
                        help='Maximum bytes to read (hex or decimal, default: read up to size of given struct)')
    parser.add_argument('--show-size', action='store_true',
                        help='Print the struct size and exit')
    parser.add_argument('--use-cpp', action='store_true',
                        help='Use C preprocessor (cpp) to process header file first')
    parser.add_argument('--cpp-args', type=str, default='',
                        help='Additional arguments to pass to cpp (e.g., "-I./include")')
    parser.add_argument('--sym', action='append', dest='symfiles',
                        help='sym.txt files to use to resolve pointer names')
    parser.add_argument('--debug-output', type=str,
                        help='Write preprocessed code to this file for debugging')
    parser.add_argument('-v', '--verbose', action='store_true',
                        help='Print verbose debug information about struct layout')
    parser.add_argument('-u', '--union', action='append', dest='union_choices',
                        help='Specify union member to use: "StructName.unionField=memberName"')
    parser.add_argument('--unnamed-values', action='store_true',
                        help='Don\'t output value names inside initializers')
    parser.add_argument('--hex', action='store_true',
                        help='Always output numbers as hexadecimal.')
    parser.add_argument('-sl', '--single-line', action='store_true',
                        help='Output array entries on a single line')
    args = parser.parse_args()
    
    # Parse union choices
    union_choice_dict = {}
    if args.union_choices:
        for choice in args.union_choices:
            if '=' not in choice:
                print(f"Error: Invalid union choice format '{choice}'. Use 'StructName.field=member'", file=sys.stderr)
                return 1
            key, value = choice.split('=', 1)
            union_choice_dict[key] = value
    
    # Parse offset
    offset = int(args.offset, 0)

    # silent-hill-decomp map address hack
    if offset > 0x800C9578:
        offset -= 0x800C9578

    max_size = int(args.size, 0) if args.size else None
    
    # Read header file
    try:
        if args.use_cpp:
            import subprocess
            cpp_cmd = ['cpp', '-P'] + args.cpp_args.split() + [args.structs]
            result = subprocess.run(cpp_cmd, capture_output=True, text=True)
            if result.returncode != 0:
                print(f"Error running C preprocessor: {result.stderr}", file=sys.stderr)
                return 1
            c_code = result.stdout
        else:
            with open(args.structs, 'r') as f:
                c_code = f.read()
    except FileNotFoundError:
        print(f"Error: Header file '{args.structs}' not found", file=sys.stderr)
        return 1
    except Exception as e:
        print(f"Error reading header file: {e}", file=sys.stderr)
        return 1
    
    # Parse struct definitions
    try:
        struct_parser = StructParser(alignment=args.alignment, verbose=args.verbose, union_choices=union_choice_dict)
        struct_parser.pointer_size = args.pointer_size
        struct_parser.unnamed_values = args.unnamed_values
        struct_parser.numbers_hex = args.hex
        struct_parser.single_line_values = args.single_line

        if args.debug_output:
            cleaned = struct_parser.preprocess_code(c_code)
            with open(args.debug_output, 'w') as f:
                f.write(cleaned)
            print(f"Preprocessed code written to {args.debug_output}", file=sys.stderr)
        
        struct_parser.parse_definitions(c_code)
    except Exception as e:
        print(f"Error parsing struct definitions: {e}", file=sys.stderr)
        if args.debug_output:
            print(f"Check {args.debug_output} to see what the parser received", file=sys.stderr)
        return 1
    
    resolved_type = struct_parser.resolve_type(args.type)
    
    # Check if struct or basic type exists, OR if it's the specific keyword 'pointer'
    is_basic_type = args.type in struct_parser.type_map or resolved_type in struct_parser.type_map or args.type == 'pointer'

    if not is_basic_type and args.type not in struct_parser.structs:
        if not is_basic_type and resolved_type not in struct_parser.structs:
            print(f"Error: Type '{args.type}' not found", file=sys.stderr)
            print(f"Available structs: {', '.join(str(k) for k in struct_parser.structs.keys() if k is not None)}", file=sys.stderr)
            print(f"Available basic types: {', '.join(struct_parser.type_map.keys())} or 'pointer'", file=sys.stderr)
            return 1
            
    # Determine if we're dealing with a struct, basic type, or pointer
    is_pointer_type = args.type == 'pointer'
    
    if is_basic_type or is_pointer_type:
        struct_size = struct_parser.get_type_size(resolved_type if not is_pointer_type else 'pointer')
    else:
        struct_size = struct_parser.struct_sizes[args.type]
    
    # Show size if requested
    if args.show_size:
        size = struct_size
        print(f"{args.type}: {size} bytes (0x{size:X})")
        return 0

    # Read binary file
    try:
        with open(args.binary, 'rb') as f:
            f.seek(offset)
            if max_size:
                data = f.read(max_size)
            else:
                data = f.read(struct_size * args.count)
    except FileNotFoundError:
        print(f"Error: Binary file '{args.binary}' not found", file=sys.stderr)
        return 1
    except Exception as e:
        print(f"Error reading binary file: {e}", file=sys.stderr)
        return 1
    
    # Check data size
    required_size = struct_size * args.count
    if len(data) < required_size:
        print(f"Warning: Only read {len(data)} bytes, but {args.type}[{args.count}] needs {required_size} bytes", 
            file=sys.stderr)

    # Parse symbol.txt files
    if args.symfiles:
        for file in args.symfiles:
            try:
                with open(file, 'r') as f:
                    struct_parser.parse_sym_addrs(f.read())
            except FileNotFoundError:
                print(f"Error: Symbol file '{file}' not found", file=sys.stderr)
                return 1
            except Exception as e:
                print(f"Error reading symbol file '{file}': {e}", file=sys.stderr)
                return 1
    
    # Parse the data
    try:
        if is_basic_type or is_pointer_type:
            # Use pointer construct if specified, otherwise use resolved basic type
            if is_pointer_type:
                construct_type = struct_parser.type_map['u32'] # Pointers are treated as u32
                array_base_type_for_format = 'pointer'
            else:
                construct_type = struct_parser.type_map[resolved_type]
                array_base_type_for_format = args.type
                
            array_construct = Array(args.count, construct_type)
            results = array_construct.parse(data)
            
            # Format output
            formatted = struct_parser.format_array(results, array_base_type_for_format, indent=0)
            
            if is_pointer_type:
                print(f"void* {args.name}[] = {formatted};")
            else:
                print(f"{args.type} {args.name}[] = {formatted};")
        else:
            if args.count == 1:
                # Single struct
                result = struct_parser.parse_data(args.type, data)
                initializer = struct_parser.to_initializer(result, args.type)
                print(f"{args.type} {args.name} = {initializer};")
            else:
                # Array of structs
                results = []
                for i in range(args.count):
                    start = i * struct_size
                    end = start + struct_size
                    if end > len(data):
                        print(f"Warning: Not enough data for element {i}", file=sys.stderr)
                        break
                    
                    chunk = data[start:end]
                    result = struct_parser.parse_data(args.type, chunk)
                    results.append(result)
                
                # Output as C array
                print(f"{args.type} {args.name}[] = {{")
                for i, result in enumerate(results):
                    initializer = struct_parser.to_initializer(result, args.type)
                    # Add comma except for last element
                    comma = "," if i < len(results) - 1 else ""
                    
                    # Indent the initializer
                    indented = "\n".join("  " + line for line in initializer.split("\n"))
                    print(f"{indented}{comma}")
                
                print("};")
            
    except Exception as e:
        print(f"Error parsing binary data: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc()
        return 1
    
    return 0

if __name__ == "__main__":
    if len(sys.argv) == 1:
        print("Run with --help for usage information")
        sys.exit(1)
    else:
        sys.exit(main())
