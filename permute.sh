#!/bin/bash

# Function to display usage
usage() {
    echo "Usage: $0 [--clean] [--run] FUNCTION_NAME ASM_FUNCTION C_FUNCTION"
    echo "ASM_FUNCTION is the .s file from asm/../nonmatching folder"
    echo "C_FUNCTION file should contain just the function and related includes"
    exit 1
}

# Initialize flags
CLEAN=false
RUN=false

# Parse flags
while [[ "$1" == "--clean" || "$1" == "--run" ]]; do
    if [ "$1" == "--clean" ]; then
        CLEAN=true
    elif [ "$1" == "--run" ]; then
        RUN=true
    fi
    shift
done

# Get the parameters
FUNCTION_NAME=$1
ASM_FUNCTION=$2
C_FUNCTION=$3

# Validate parameters
if [ -z "$FUNCTION_NAME" ] || [ -z "$ASM_FUNCTION" ] || [ -z "$C_FUNCTION" ]; then
    usage
fi

# Get the path to the current script's directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Clean the directory if the --clean flag is set
if [ "$CLEAN" = true ]; then
    echo "Cleaning directory: permuter/$FUNCTION_NAME"
    rm -rf permuter/$FUNCTION_NAME
fi

echo "Creating directory: permuter/$FUNCTION_NAME"
mkdir -p permuter/$FUNCTION_NAME

echo "Creating settings.toml file"
{
    echo "func_name = \"$FUNCTION_NAME\""
    cat permute_defaults.toml
} > permuter/$FUNCTION_NAME/settings.toml

echo "Creating compile.sh file"
{
    echo '#!/usr/bin/env bash'
    echo 'INPUT="$(realpath "$1")"'
    echo 'INPUT_I=$INPUT.i'
    echo 'INPUT_D=$INPUT_I.d'
    echo 'INPUT_S=$INPUT_I.s'
    echo ''
    echo 'OUTPUT="$(realpath "$3")"'
    echo ''
    echo "cd $SCRIPT_DIR"
    echo ''
    echo 'mips-linux-gnu-cpp -P -MMD -MP -MT "$INPUT_I" -MF "$INPUT_D" -Iinclude -Iinclude/psyq -I build -D_LANGUAGE_C -DUSE_INCLUDE_ASM -P -MMD -MP -undef -Wall -lang-c -nostdinc -o "$INPUT_I" "$INPUT"'
    echo 'tools/gcc-2.8.1-psx/cc1 -O2 -mips1 -mcpu=3000 -w -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -mgas -fgnu-linker -quiet -G4 -o "$INPUT_S" "$INPUT_I"'
    echo 'python3 tools/maspsx/maspsx.py --aspsx-version=2.77 --run-assembler -EL -Iinclude -Iinclude/psyq -I build -O2 -G4 -march=r3000 -mtune=r3000 -no-pad-sections -o "$OUTPUT" "$INPUT_S"'
} > permuter/$FUNCTION_NAME/compile.sh

chmod +x permuter/$FUNCTION_NAME/compile.sh

echo "Creating or overwriting permuter/$FUNCTION_NAME/target.s file from $ASM_FUNCTION"
{
    echo '.include "macro.inc"'
    echo ''
    echo ''
    cat $ASM_FUNCTION
} > permuter/$FUNCTION_NAME/target.s

echo "Preprocessing the C function $C_FUNCTION and saving to permuter/$FUNCTION_NAME/base.c"
gcc -E -P -Iinclude -Iinclude/psyq -DPERMUTER $C_FUNCTION > permuter/$FUNCTION_NAME/base.c

echo "Assembling the ASM function permuter/$FUNCTION_NAME/target.o"
mips-linux-gnu-as -EL -Iinclude -Iinclude/psyq -I build -O2 -march=r3000 -mtune=r3000 -no-pad-sections -G4 -o permuter/$FUNCTION_NAME/target.o permuter/$FUNCTION_NAME/target.s

# Run decomp-permuter if the --run flag is set
if [ "$RUN" = true ]; then
    echo "Running decomp-permuter"
    python3 tools/decomp-permuter/permuter.py -j2 --algorithm levenshtein permuter/$FUNCTION_NAME/
fi
