#!/usr/bin/env python3
import os
import re
from pathlib import Path
from dataclasses import dataclass
from typing import List, Set, Dict
from collections import defaultdict

# Try to import pycparser, but make it optional
try:
    from pycparser import c_parser, c_ast, parse_file
    from pycparser.c_generator import CGenerator
    PYCPARSER_AVAILABLE = True
except ImportError:
    PYCPARSER_AVAILABLE = False
    print("Warning: pycparser not available. Install with: pip install pycparser")
    print("Data reference analysis will use regex fallback.\n")

@dataclass
class AsmFileAnalysis:
    filepath: str
    size_lines: int
    has_gte_opcodes: bool
    gte_count: int
    has_gsout_packet: bool
    gsout_count: int
    loop_count: int
    data_refs: Set[str]
    undeclared_data_refs: Set[str]
    difficulty_score: float

def extract_symbols_from_headers_pycparser(include_dir: str) -> Set[str]:
    """Extract all declared symbols from headers using pycparser"""
    symbols = set()
    include_path = Path(include_dir)
    
    if not include_path.exists():
        print(f"Warning: Include directory '{include_dir}' not found")
        return symbols
    
    # Collect all header files
    header_files = list(include_path.rglob('*.h'))
    print(f"Parsing {len(header_files)} header files with pycparser...")
    
    class DeclVisitor(c_ast.NodeVisitor):
        def __init__(self):
            self.symbols = set()
        
        def visit_Decl(self, node):
            if node.name:
                self.symbols.add(node.name)
        
        def visit_FuncDef(self, node):
            if node.decl and node.decl.name:
                self.symbols.add(node.decl.name)
    
    for header in header_files:
        try:
            # Create a temporary preprocessed file
            # pycparser needs preprocessing, so we'll use fake_libc_include
            ast = parse_file(str(header), use_cpp=False)
            
            visitor = DeclVisitor()
            visitor.visit(ast)
            symbols.update(visitor.symbols)
            
        except Exception as e:
            # If pycparser fails, fall back to regex for this file
            try:
                with open(header, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                    # Remove comments
                    content = re.sub(r'//.*?$', '', content, flags=re.MULTILINE)
                    content = re.sub(r'/\*.*?\*/', '', content, flags=re.DOTALL)
                    
                    # Find declarations (simple regex approach)
                    matches = re.findall(r'\b(?:extern\s+)?(?:static\s+)?(?:const\s+)?(?:volatile\s+)?'
                                       r'(?:unsigned\s+|signed\s+)?(?:\w+\s+\**\s*)(\w+)\s*(?:[;\[\(])', 
                                       content)
                    symbols.update(matches)
            except:
                pass
    
    return symbols

def extract_symbols_from_headers_regex(include_dir: str) -> Set[str]:
    """Extract declared symbols from headers using regex (fallback method)"""
    symbols = set()
    include_path = Path(include_dir)
    
    if not include_path.exists():
        print(f"Warning: Include directory '{include_dir}' not found")
        return symbols
    
    header_files = list(include_path.rglob('*.h'))
    print(f"Scanning {len(header_files)} header files with regex...")
    
    for header in header_files:
        try:
            with open(header, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
                
                # Remove single-line comments
                content = re.sub(r'//.*?$', '', content, flags=re.MULTILINE)
                # Remove multi-line comments
                content = re.sub(r'/\*.*?\*/', '', content, flags=re.DOTALL)
                
                # Pattern to match variable/function declarations
                # Matches: type name; or type name[]; or type name(...);
                # Handles: extern, static, const, volatile modifiers
                decl_pattern = r'\b(?:extern\s+)?(?:static\s+)?(?:const\s+)?(?:volatile\s+)?'
                decl_pattern += r'(?:unsigned\s+|signed\s+)?'
                decl_pattern += r'(?:struct\s+\w+|union\s+\w+|enum\s+\w+|\w+)'
                decl_pattern += r'\s+\**\s*(\w+)\s*(?:[;\[\(])'
                
                matches = re.findall(decl_pattern, content)
                symbols.update(matches)
                
                # Also catch #define macros (data references might be macros)
                define_pattern = r'#define\s+(\w+)'
                define_matches = re.findall(define_pattern, content)
                symbols.update(define_matches)
                
        except Exception as e:
            pass
    
    return symbols

def extract_data_references(content: str) -> Set[str]:
    """Extract data symbol references from assembly code"""
    data_refs = set()
    
    # Pattern for %hi(symbol) and %lo(symbol)
    hi_lo_pattern = r'%(?:hi|lo)\(([A-Za-z_][A-Za-z0-9_]*)\)'
    matches = re.findall(hi_lo_pattern, content)
    data_refs.update(matches)
    
    # Also catch direct symbol references (without %hi/%lo)
    # Common patterns: label references, .word directives
    direct_pattern = r'\b([A-Z_][A-Z0-9_]*)\b'
    matches = re.findall(direct_pattern, content)
    # Filter to only symbols that look like data (all caps with underscores)
    data_refs.update(m for m in matches if m.startswith('D_'))
    
    return data_refs

def count_loops(content: str) -> int:
    """Count branch-back patterns that indicate loops"""
    loop_count = 0
    lines = content.split('\n')
    labels = {}
    
    # First pass: collect label positions
    for i, line in enumerate(lines):
        line = line.strip()
        if line and ':' in line and not line.startswith('#'):
            label = line.split(':')[0].strip()
            if label:
                labels[label] = i
    
    # Second pass: find backward branches
    for i, line in enumerate(lines):
        # Look for branch instructions
        if re.search(r'\b(b|beq|beqz|bne|bnez|blez|bgtz|bltz|bgez|beql|bnel|blezl|bgtzl|bltzl|bgezl)\b', line, re.IGNORECASE):
            # Extract target label
            parts = line.split()
            if len(parts) >= 2:
                target = parts[-1].strip()
                # Check if it's a backward branch (loop)
                if target in labels and labels[target] <= i:
                    loop_count += 1
    
    return loop_count

def analyze_asm_file(filepath: Path, declared_symbols: Set[str]) -> AsmFileAnalysis:
    """Analyze a single assembly file for difficulty factors"""
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    
    if ".section .rodata" in content and ".section .text" not in content:
        return None

    lines = content.split('\n')
    size_lines = len([l for l in lines if l.strip() and not l.strip().startswith('#')])
    
    # Check for GTE opcodes (common PSX GTE instructions)
    gte_opcodes = [
        'rtps', 'rtpt', 'mvmva', 'dpcs', 'dpct', 'intpl', 'sqr', 'ncs', 'nct',
        'ncds', 'ncdt', 'nccs', 'ncct', 'cdp', 'cc', 'dcpl', 'gpf', 'gpl',
        'avsz3', 'avsz4', 'op', 'swc2', 'mfc2', 'mtc2', 'cfc2'
    ]
    
    gte_pattern = r'\b(' + '|'.join(gte_opcodes) + r')\b'
    gte_matches = re.findall(gte_pattern, content, re.IGNORECASE)
    has_gte = len(gte_matches) > 0
    gte_count = len(gte_matches)
    
    # Check for GsOUT_PACKET_P references
    gsout_matches = re.findall(r'GsOUT_PACKET_P', content, re.IGNORECASE)
    has_gsout = len(gsout_matches) > 0
    gsout_count = len(gsout_matches)
    
    # Count loops
    loop_count = count_loops(content)
    
    # Extract data references
    data_refs = extract_data_references(content)
    
    # Find undeclared data references
    undeclared = data_refs - declared_symbols

    # Calculate difficulty score
    difficulty = 0.0
    
    # Difficulty weights follow:

    # Size factor: gentle curve, only becomes significant for very long functions
    if size_lines < 50:
        difficulty += size_lines * 0.1
    elif size_lines < 100:
        difficulty += 5 + (size_lines - 50) * 0.2
    elif size_lines < 300:
        difficulty += 15 + (size_lines - 100) * 0.25
    else:
        difficulty += 55 + (size_lines - 300) * 0.30
    
    # GTE opcodes (medium weight, not hard to decomp but usually means harder code around it)
    # Base cost for having any GTE, plus small per-instance cost
    if has_gte:
        difficulty += 15.0 + (gte_count * 1.0)
    
    # GsOUT_PACKET_P: higher difficulty - packet decoding takes time
    # Higher base cost, moderate per-instance scaling
    if has_gsout:
        difficulty += 25.0 + (gsout_count * 4.0)
    
    # Loops: variable difficulty, moderate weight
    # Having loops at all adds base difficulty, scales moderately
    if loop_count > 0:
        difficulty += 8.0 + (loop_count * 6.0)
    
    # Undeclared data: highly variable difficulty
    # Conservative base cost per symbol, assuming mix of simple and complex types
    # Could be u32 (easy) or complex struct (hard), so middle ground
    difficulty += len(undeclared) * 8.0
    
    return AsmFileAnalysis(
        filepath=str(filepath),
        size_lines=size_lines,
        has_gte_opcodes=has_gte,
        gte_count=gte_count,
        has_gsout_packet=has_gsout,
        gsout_count=gsout_count,
        loop_count=loop_count,
        data_refs=data_refs,
        undeclared_data_refs=undeclared,
        difficulty_score=difficulty
    )

def find_and_analyze_files(root_dir: str, include_dir: str) -> List[AsmFileAnalysis]:
    """Find all .s files in nonmatchings directories and analyze them"""
    results = []
    root_path = Path(root_dir)
    
    if not root_path.exists():
        print(f"Error: Directory '{root_dir}' not found")
        return results
    
    # First, extract all declared symbols from headers
    print(f"\nExtracting symbols from headers in '{include_dir}'...")
    if PYCPARSER_AVAILABLE:
        declared_symbols = extract_symbols_from_headers_pycparser(include_dir)
    else:
        declared_symbols = extract_symbols_from_headers_regex(include_dir)
    
    print(f"Found {len(declared_symbols)} declared symbols in headers\n")
    
    # Find all .s files containing 'nonmatchings' in path
    print(f"Analyzing assembly files in '{root_dir}'...")
    s_files = [f for f in root_path.rglob('*.s') if 'nonmatchings' in str(f) and "/D_" not in str(f) and "/g_" not in str(f)]
    print(f"Found {len(s_files)} files to analyze...\n")
    
    for s_file in s_files:
        try:
            analysis = analyze_asm_file(s_file, declared_symbols)
            if analysis:
                results.append(analysis)
        except Exception as e:
            print(f"Error analyzing {s_file}: {e}")

    return results

def print_results(analyses: List[AsmFileAnalysis], show_data_refs: bool = False):
    """Print analysis results in a formatted table"""
    if not analyses:
        print("No files found matching criteria.")
        return
    
    analyses.sort(key=lambda x: x.difficulty_score, reverse=True)
    
    print(f"\n{'='*130}")
    print(f"Found {len(analyses)} assembly files in nonmatchings directories")
    print(f"{'='*130}\n")
    
    if show_data_refs:
        print(f"{'Difficulty':<12} {'Lines':<8} {'GTE':<8} {'GSOUT':<8} {'Loops':<8} {'DataRefs':<10} {'Undecl':<9} {'File':<50}")
    else:
        print(f"{'Difficulty':<12} {'Lines':<8} {'GTE':<8} {'GSOUT':<8} {'Loops':<8} {'Undecl':<9} {'File':<70}")
    print("="*130)
    
    for analysis in analyses:
        gte_mark = f"GTE({analysis.gte_count})" if analysis.has_gte_opcodes else "-"
        gsout_mark = f"GS({analysis.gsout_count})" if analysis.has_gsout_packet else "-"
        loop_mark = f"LOOP({analysis.loop_count})" if analysis.loop_count > 0 else "-"
        data_mark = f"UNDEF({len(analysis.undeclared_data_refs)})" if len(analysis.undeclared_data_refs) > 0 else "-"
        diff_str = f"{analysis.difficulty_score:>6.1f}"
        
        if show_data_refs:
            print(f"{diff_str:<12} {analysis.size_lines:<8} {gte_mark:<8} {gsout_mark:<8} "
                  f"{loop_mark:<8} {len(analysis.data_refs):<10} {data_mark:<9} "
                  f"{analysis.filepath}")
        else:
            print(f"{diff_str:<12} {analysis.size_lines:<8} {gte_mark:<8} {gsout_mark:<8} "
                  f"{loop_mark:<8} {data_mark:<9} {analysis.filepath}")
    
    print("="*130)
    
    # Summary statistics
    total_lines = sum(a.size_lines for a in analyses)
    avg_difficulty = sum(a.difficulty_score for a in analyses) / len(analyses)
    files_with_gte = sum(1 for a in analyses if a.has_gte_opcodes)
    files_with_gsout = sum(1 for a in analyses if a.has_gsout_packet)
    total_data_refs = sum(len(a.data_refs) for a in analyses)
    total_undeclared = sum(len(a.undeclared_data_refs) for a in analyses)
    
    print(f"\nSummary:")
    print(f"  Unmatched file count: {len(analyses)}")
    print(f"  Total lines of assembly: {total_lines}")
    print(f"  Average difficulty: {avg_difficulty:.1f}")
    print(f"  Files with GTE opcodes: {files_with_gte}")
    print(f"  Files with GsOUT_PACKET_P: {files_with_gsout}")
    print(f"  Undeclared data references: {total_undeclared}/{total_data_refs}")

if __name__ == '__main__':
    import sys
    
    # Command line arguments
    asm_dir = sys.argv[1] if len(sys.argv) > 1 else 'asm'
    include_dir = sys.argv[2] if len(sys.argv) > 2 else 'include'
    show_data = '--show-data' in sys.argv or '-d' in sys.argv
    
    print(f"SH1 decomp function difficulty rater")
    print(f"Assembly directory: {asm_dir}")
    print(f"Include directory: {include_dir}")
    print(f"Include parser: {'pycparser' if PYCPARSER_AVAILABLE else 'regex fallback'}")
    
    analyses = find_and_analyze_files(asm_dir, include_dir)
    print_results(analyses, show_data_refs=show_data)