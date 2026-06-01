#!/usr/bin/env python3

# Usage:
#   tools/naming_progress.py <elf path> [--verbose] [--code] [--data]
# eg:
#   tools/naming_progress.py build/USA/out/1ST/BODYPROG.BIN.elf
#   tools/naming_progress.py build/USA/out/1ST/BODYPROG.BIN.elf --verbose
#
# This will display a summary of the auto-generated/non-matching names in the file
# along with the progress of each C file/subsegment in the splat config.
#
# --verbose will also list each auto-generated/non-matched name.
#
# --code/--data can be used to only display functions or data.
#
# Funcs/data are counted as auto-generated if they begin with
#  func_ / sharedFunc_ / D_ / sharedData_
#
# Non-match is detected by finding a <func/data name>.NON_MATCHING symbol
# Note that this isn't completely reliable though!
# Seems some C funcs that are still INCLUDE_ASM aren't counted (the 3 bodyprog funcs)
# while some data which is matched also have NON_MATCHING symbols for some reason too.
#
# Some syms detected as auto-generated might not actually exist in the C/headers too.
# These likely only exist in the splat ASM, and our C code might use an array/struct field to access it instead.
# To fix these just add a `size:0xXX` to the splat sym it belongs inside and rebuild.
#
# TODO: Test with maps/screens elf files.

import bisect
import os
import re
import sys
import argparse

import yaml
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

SKIP_SOURCES = (
    "libpad/", "libgte/", "libgs/", "libapi/", "libc/",
    "libcard/", "libcd/", "libgpu/", "libspu/",
)

def find_config(elf_path, filename_fmt, ext):
    """Find a config file for the given ELF.

    Searches:
      configs/USA/<name>.<ext>
      configs/USA/maps/<name>.<ext>
      configs/USA/screens/<name>.<ext>
    """
    basename = os.path.basename(elf_path)
    elfname = basename.split(".")[0].lower()

    # Walk up from elf_path to find repo root (where configs/ lives)
    search = os.path.abspath(os.path.dirname(elf_path))
    for _ in range(10):
        configs_dir = os.path.join(search, "configs", "USA")
        if os.path.isdir(configs_dir):
            break
        parent = os.path.dirname(search)
        if parent == search:
            return None
        search = parent
    else:
        return None

    name = filename_fmt.format(elfname)
    candidates = [
        os.path.join(configs_dir, f"{name}.{ext}"),
        os.path.join(configs_dir, "maps", f"{name}.{ext}"),
        os.path.join(configs_dir, "screens", f"{name}.{ext}"),
    ]

    for path in candidates:
        if os.path.isfile(path):
            return path

    return None

def find_sym_txt(elf_path):
    return find_config(elf_path, "sym.{}", "txt")

def find_config_yaml(elf_path):
    return find_config(elf_path, "{}", "yaml")

def parse_sym_txt(path):
    """Parse a splat sym.txt file.

    Returns a dict of symbol_name -> source_file.
    Source file comes from subsegment comments like:
      //--- PA: 0x009AD0   VA: 0x8002E630   subsegment: c, memcard
    """
    sym_to_source = {}
    current_source = None

    # Named: "subsegment: c, memcard"
    named_re = re.compile(r"//---.*VA:\s*(0x[0-9A-Fa-f]+).*subsegment:\s*\S+,\s*(\S+)")
    # Unnamed: "subsegment: bss" (no comma, no source name)
    unnamed_re = re.compile(r"//---.*VA:\s*(0x[0-9A-Fa-f]+).*subsegment:\s*(\S+)\s*$")

    with open(path, "r") as f:
        for line in f:
            line = line.strip()

            m = named_re.match(line)
            if m:
                current_source = m.group(2).rstrip(",")
                continue

            m = unnamed_re.match(line)
            if m:
                va = m.group(1)
                current_source = f"unnamed_{int(va, 16):08X}"
                continue

            if not line or line.startswith("//"):
                continue

            parts = line.split("=")
            if len(parts) != 2:
                continue

            name = parts[0].strip()
            if current_source:
                sym_to_source[name] = current_source

    return sym_to_source

def parse_config_yaml(path):
    """Parse a splat config YAML to extract subsegment address ranges.

    Returns a sorted list of (va, source_or_none) tuples.
    Unnamed subsegments have None as source so they properly bound ranges.
    """
    with open(path, "r") as f:
        config = yaml.safe_load(f)

    def to_int(val):
        if isinstance(val, int):
            return val
        if isinstance(val, str):
            try:
                return int(val, 0)
            except ValueError:
                return None
        return None

    ranges = []

    for segment in config.get("segments", []):
        if isinstance(segment, list):
            # End marker like [0x1A600], skip
            continue
        if not isinstance(segment, dict):
            continue

        vram = to_int(segment.get("vram", 0)) or 0
        subsegments = segment.get("subsegments", [])

        for sub in subsegments:
            if not isinstance(sub, list) or len(sub) < 2:
                continue

            offset = to_int(sub[0])
            if offset is None:
                continue
            va = vram + offset

            if len(sub) >= 3:
                # Named: [offset, type, name]
                source = sub[2]
            else:
                # Unnamed: [offset, type] - label by address
                source = f"unnamed_{va:08X}"

            ranges.append((va, source))

    ranges.sort(key=lambda x: x[0])
    return ranges

def parse_elf_symbols(path, base_filter=True):
    """Extract function and data symbols from an ELF file.

    Returns a dict with 'functions' and 'data' keys, each containing
    a dict with 'named' and 'auto' lists of (name, address) tuples,
    plus a 'non_matching' list.
    """
    base_addr = 0
    end_addr = None

    # name -> addr dicts
    func_symbols = {}
    data_symbols = {}

    with open(path, "rb") as f:
        elffile = ELFFile(f)

        for segment in elffile.iter_segments():
            if segment["p_type"] == "PT_LOAD":
                base_addr = segment["p_vaddr"]
                break

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

                if sym["st_info"]["type"] == "STT_FUNC":
                    func_symbols[name] = addr
                else:
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
            if name.endswith(".NON_MATCHING"):
                continue
            if any(name.startswith(p) for p in auto_prefixes):
                auto.append((name, addr))
            else:
                named.append((name, addr))
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

def print_category(label, named, auto, non_matching):
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

def lookup_source(name, addr, sym_to_source, subseg_ranges, subseg_addrs):
    """Look up source file for a symbol.

    Tries name-based lookup in sym.txt first, then falls back to
    address-based bisect into YAML subsegment ranges.
    """
    source = sym_to_source.get(name)
    if source:
        return source
    idx = bisect.bisect_right(subseg_addrs, addr) - 1
    if idx >= 0:
        return subseg_ranges[idx][1]
    return "<unknown>"

def print_per_file(result, sym_to_source, subseg_ranges, verbose=False,
                   show_code=True, show_data=True):
    """Show per-source-file progress."""
    files = {}  # source -> {"named": [], "auto": [], "non_matching": []}

    subseg_addrs = [va for va, _ in subseg_ranges]

    def add_to_file(name, addr, category):
        source = lookup_source(name, addr, sym_to_source, subseg_ranges, subseg_addrs)
        if source not in files:
            files[source] = {"named": [], "auto": [], "non_matching": []}
        files[source][category].append((name, addr))

    if show_code:
        for name, addr in result["functions"]["named"]:
            add_to_file(name, addr, "named")
        for name, addr in result["functions"]["auto"]:
            add_to_file(name, addr, "auto")
        for name, addr in result["functions"]["non_matching"]:
            add_to_file(name, addr, "non_matching")

    if show_data:
        for name, addr in result["data"]["named"]:
            add_to_file(name, addr, "named")
        for name, addr in result["data"]["auto"]:
            add_to_file(name, addr, "auto")
        for name, addr in result["data"]["non_matching"]:
            add_to_file(name, addr, "non_matching")

    # Sort files by name, but put <unknown> last
    sorted_files = sorted(files.keys(), key=lambda s: (s == "<unknown>", s))

    # Find longest filename for alignment
    max_name = max(len(s) for s in sorted_files)
    col = max(max_name + 2, 20)

    print(f"\n=== Per-file progress ===")

    for source in sorted_files:
        if any(source.startswith(p) for p in SKIP_SOURCES):
            continue
        f = files[source]
        named = len(f["named"])
        auto = len(f["auto"])
        total = named + auto
        if total == 0:
            continue
        pct = named / total * 100
        nm = len(f["non_matching"])
        nm_str = f"  nm:{nm}" if nm else ""
        print(f"  {source:{col}s}{named:>4}/{total:<4}  ({pct:5.1f}%)  {print_bar(pct / 100)}{nm_str}")

        if verbose and (f["auto"] or f["non_matching"]):
            for name, addr in sorted(f["auto"], key=lambda x: x[1]):
                print(f"    0x{addr:08X}  {name}")
            for name, addr in sorted(f["non_matching"], key=lambda x: x[1]):
                print(f"    0x{addr:08X}  {name}  (non-matching)")

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
    parser.add_argument(
        "--code", action="store_true",
        help="Only show function progress"
    )
    parser.add_argument(
        "--data", action="store_true",
        help="Only show data progress"
    )
    parser.add_argument(
        "--sym-txt", default=None,
        help="Path to splat sym.txt (auto-detected if not given)"
    )
    parser.add_argument(
        "--config-yaml", default=None,
        help="Path to splat config YAML (auto-detected if not given)"
    )
    args = parser.parse_args()

    result = parse_elf_symbols(args.elf_path, base_filter=not args.no_filter)

    fn = result["functions"]
    dt = result["data"]

    # If neither --code nor --data, show both
    show_code = args.code or not args.data
    show_data = args.data or not args.code

    total_all = 0
    named_all = 0
    nm_all = 0
    if show_code:
        total_all += len(fn["named"]) + len(fn["auto"])
        named_all += len(fn["named"])
        nm_all += len(fn["non_matching"])
    if show_data:
        total_all += len(dt["named"]) + len(dt["auto"])
        named_all += len(dt["named"])
        nm_all += len(dt["non_matching"])

    if total_all == 0:
        print("No matching symbols found in ELF.")
        sys.exit(1)

    pct_all = named_all / total_all * 100

    print(f"ELF: {args.elf_path}")
    print()
    print(f"=== Overall ===")
    print(f"  {'Total symbols:':16s}{total_all:>5}")
    print(f"  {'Named:':16s}{named_all:>5}  ({pct_all:5.1f}%)  {print_bar(pct_all / 100)}")
    print(f"  {'Auto-generated:':16s}{total_all - named_all:>5}  ({100 - pct_all:5.1f}%)")

    if nm_all:
        print(f"  {'Non-matching:':16s}{nm_all:>5}")

    if show_code:
        print(f"\n=== Functions ===")
        print_category("Functions", fn["named"], fn["auto"], fn["non_matching"])

    if show_data:
        print(f"\n=== Data ===")
        print_category("Data", dt["named"], dt["auto"], dt["non_matching"])

    sym_txt = args.sym_txt or find_sym_txt(args.elf_path)
    if sym_txt is None:
        print(f"\nCould not find sym.txt for {args.elf_path}")
        print("Use --sym-txt to specify the path manually.")
        sys.exit(1)

    config_yaml = args.config_yaml or find_config_yaml(args.elf_path)
    if config_yaml is None:
        print(f"\nCould not find config YAML for {args.elf_path}")
        print("Use --config-yaml to specify the path manually.")
        sys.exit(1)

    if args.verbose:
        print(f"\nsym.txt: {sym_txt}")
        print(f"config:  {config_yaml}")
    sym_to_source = parse_sym_txt(sym_txt)
    subseg_ranges = parse_config_yaml(config_yaml)
    print_per_file(result, sym_to_source, subseg_ranges,
                    verbose=args.verbose, show_code=show_code, show_data=show_data)


if __name__ == "__main__":
    main()
