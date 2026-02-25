#!/usr/bin/env python3
import sys
import re
from pathlib import Path


# =============================================================================
# FILE DISCOVERY AND VALIDATION
# =============================================================================

def validate_input_path(input_path):
    path = Path(input_path)
    if not path.exists():
        print(f"Error: Path not found: {path}")
        sys.exit(1)
    if not path.is_dir():
        print(f"Error: Not a directory: {path}")
        sys.exit(1)
    return path


def discover_and_validate_files():
    # Get input path
    default_path = Path(__file__).parent.parent / 'configs/USA'
    input_path = validate_input_path(sys.argv[1] if len(sys.argv) > 1 else default_path)

    # Find files
    txt_files = sorted(input_path.rglob('*.txt'))
    yaml_files = sorted(input_path.rglob('*.yaml'))

    # no txt files found
    if not txt_files:
        print(f"Error: No files found in {input_path}")
        sys.exit(1)

    # txt file count is not equal to yaml file count
    if len(txt_files) != len(yaml_files):
        print(f"Error: Found {len(txt_files)} .txt and {len(yaml_files)} .yaml files")
        sys.exit(1)

    return txt_files, yaml_files


def discover_file_pairs(txt_files, yaml_files):
    """Create file pairs based on matching base names"""
    txt_dict = {txt_file.stem.replace('sym.', ''): txt_file for txt_file in txt_files}
    yaml_dict = {yaml_file.stem: yaml_file for yaml_file in yaml_files}

    pairs = []
    for base_name in sorted(txt_dict.keys()):
        if base_name in yaml_dict:
            pairs.append((txt_dict[base_name], yaml_dict[base_name]))

    return pairs


# =============================================================================
# YAML PARSING AND COMMENT GENERATION
# =============================================================================


def parse_yaml_for_comments(yaml_file):
    """Parse YAML file and generate comments."""

    SECTION_TYPES = {
        'rodata': ['.rodata', 'rodata', '.rdata'],
        'text': ['.text', 'asm', 'hasm', 'asmtu', 'c', 'cpp'],
        'data': ['.data', 'data'],
        'sdata': ['.sdata', 'sdata'],
        'bss': ['.bss', 'bss'],
        'sbss': ['.sbss', 'sbss'],
        'pad': ['pad']  # Special handling - no section header
    }

    with open(yaml_file, 'r') as f:
        content = f.read()

    # Simple approach - find first start: and vram: lines
    lines = content.split('\n')
    ram_start = None
    vram_start = None

    current_block = []

    for line in lines:
        stripped = line.strip()

        # Detect the start of a new segment block
        if stripped.startswith('- name:'):
            if current_block:
                # Check previous block before starting new one
                block_text = "\n".join(current_block)
                if 'start:' in block_text and 'vram:' in block_text:
                    for blk_line in current_block:
                        blk_line = blk_line.strip()
                        if blk_line.startswith('start:'):
                            ram_start = int(blk_line.split('0x')[1], 16) if '0x' in blk_line else int(
                                blk_line.split(':')[1].strip())
                        elif blk_line.startswith('vram:'):
                            vram_start = int(blk_line.split('0x')[1], 16) if '0x' in blk_line else int(
                                blk_line.split(':')[1].strip())
                    break  # Found the correct block, stop searching
            current_block = [stripped]  # Start new block
        elif stripped.startswith('segments:'):
            continue
        elif current_block is not None:
            current_block.append(stripped)

    # In case the last block was the correct one
    if ram_start is None or vram_start is None:
        block_text = "\n".join(current_block)
        if 'start:' in block_text and 'vram:' in block_text:
            for blk_line in current_block:
                blk_line = blk_line.strip()
                if blk_line.startswith('start:'):
                    ram_start = int(blk_line.split('0x')[1], 16) if '0x' in blk_line else int(
                        blk_line.split(':')[1].strip())
                elif blk_line.startswith('vram:'):
                    vram_start = int(blk_line.split('0x')[1], 16) if '0x' in blk_line else int(
                        blk_line.split(':')[1].strip())

    # if ram_start is not None and vram_start is not None:
        # print(f"DEBUG ADDRESSES: ram_start=0x{ram_start:X}, vram_start=0x{vram_start:X}")
    # else:
        # print("Could not find a segment with both start and vram.")

    # Create section headers (exclude pad)
    section_map = {
        name: [
            "//" + "=" * 48,
            f"//=== .{name} section",
            "//" + "=" * 48
        ]
        for name in SECTION_TYPES.keys() if name != 'pad'
    }

    # Parse only subsegment lines (starting with "      - [0x")
    subsegment_map = {}

    for line in lines:
        line = line.strip()
        if line.startswith('- [0x') and ', ' in line:
            # Strip everything after the first closing bracket (including comments)
            line = line.split(']', 1)[0] + ']'

            # Parse: "- [0x1234, stuff, more stuff]"
            line = line[2:]  # Remove "- "
            line = line[1:-1]  # Remove [ ]
            parts = [part.strip() for part in line.split(',')]

            ram = int(parts[0], 16)  # First part is always the address
            vram = vram_start - ram_start + ram
            segment_info = ', '.join(parts[1:])  # Everything else

            # print(f"DEBUG CALC: ram={parts[0]} -> vram=0x{vram_start:X} - 0x{ram_start:X} + {parts[0]} = 0x{vram:X}")

            # Clean up segment parts for section detection
            clean_parts = [part.strip() for part in parts[1:]]

            if clean_parts[0] == 'lib' or clean_parts[0] == 'o':
                section_type = clean_parts[-1]
                section_name = None
                for name, types in SECTION_TYPES.items():
                    if section_type in types:
                        section_name = name if name != 'pad' else None
                        break
                if not section_name:
                    section_name = 'text'
            else:
                section_type = clean_parts[0]
                section_name = None
                for name, types in SECTION_TYPES.items():
                    if section_type in types:
                        section_name = name if name != 'pad' else None
                        break

            if section_name:
                info_line = f"PA: 0x{ram:06X}   VA: 0x{vram:08X}   subsegment: {segment_info}"
                separator = "//----" + "-" * len(info_line)
                comment_lines = [separator, f"//--- {info_line}", separator]
                subsegment_map[vram] = (section_name, comment_lines)

    return section_map, subsegment_map


# =============================================================================
# TEXT PROCESSING AND FORMATTING
# =============================================================================

def clean_yaml_comments_from_txt(txt_lines):
    """Remove all YAML-generated comments and decorative lines"""
    cleaned = []

    for txt_line in txt_lines:

        # Skip empty lines
        if not txt_line:
            continue

        # Skip all YAML-generated content
        if (txt_line.startswith("//---") or
            txt_line.startswith("//===")):
            continue

        cleaned.append(txt_line)

    return cleaned


def convert_hex_to_uppercase(text):
    """Convert hex values to uppercase"""
    lines = text.split('\n')
    result = []

    for line in lines:
        if "0x" in line:
            # Find and convert hex values
            hex_match = re.search(r'0x[0-9a-fA-F]+', line)
            if hex_match:
                try:
                    hex_value = int(hex_match.group(), 16)
                    uppercase_hex = f"0x{hex_value:X}"
                    line = line.replace(hex_match.group(), uppercase_hex)
                except ValueError:
                    pass
        result.append(line)

    return '\n'.join(result)


def sort_and_format_with_yaml_comments(input_text, section_map, subsegment_map):
    """Sort variables by address and insert YAML comments at the right places"""
    import re

    lines = input_text.strip().split('\n')

    # Parse txt file into variable groups
    variables = []
    current_comments = []

    for line in lines:
        if not line.strip() or line.strip().startswith('//'):
            current_comments.append(line)
        else:
            # Variable line - extract address
            hex_match = re.search(r'0x[0-9a-fA-F]+', line)
            address = int(hex_match.group(), 16) if hex_match else 0

            variables.append({
                'address': address,
                'variable_line': line,
                'original_comments': current_comments[:]
            })
            current_comments = []

    # Calculate alignment for variables
    max_var_length = 0
    for var in variables:
        if '=' in var['variable_line']:
            var_part = var['variable_line'].split('=')[0].rstrip()
            max_var_length = max(max_var_length, len(var_part))

    # Sort variables by address
    variables.sort(key=lambda x: x['address'])

    # Build output by processing variables in order and inserting subsegments when needed
    output_lines = []
    seen_sections = set()
    used_subsegments = set()

    for var in variables:
        address = var['address']

        # Find all subsegments that should appear before this variable
        subsegments_to_add = []
        for sub_addr, (section_name, subseg_comments) in subsegment_map.items():
            if sub_addr <= address and sub_addr not in used_subsegments:
                subsegments_to_add.append((sub_addr, section_name, subseg_comments))
                used_subsegments.add(sub_addr)

        # Sort subsegments by address and add them
        for sub_addr, section_name, subseg_comments in sorted(subsegments_to_add):
            # print(f"DEBUG FORMAT: Adding subsegment 0x{sub_addr:08X} before variable 0x{address:08X}")

            # Add section header if not seen before
            if section_name not in seen_sections:
                output_lines.extend(['', '', ''])  # Spacing before section
                output_lines.extend(section_map[section_name])
                output_lines.append('')  # Spacing after section
                seen_sections.add(section_name)

            # Add subsegment comment
            output_lines.append('')  # Spacing before subsegment
            output_lines.extend(subseg_comments)

        # Add original comments
        for comment in var['original_comments']:
            output_lines.append(comment)

        # Add aligned variable line
        line = var['variable_line']
        if '=' in line:
            parts = line.split('=', 1)
            var_part = parts[0].rstrip()
            value_part = parts[1]
            aligned_line = var_part.ljust(max_var_length) + ' =' + value_part
            output_lines.append(aligned_line)
        else:
            output_lines.append(line)

    # Add newline to file end
    output_lines.append('')

    return '\n'.join(output_lines)


# =============================================================================
# MAIN EXECUTION
# =============================================================================

def main():
    # Discover and validate files
    txt_files, yaml_files = discover_and_validate_files()

    # Process pairs
    pairs = discover_file_pairs(txt_files, yaml_files)
    print(f"Processing {len(pairs)} file pairs")

    for txt_file, yaml_file in pairs:
        print(f"\n\n=== {txt_file.name} + {yaml_file.name} ===\n")

        # Read files
        with open(txt_file, 'r', encoding='utf-8') as f:
            txt_content = f.read()

        # Parse YAML
        section_map, subsegment_map = parse_yaml_for_comments(yaml_file)
        print(f"Found {len(subsegment_map)} subsegments")



        # Process pipeline:
        # 1. Clean old YAML comments
        txt_lines = txt_content.split('\n')
        cleaned_lines = clean_yaml_comments_from_txt(txt_lines)
        cleaned_content = '\n'.join(cleaned_lines)

        # 2. Convert hex to uppercase
        uppercase_content = convert_hex_to_uppercase(cleaned_content)

        # 3. Sort and add YAML comments
        final_content = sort_and_format_with_yaml_comments(
            uppercase_content, section_map, subsegment_map
        )

        # Output (debug mode)
        # print(final_content)

        # to write to files
        with open(txt_file, 'w', encoding='utf-8') as f:
            f.write(final_content)


if __name__ == "__main__":
    main()
