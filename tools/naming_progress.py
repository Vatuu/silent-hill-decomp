#!/usr/bin/env python3

# Usage:
#   tools/naming_progress.py <elf path> [--verbose] [--code] [--data] [--html outfile.html]
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
# --html [outfile.html] will generate a HTML file that can be browsed through.
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
import json
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

def build_report_data(result, sym_to_source, subseg_ranges):
    """Build a JSON-serializable report structure."""
    files = {}
    subseg_addrs = [va for va, _ in subseg_ranges]

    def add(name, addr, category, kind):
        source = lookup_source(name, addr, sym_to_source, subseg_ranges, subseg_addrs)
        if source not in files:
            files[source] = {"funcs": {"named": [], "auto": [], "non_matching": []},
                             "data": {"named": [], "auto": [], "non_matching": []}}
        files[source][kind][category].append({"name": name, "addr": f"0x{addr:08X}"})

    for name, addr in result["functions"]["named"]:
        add(name, addr, "named", "funcs")
    for name, addr in result["functions"]["auto"]:
        add(name, addr, "auto", "funcs")
    for name, addr in result["functions"]["non_matching"]:
        add(name, addr, "non_matching", "funcs")
    for name, addr in result["data"]["named"]:
        add(name, addr, "named", "data")
    for name, addr in result["data"]["auto"]:
        add(name, addr, "auto", "data")
    for name, addr in result["data"]["non_matching"]:
        add(name, addr, "non_matching", "data")

    file_list = []
    for source, cats in sorted(files.items(), key=lambda s: (s[0] == "<unknown>", s[0])):
        if any(source.startswith(p) for p in SKIP_SOURCES):
            continue
        fn, dt = cats["funcs"], cats["data"]
        file_list.append({
            "name": source,
            "funcs": fn,
            "data": dt,
        })

    fn = result["functions"]
    dt = result["data"]
    return {
        "summary": {
            "functions": {
                "named": len(fn["named"]),
                "auto": len(fn["auto"]),
                "non_matching": len(fn["non_matching"]),
            },
            "data": {
                "named": len(dt["named"]),
                "auto": len(dt["auto"]),
                "non_matching": len(dt["non_matching"]),
            },
        },
        "files": file_list,
    }

def generate_html(report_data, elf_path, output_path):
    """Generate a self-contained HTML report."""
    html = HTML_TEMPLATE.replace("__REPORT_DATA__", json.dumps(report_data))
    html = html.replace("__ELF_PATH__",os.path.splitext(os.path.basename(elf_path))[0])
    with open(output_path, "w") as f:
        f.write(html)
    print(f"HTML report written to {output_path}")

HTML_TEMPLATE = r"""<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Decomp Progress - __ELF_PATH__</title>
<style>
  body {
    font-family: Verdana, Tahoma, Geneva, sans-serif;
    font-size: 12px;
    background: #eef1f5;
    color: #333;
    margin: 0;
    padding: 20px;
  }
  a { color: #2654a1; }
  .container { max-width: 960px; margin: 0 auto; }

  /* Header bar */
  .header {
    background: #3c5a99;
    background: linear-gradient(to bottom, #4a6fb5, #35507a);
    color: #fff;
    padding: 10px 16px;
    border-radius: 4px 4px 0 0;
    border: 1px solid #2d4470;
    border-bottom: none;
  }
  .header h1 {
    font-size: 15px;
    font-weight: bold;
    margin: 0;
  }
  .header .path {
    font-size: 11px;
    color: #c0cce0;
    margin-top: 2px;
    font-family: 'Courier New', Courier, monospace;
  }

  /* Main panel */
  .panel {
    background: #fff;
    border: 1px solid #b0b8c4;
    border-radius: 0 0 4px 4px;
    padding: 16px;
    margin-bottom: 16px;
  }

  /* Summary boxes */
  .summary-row {
    display: flex;
    gap: 12px;
    margin-bottom: 16px;
  }
  .stat-box {
    flex: 1;
    background: #f7f8fa;
    border: 1px solid #d0d5dd;
    border-radius: 3px;
    padding: 10px 12px;
  }
  .stat-box h3 {
    font-size: 11px;
    font-weight: bold;
    color: #555;
    text-transform: uppercase;
    margin: 0 0 6px 0;
    border-bottom: 1px solid #e0e3e8;
    padding-bottom: 4px;
  }
  .stat-line {
    font-size: 11px;
    line-height: 1.7;
  }
  .stat-line .num { font-weight: bold; color: #222; }
  .stat-pct {
    font-size: 18px;
    font-weight: bold;
    margin: 4px 0;
  }
  .stat-pct.good { color: #2e7d32; }
  .stat-pct.mid  { color: #e67c00; }
  .stat-pct.low  { color: #c62828; }
  .stat-bar-outer {
    height: 10px;
    background: #dde0e6;
    border-radius: 2px;
    overflow: hidden;
    margin-top: 6px;
    border: 1px solid #c8ccd2;
  }
  .stat-bar-fill {
    height: 100%;
    border-radius: 1px;
    transition: width 0.3s;
  }

  /* Controls row */
  .controls {
    display: flex;
    align-items: center;
    gap: 6px;
    margin-bottom: 10px;
    flex-wrap: wrap;
    font-size: 11px;
  }
  .controls label {
    color: #666;
    margin-right: 2px;
  }
  .btn {
    font-family: Verdana, Tahoma, sans-serif;
    font-size: 11px;
    padding: 3px 9px;
    border: 1px solid #a0a8b4;
    border-radius: 3px;
    background: linear-gradient(to bottom, #fff, #e8ecf0);
    color: #333;
    cursor: pointer;
  }
  .btn:hover {
    background: linear-gradient(to bottom, #f0f4f8, #dde2e8);
    border-color: #808890;
  }
  .btn.active {
    background: linear-gradient(to bottom, #5a7db5, #3c5a8a);
    border-color: #2d4470;
    color: #fff;
  }
  .search-box {
    font-family: Verdana, Tahoma, sans-serif;
    font-size: 11px;
    padding: 3px 7px;
    border: 1px solid #a0a8b4;
    border-radius: 3px;
    width: 180px;
    margin-left: auto;
  }
  .search-box:focus { outline: none; border-color: #4a6fb5; }

  /* File table */
  table.files {
    width: 100%;
    border-collapse: collapse;
    font-size: 11px;
  }
  table.files th {
    text-align: left;
    padding: 5px 8px;
    background: #e8ecf0;
    border: 1px solid #c8ccd2;
    font-size: 10px;
    font-weight: bold;
    color: #555;
    text-transform: uppercase;
  }
  table.files td {
    padding: 4px 8px;
    border: 1px solid #d8dce2;
  }
  table.files tr.file-row { cursor: pointer; }
  table.files tr.file-row:hover { background: #f0f4fa; }
  table.files tr.file-row:nth-child(odd) { background: #fafbfc; }
  table.files tr.file-row:nth-child(odd):hover { background: #f0f4fa; }
  .fname {
    font-family: 'Courier New', Courier, monospace;
    font-weight: bold;
    font-size: 11px;
    color: #2654a1;
    white-space: nowrap;
  }
  .ratio { font-family: 'Courier New', Courier, monospace; }
  .pct { font-weight: bold; }
  .pct-good { color: #2e7d32; }
  .pct-mid  { color: #e67c00; }
  .pct-low  { color: #c62828; }
  .bar-cell { width: 200px; }
  .bar-outer {
    height: 10px;
    background: #dde0e6;
    border: 1px solid #c8ccd2;
    border-radius: 2px;
    overflow: hidden;
  }
  .bar-fill { height: 100%; border-radius: 1px; }
  .nm-cell {
    font-family: 'Courier New', Courier, monospace;
    color: #e67c00;
    font-weight: bold;
    text-align: center;
  }
  .chevron {
    display: inline-block;
    width: 10px;
    font-size: 9px;
    color: #999;
    margin-right: 4px;
    transition: transform 0.1s;
  }
  tr.file-row.open .chevron { transform: rotate(90deg); }

  /* Detail rows */
  tr.detail-row { display: none; }
  tr.detail-row.open { display: table-row; }
  tr.detail-row td {
    padding: 6px 8px 8px 28px;
    background: #f4f5f8;
    border: 1px solid #d8dce2;
  }
  .detail-heading {
    font-size: 10px;
    font-weight: bold;
    color: #666;
    text-transform: uppercase;
    margin: 6px 0 3px 0;
    border-bottom: 1px dotted #c8ccd2;
    padding-bottom: 2px;
  }
  .detail-heading:first-child { margin-top: 0; }
  .sym-row {
    font-family: 'Courier New', Courier, monospace;
    font-size: 11px;
    line-height: 1.6;
    color: #444;
  }
  .sym-row .addr { color: #888; }
  .sym-row .name { color: #222; }
  .tag {
    font-family: Verdana, sans-serif;
    font-size: 9px;
    font-weight: bold;
    padding: 1px 5px;
    border-radius: 2px;
    margin-left: 6px;
  }
  .tag-auto { background: #fde8e8; color: #c62828; border: 1px solid #f5c0c0; }
  .tag-nm   { background: #fff3d4; color: #b87000; border: 1px solid #f0d890; }
  .tag-func { background: #e0ecf8; color: #2654a1; border: 1px solid #b0c8e8; }
  .tag-data { background: #eee8f8; color: #6a40a0; border: 1px solid #c8b8e0; }

  .empty-detail {
    font-style: italic;
    color: #999;
    font-size: 11px;
  }

  .footer {
    text-align: center;
    font-size: 10px;
    color: #999;
    margin-top: 12px;
  }
</style>
</head>
<body>
<div class="container">
  <div class="header">
    <h1>Decomp Naming Progress: __ELF_PATH__</h1>
  </div>
  <div class="panel">
    <div class="summary-row" id="summary"></div>
    <div class="controls">
      <label>Show:</label>
      <button class="btn active" data-filter="all">All</button>
      <button class="btn" data-filter="code">Functions</button>
      <button class="btn" data-filter="data">Data</button>
      <span style="color:#aaa;margin:0 4px">|</span>
      <label>Sort:</label>
      <button class="btn active" data-sort="name">Name</button>
      <button class="btn" data-sort="pct-asc">% Asc</button>
      <button class="btn" data-sort="pct-desc">% Desc</button>
      <button class="btn" data-sort="remaining">Remaining</button>
      <input class="search-box" type="text" placeholder="Filter files..." id="searchInput">
    </div>
    <div id="fileTable"></div>
  </div>
  <div class="footer">generated by naming_progress.py</div>
</div>
<script>
const DATA = __REPORT_DATA__;

function pctClass(p) { return p >= 75 ? 'good' : p >= 40 ? 'mid' : 'low'; }
function barColor(p) { return p >= 75 ? '#5a9e5f' : p >= 40 ? '#e6a817' : '#c84040'; }

function makeStatBox(label, named, auto, nm) {
  const total = named + auto;
  const pct = total ? (named / total * 100) : 0;
  const pc = pctClass(pct);
  const bc = barColor(pct);
  return `<div class="stat-box">
    <h3>${label}</h3>
    <div class="stat-pct ${pc}">${pct.toFixed(1)}%</div>
    <div class="stat-line"><span class="num">${named}</span> / ${total} named</div>
    <div class="stat-line">${auto} auto-generated</div>
    ${nm ? `<div class="stat-line" style="color:#e67c00">${nm} non-matching</div>` : ''}
    <div class="stat-bar-outer"><div class="stat-bar-fill" style="width:${pct}%;background:${bc}"></div></div>
  </div>`;
}

const S = DATA.summary;
const allN = S.functions.named + S.data.named;
const allA = S.functions.auto + S.data.auto;
const allNM = S.functions.non_matching + S.data.non_matching;
document.getElementById('summary').innerHTML =
  makeStatBox('Overall', allN, allA, allNM) +
  makeStatBox('Functions', S.functions.named, S.functions.auto, S.functions.non_matching) +
  makeStatBox('Data', S.data.named, S.data.auto, S.data.non_matching);

let currentFilter = 'all';
let currentSort = 'name';

function getCounts(f, filter) {
  let named = 0, auto = 0, nm = 0, autoList = [], nmList = [];
  if (filter !== 'data') {
    named += f.funcs.named.length;
    auto += f.funcs.auto.length;
    nm += f.funcs.non_matching.length;
    autoList = autoList.concat(f.funcs.auto.map(s => ({...s, kind: 'func', tag: 'auto'})));
    nmList = nmList.concat(f.funcs.non_matching.map(s => ({...s, kind: 'func', tag: 'nm'})));
  }
  if (filter !== 'code') {
    named += f.data.named.length;
    auto += f.data.auto.length;
    nm += f.data.non_matching.length;
    autoList = autoList.concat(f.data.auto.map(s => ({...s, kind: 'data', tag: 'auto'})));
    nmList = nmList.concat(f.data.non_matching.map(s => ({...s, kind: 'data', tag: 'nm'})));
  }
  return { named, auto, nm, total: named + auto, autoList, nmList };
}

function renderTable() {
  const search = document.getElementById('searchInput').value.toLowerCase();

  let files = DATA.files.map(f => {
    const c = getCounts(f, currentFilter);
    return { ...f, ...c };
  }).filter(f => f.total > 0 && f.name.toLowerCase().includes(search));

  if (currentSort === 'name') files.sort((a, b) => a.name.localeCompare(b.name));
  else if (currentSort === 'pct-asc') files.sort((a, b) => (a.named/a.total) - (b.named/b.total));
  else if (currentSort === 'pct-desc') files.sort((a, b) => (b.named/b.total) - (a.named/a.total));
  else if (currentSort === 'remaining') files.sort((a, b) => b.auto - a.auto);

  let html = `<table class="files">
    <tr><th>File</th><th>Progress</th><th>%</th><th class="bar-cell">Bar</th><th>NM</th></tr>`;

  files.forEach((f, i) => {
    const pct = f.total ? (f.named / f.total * 100) : 0;
    const pc = 'pct-' + pctClass(pct);
    const bc = barColor(pct);

    html += `<tr class="file-row" data-idx="${i}" onclick="toggleDetail(${i})">
      <td class="fname"><span class="chevron">&#9654;</span>${f.name}</td>
      <td class="ratio">${f.named}/${f.total}</td>
      <td class="pct ${pc}">${pct.toFixed(1)}%</td>
      <td class="bar-cell"><div class="bar-outer"><div class="bar-fill" style="width:${pct}%;background:${bc}"></div></div></td>
      <td class="nm-cell">${f.nm || ''}</td>
    </tr>`;

    const syms = f.autoList.concat(f.nmList).sort((a, b) => a.addr.localeCompare(b.addr));
    html += `<tr class="detail-row" data-detail="${i}"><td colspan="5">`;
    if (syms.length === 0) {
      html += `<div class="empty-detail">All symbols have been named.</div>`;
    } else {
      const autoFuncs = syms.filter(s => s.tag === 'auto' && s.kind === 'func');
      const autoData  = syms.filter(s => s.tag === 'auto' && s.kind === 'data');
      const nmFuncs   = syms.filter(s => s.tag === 'nm'   && s.kind === 'func');
      const nmData    = syms.filter(s => s.tag === 'nm'   && s.kind === 'data');

      function renderGroup(label, items, tagClass, tagLabel) {
        if (!items.length) return '';
        let out = `<div class="detail-heading">${label} (${items.length})</div>`;
        items.forEach(s => {
          out += `<div class="sym-row">
            <span class="addr">${s.addr}</span>&nbsp;
            <span class="name">${s.name}</span>
            <span class="tag tag-${s.kind}">${s.kind}</span>
            <span class="tag ${tagClass}">${tagLabel}</span>
          </div>`;
        });
        return out;
      }

      html += renderGroup('Auto-generated functions', autoFuncs, 'tag-auto', 'auto');
      html += renderGroup('Auto-generated data', autoData, 'tag-auto', 'auto');
      html += renderGroup('Non-matching functions', nmFuncs, 'tag-nm', 'non-matching');
      html += renderGroup('Non-matching data', nmData, 'tag-nm', 'non-matching');
    }
    html += `</td></tr>`;
  });

  html += '</table>';
  document.getElementById('fileTable').innerHTML = html;
}

function toggleDetail(idx) {
  const row = document.querySelector(`tr.file-row[data-idx="${idx}"]`);
  const detail = document.querySelector(`tr.detail-row[data-detail="${idx}"]`);
  row.classList.toggle('open');
  detail.classList.toggle('open');
}

document.querySelectorAll('.btn[data-filter]').forEach(btn => {
  btn.addEventListener('click', () => {
    document.querySelectorAll('.btn[data-filter]').forEach(b => b.classList.remove('active'));
    btn.classList.add('active');
    currentFilter = btn.dataset.filter;
    renderTable();
  });
});

document.querySelectorAll('.btn[data-sort]').forEach(btn => {
  btn.addEventListener('click', () => {
    document.querySelectorAll('.btn[data-sort]').forEach(b => b.classList.remove('active'));
    btn.classList.add('active');
    currentSort = btn.dataset.sort;
    renderTable();
  });
});

document.getElementById('searchInput').addEventListener('input', renderTable);
renderTable();
</script>
</body>
</html>"""

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
        "--html", default=None, metavar="OUTPUT",
        help="Generate HTML report (requires sym.txt + config yaml)"
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

    if args.html:
        sym_txt = args.sym_txt or find_sym_txt(args.elf_path)
        config_yaml = args.config_yaml or find_config_yaml(args.elf_path)
        if sym_txt is None or config_yaml is None:
            missing = []
            if sym_txt is None:
                missing.append("sym.txt (use --sym-txt)")
            if config_yaml is None:
                missing.append("config YAML (use --config-yaml)")
            print(f"\nCannot generate HTML: missing {', '.join(missing)}")
            sys.exit(1)
        sym_to_source = parse_sym_txt(sym_txt)
        subseg_ranges = parse_config_yaml(config_yaml)
        report = build_report_data(result, sym_to_source, subseg_ranges)
        generate_html(report, args.elf_path, args.html)


if __name__ == "__main__":
    main()
