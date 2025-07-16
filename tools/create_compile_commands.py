import json
import os
import shlex
import sys

# Usage: create_compile_commands.py [root_dir]
# Generates compile_commands.json for use with clangd in VSCode, to enable features like "go to definition".
#
# Run "make clean && make check MAKE_COMPILE_LOG=1", once that has finished run "python tools/create_compile_commands.py"
# After that just restart VSCode, and hopefully the compile_commands.json should take effect.
#
# Note:
# If running this from a different machine/VM than the one where VSCode is running
# You'll need to provide path where the source code is accessible from VSCode as the optional [root_dir] argument.
# (eg. "python create_compile_commands.py S:\\shdecomp")

root_dir = sys.argv[1] if len(sys.argv) > 1 else os.getcwd()
root_dir = root_dir.replace("\\", "/")

def convert_line(line):
    parts = shlex.split(line.strip())

    # Replace compiler
    parts[0] = "clang"

    # Remove unwanted flags
    skip_flags = {"-P", "-MMD", "-MP", "-MT", "-MF"}
    cleaned = []
    skip_next = False
    for i, part in enumerate(parts):
        if skip_next:
            skip_next = False
            continue
        if part in skip_flags:
            skip_next = True
            continue
        cleaned.append(part)

    # Find source file (assumes it’s the last .c file)
    src_file = next((p for p in reversed(cleaned) if p.endswith(".c")), None)
    if not src_file:
        return None

    return {
        "directory": root_dir,
        "file": src_file,
        "command": " ".join(cleaned)
    }

with open("compile.log") as f:
    entries = [convert_line(line) for line in f if line.strip()]
    entries = [e for e in entries if e is not None]

with open("compile_commands.json", "w") as out:
    json.dump(entries, out, indent=2)
