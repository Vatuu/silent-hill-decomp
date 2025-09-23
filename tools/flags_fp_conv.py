#!/usr/bin/env python3

# Converts `g_SavegamePtr->eventFlags_168[X] & Y` expressions to `Savegame_EventFlagGet(Z)`
# Also converts Q12 integers (0x7CCC, -0x1444, 0xFFFE0DDD, 4096) into float equivalents (may need to be rounded afterward)

import re

# ---------- EventFlags converter ----------
def bit_index(mask):
    """Convert a mask like 8 (0b1000) to its bit index (3)."""
    if mask == 0:
        raise ValueError("Mask cannot be zero")
    index = 0
    while mask > 1:
        mask >>= 1
        index += 1
    return index

def convert_flag_expression(expr):
    """
    Converts:
        g_SavegamePtr->eventFlags_168[2] & 8
        g_SavegamePtr->eventFlags_168[2] & 0x8
        g_SavegamePtr->eventFlags_168[2] & (1 << 3)
        temp_a0->eventFlags_168[2] & [...]
    into Savegame_EventFlagGet(final_index)
    """
    # Pattern for decimal or hex mask
    pattern_literal = r'.*?eventFlags_168\[(\d+)\]\s*&\s*(0x[0-9a-fA-F]+|\d+)'
    # Pattern for bit shift
    pattern_shift = r'.*?eventFlags_168\[(\d+)\]\s*&\s*\(\s*1\s*<<\s*(\d+)\s*\)'

    match_shift = re.search(pattern_shift, expr)
    if match_shift:
        array_idx = int(match_shift.group(1))
        bit_idx = int(match_shift.group(2))
    else:
        match_literal = re.search(pattern_literal, expr)
        if not match_literal:
            return None  # not an eventFlags expression
        array_idx = int(match_literal.group(1))
        mask_str = match_literal.group(2)
        mask = int(mask_str, 0)  # handles decimal and hex
        bit_idx = bit_index(mask)
    
    final_idx = array_idx * 32 + bit_idx
    return f"Savegame_EventFlagGet({final_idx})"

# ---------- FP converter ----------
def to_signed(val, bits=32):
    """Convert unsigned int to signed (two's complement)."""
    if val & (1 << (bits - 1)):
        val -= 1 << bits
    return val

def convert_value(match):
    value_str = match.group(0)

    if value_str.startswith(("0x", "-0x", "+0x")):
        val = int(value_str, 16)
        if value_str.startswith("-0x"):
            val = -int(value_str[3:], 16)
        elif value_str.startswith("+0x"):
            val = int(value_str[3:], 16)
        else:
            val = to_signed(val, 32)
    else:
        val = int(value_str, 10)

    return str(val / 4096.0) + "f"

def process_fp_text(text):
    pattern = re.compile(r'[-+]?0x[0-9A-Fa-f]+|[-+]?\d+')
    return pattern.sub(convert_value, text)

# ---------- Unified REPL ----------
if __name__ == "__main__":
    print("Enter expressions like '(g_SavegamePtr->eventFlags_168[2] & 8)' or '(g_SavegamePtr->eventFlags_168[2] & (1 << 3))'.")
    print("Or enter decimal/hexadecimal Q12 numbers (0x7CCC, -0x1444, 0xFFFE0DDD) to convert to float")
    print("Type 'exit' to quit.")
    while True:
        try:
            line = input("> ").strip()
        except EOFError:
            break
        if line.lower() in ("quit", "exit"):
            break
        if not line:
            continue

        # Try eventFlags conversion first
        result = convert_flag_expression(line)
        if result is not None:
            print(result)
        else:
            # fallback to FP converter
            print(process_fp_text(line))
