#!/usr/bin/env python3

# Usage:
#   tools/naming_progress.py <elf path> [--verbose]
# eg:
#   tools/naming_progress.py build/USA/out/1ST/BODYPROG.BIN.elf
#   tools/naming_progress.py build/USA/out/1ST/BODYPROG.BIN.elf --verbose
#   tools/naming_progress.py build/USA/src/bodyprog/sound/sfx.c.o
#
# This will display a summary of the auto-generated/non-matching names in the file
# --verbose will also list out those names for viewing.
#
# Funcs/data are counted as auto-generated if they begin with
#  func_ / sharedFunc_ / D_ / sharedData_
#
# Non-match is detected by finding a <func/data name>.NON_MATCHING symbol
# Note that this isn't completely reliable though!
# Seems some C funcs that are still INCLUDE_ASM aren't counted (the 3 bodyprog funcs)
# while some data which is matched also has NON_MATCHING symbols for some reason too.
#
# TODO: Add sym.txt parsing so we can grab the names of .c files from the comments.

import sys
import argparse
from elftools.elf.elffile import ELFFile

FUNC_AUTO_PREFIXES = ("func_", "sharedFunc_")
DATA_AUTO_PREFIXES = ("D_", "sharedData_")

# Linker/compiler symbols to skip
IGNORED_SYMBOLS = {"__gnu_compiled_c", "gcc2_compiled."}
IGNORED_SUFFIXES = (
    "_ROM_START", "_ROM_END", "_RODATA_START", "_RODATA_END",
    "_BSS_START", "_BSS_END", "_TEXT_START", "_TEXT_END",
    "_DATA_START", "_DATA_END", "_SDATA_START", "_SDATA_END",
    "_VRAM", "_VRAM_END", "_DATA_SIZE", "_bin_end",
)

def parse_elf_symbols(path, base_filter=True):
    """Extract function and data symbols from an ELF file.

    Returns a dict with 'functions' and 'data' keys, each containing
    a dict with 'named' and 'auto' lists of (name, address) tuples,
    plus a 'non_matching' count.
    """
    base_addr = 0
    end_addr = None

    # name -> addr dicts
    func_symbols = {}
    data_symbols = {}

    with open(path, "rb") as f:
        elffile = ELFFile(f)

        # Base address from first PT_LOAD segment
        for segment in elffile.iter_segments():
            if segment["p_type"] == "PT_LOAD":
                base_addr = segment["p_vaddr"]
                break

        # Collect all symbols
        vram_ends = []

        for section in elffile.iter_sections():
            if not hasattr(section, "iter_symbols"):
                continue
            for sym in section.iter_symbols():
                addr = sym["st_value"]
                name = sym.name
                if not name or addr == 0:
                    continue

                if name.endswith("_VRAM_END"):
                    vram_ends.append(addr)

                if name in IGNORED_SYMBOLS or any(name.endswith(s) for s in IGNORED_SUFFIXES):
                    continue

                # STT_FUNC is reliable for functions even with merged sections
                if sym["st_info"]["type"] == "STT_FUNC":
                    func_symbols[name] = addr
                else:
                    # Classify by name prefix since splat merges all sections
                    base_name = name.removesuffix(".NON_MATCHING")
                    if any(base_name.startswith(p) for p in DATA_AUTO_PREFIXES):
                        data_symbols[name] = addr
                    elif not any(base_name.startswith(p) for p in FUNC_AUTO_PREFIXES):
                        data_symbols[name] = addr

        if vram_ends:
            end_addr = min(vram_ends)

    def in_range(addr):
        if not base_filter:
            return True
        return addr > base_addr and (end_addr is None or addr < end_addr)

    def classify(symbols, auto_prefixes, other):
        named = []
        auto = []
        non_matching = []
        for name, addr in symbols.items():
            if not in_range(addr):
                continue
            # .NON_MATCHING entries are counted separately, skip from main lists
            if name.endswith(".NON_MATCHING"):
                continue
            if any(name.startswith(p) for p in auto_prefixes):
                auto.append((name, addr))
            else:
                named.append((name, addr))
            # Check if <name>.NON_MATCHING exists in either dict
            nm_name = name + ".NON_MATCHING"
            if nm_name in symbols or nm_name in other:
                non_matching.append((name, addr))
        return named, auto, non_matching

    fn_named, fn_auto, fn_nm = classify(func_symbols, FUNC_AUTO_PREFIXES, data_symbols)
    dt_named, dt_auto, dt_nm = classify(data_symbols, DATA_AUTO_PREFIXES, func_symbols)

    return {
        "functions": {"named": fn_named, "auto": fn_auto, "non_matching": fn_nm},
        "data": {"named": dt_named, "auto": dt_auto, "non_matching": dt_nm},
    }


def print_bar(fraction, width=40):
    filled = int(fraction * width)
    empty = width - filled
    return "[" + "#" * filled + "-" * empty + "]"

def print_category(label, named, auto, non_matching, verbose):
    total = len(named) + len(auto)
    if total == 0:
        print(f"  No {label.lower()} symbols found.")
        return
 
    pct = len(named) / total * 100
    total_label = f"Total {label.lower()}:"
 
    print(f"  {total_label:16s}{total:>5}")
    print(f"  {'Named:':16s}{len(named):>5}  ({pct:5.1f}%)  {print_bar(pct / 100)}")
    print(f"  {'Auto-generated:':16s}{len(auto):>5}  ({100 - pct:5.1f}%)")
 
    if non_matching:
        print(f"  {'Non-matching:':16s}{len(non_matching):>5}")
 
    if verbose and auto:
        print(f"\n  --- Auto-generated {label.lower()} ({len(auto)}) ---")
        for name, addr in sorted(auto, key=lambda x: x[1]):
            print(f"    0x{addr:08X}  {name}")
 
    if verbose and non_matching:
        print(f"\n  --- Non-matching {label.lower()} ({len(non_matching)}) ---")
        for name, addr in sorted(non_matching, key=lambda x: x[1]):
            print(f"    0x{addr:08X}  {name}")
 
 
def main():
    parser = argparse.ArgumentParser(
        description="Show symbol naming progress from an ELF file"
    )
    parser.add_argument("elf_path", help="Path to the ELF file")
    parser.add_argument(
        "--verbose", "-v", action="store_true",
        help="List all auto-generated symbol names"
    )
    parser.add_argument(
        "--no-filter", action="store_true",
        help="Don't filter symbols by overlay address range"
    )
    args = parser.parse_args()
 
    result = parse_elf_symbols(args.elf_path, base_filter=not args.no_filter)
 
    fn = result["functions"]
    dt = result["data"]
 
    total_all = len(fn["named"]) + len(fn["auto"]) + len(dt["named"]) + len(dt["auto"])
    if total_all == 0:
        print("No function or data symbols found in ELF.")
        sys.exit(1)
 
    named_all = len(fn["named"]) + len(dt["named"])
    pct_all = named_all / total_all * 100
 
    print(f"ELF: {args.elf_path}")
    print()
    print(f"=== Overall ===")
    print(f"  {'Total symbols:':16s}{total_all:>5}")
    print(f"  {'Named:':16s}{named_all:>5}  ({pct_all:5.1f}%)  {print_bar(pct_all / 100)}")
    print(f"  {'Auto-generated:':16s}{total_all - named_all:>5}  ({100 - pct_all:5.1f}%)")
 
    nm_all = len(fn["non_matching"]) + len(dt["non_matching"])
    if nm_all:
        print(f"  {'Non-matching:':16s}{nm_all:>5}")
 
    print(f"\n=== Functions ===")
    print_category("Functions", fn["named"], fn["auto"], fn["non_matching"], args.verbose)
 
    print(f"\n=== Data ===")
    print_category("Data", dt["named"], dt["auto"], dt["non_matching"], args.verbose)

if __name__ == "__main__":
    main()
