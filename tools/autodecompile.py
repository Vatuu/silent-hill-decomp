#!/usr/bin/env python3

# Usage: `autodecompile.py [filters]`
# Filters can be any directory/filename required to be in the path, eg 'bodyprog/' or 'map7_s01/'
# Only files whose path contains all filters are attempted for decompile.
# 
# Script will try running decompile.py on each function, which uses m2ctx/m2c to decompile the function & inserts the decompilation into the C to check for match
# If the func matches it will be printed out at the end, and will also be logged into `build/autodecompile.log`
# The log can be viewed live via `tail -f build/autodecompile.log`
# 
# After each decompilation attempt `git restore` will be ran to restore the repo.
# This will also be ran after all attempts have finished.
# If `--stage` argument is provided, each matching decompilation will be staged with `git add`
# Once script finishes it will list out each func that can be m2c decompiled.

import os
import sys
import subprocess
from pathlib import Path

# Ensure running from repo root
cwd = Path.cwd()
if not (cwd / "asm").is_dir() or not (cwd / "src").is_dir():
    print("Error: Must run from the repo root (both 'asm/' and 'src/' directories must exist in the current working directory).")
    print("Change directory to repo and run `tools/autodecompile.py`")
    sys.exit(1)

import decompile
import argparse

ASM_PATH = Path("asm/")
SUCCESS_LOG = Path("build/autodecompile.log")

def find_functions(filters):
    """
    Recursively find all func_* and sharedFunc_* files under ASM_PATH that match all filters.
    """
    funcs = []
    for path in ASM_PATH.rglob("*"):  # check all files
        if path.is_file() and path.suffix in (".s", ".asm"):
            path_str = str(path)
            if any(prefix in path_str for prefix in ("func_", "sharedFunc_")):
                if "nonmatchings" in path_str:
                    if all(f in path_str for f in filters):
                        func_name = path.stem
                        funcs.append((func_name, path))
    return funcs

def try_decompile(func_name: str, func_path: Path = None):
    """Try to decompile one function and log success if it works."""
    subprocess.run(["git", "restore", "src/"], check=False)
    # Clear build folders for everything except main EXE, faster than using make clean, and we keep main intact for quicker build iterations
    subprocess.run(["rm", "-rf", "build/asm/bodyprog", "build/asm/maps", "build/asm/screens", "build/out/1ST", "build/out/VIN", "build/src/bodyprog", "build/src/maps", "build/src/screens"], check=False) # faster than make clean
    try:
        result = decompile.decompile(str(func_path.resolve()), force=True, resolve_jtbl=False)
    except Exception as e:
        print(f"Error while decompiling {func_name}: {e}")
        result = decompile.InjectRes.UNKNOWN_ERROR
        return False

    if result == decompile.InjectRes.SUCCESS:
        with open(SUCCESS_LOG, "a") as f:
            f.write(f"{func_name} | {func_path or '(manual)'}\n")
        print(f"Logged success for {func_name}")
        return True
    return False

def has_unstaged_changes(path="src/"):
    try:
        # This returns 0 if no unstaged changes, 1 if there are
        subprocess.run(
            ["git", "diff", "--quiet", path],
            check=True
        )
        return False
    except subprocess.CalledProcessError:
        return True

def main():
    parser = argparse.ArgumentParser(description="Automatically try decompile functions with optional path filters")
    parser.add_argument(
        "filters",
        nargs="*",
        help="Filters, eg 'bodyprog/' or 'map7_s01/'. Only files whose path contains all filters are included.",
    )
    parser.add_argument(
        "--stage",
        action="store_true",
        help="If set, keeps each matching decompilation by staging with `git add`"
    )
    args = parser.parse_args()

    filters = args.filters

    if not filters:
        parser.print_help()
        print("\nerror: at least one filter must be provided (e.g. 'bodyprog/' or 'map7_s01/')\n")
        return

    # Prevent running if any unstaged changes in src/, since this would destroy them.
    if has_unstaged_changes("src/"):
        print("\nerror: unstaged changes in src/, stage or stash them first.")
        return

    if args.stage:
        print("\nwarning: --stage mode enabled, staged funcs may cause later decompiled funcs to mismatch.")

    # Speedup by skipping the separate overlay-only build and only run `make check`
    decompile.only_make_check = True

    print("\nRunning `make check`...")
    check_result = subprocess.run(
        "make check", shell=True, check=False, capture_output=True
    )
    if check_result.returncode != 0:
        print("\nerror: `make check` failed, repo not clean? exiting")
        return

    print("\nStarting autodecompilation")
    print("(will run `git restore` after each attempt - don't modify repo!)")

    # --- 2. Batch mode ---
    funcs = find_functions(filters)
    print(f"\nFound {len(funcs)} functions to decompile")
    print("Will write successes to build/autodecompile.log")
    print("(`tail -f build/autodecompile.log` to view live)")
    print()
    succeeded_paths = []

    count = 0
    for func_name, func_path in funcs:
        print(f"=== ({count+1}/{len(funcs)}) Decompiling {'/'.join(func_path.parts[-2:])} ===")
        count = count + 1
        if try_decompile(func_name, func_path):
            succeeded_paths.append(func_path)
            if args.stage:
                subprocess.run(["git", "add", "src/"], check=False)
        print()

    # restore src after all attempts
    subprocess.run(["git", "restore", "src/"], check=False)

    # summary
    print(f"\nAutodecompiled {len(succeeded_paths)}/{len(funcs)} functions:")

    if succeeded_paths:
        for path in sorted(succeeded_paths, key=lambda p: str(p)):
            print(f"  {path}")

        print("\nLog written to build/autodecompile.log")
        if args.stage:
            print("Matching funcs have been staged with `git add`, can be unstaged with `git restore --staged`")
            print("Recommend fixing up and `git clang-format` before committing.")

if __name__ == "__main__":
    main()
