#!/usr/bin/env python3

# Converts `g_SavegamePtr->eventFlags_168[X]` expressions to `Savegame_EventFlagGet(Z)` / `Savegame_EventFlagSet` / `Savegame_EventFlagClear`
# Also converts Q format integers (0x7CCC, -0x1444, 0xFFFE0DDD, 4096) into float equivalents
# Q12 is used by default, but can be specified by including it in the line (`4096 Q8` or `Q8(0x1337)` to convert to Q8)
# May need to round the result afterward
# (mostly GPT written)

import re
import readline
import math
import os
import sys
import pyperclip

# ---------- EventFlags converter ----------
def _parse_mask(mask_str):
    """Strip integer suffixes (U/L) and parse mask as int."""
    mask_clean = re.sub(r'[uUlL]+$', '', mask_str)
    return int(mask_clean, 0)

def _bit_indices(mask, width=32):
    """Return list of bit indices (0..width-1) that are set in mask."""
    return [i for i in range(width) if (mask >> i) & 1]

def read_file(path):
    try:
        with open(path, 'r') as file:
            text = file.read()
            return text
    except Exception as e:
        print(f"Error reading {path}: {e}")
        return None

def parse_enum_header(path):
    """
    Parse a C enum definition and return a dict mapping values to names.
    """
    if not os.path.exists(path):
        print(f"Warning: file not found: {path}")
        return {}
    text = read_file(path)
    pattern = re.compile(r'\b([A-Za-z_]\w*)\s*=\s*(\d+)\s*,?')
    result = {}
    for match in pattern.finditer(text):
        name, value = match.groups()
        result[int(value)] = name
    return result

eventFlags = parse_enum_header("include/event_flags.h")
mapMarkings = parse_enum_header("include/bodyprog/map_marking_flags.h")

def get_flag_name(flagIdx, isMapMarking):
    flags = mapMarkings if isMapMarking else eventFlags
    enumName = "EventFlag_" if not isMapMarking else "MapMarkFlag_"
    return flags.get(flagIdx, f"{enumName}{flagIdx}")

def convert_pose(line):
    pattern = r"WorldObjectSet\(([^,]+),\s*([^,]+),\s*([^,]+),\s*([^,]+),\s*([^,]+),\s*([^,]+),\s*([^,]+),\s*([^\,\)]+)\)"
    m = re.search(pattern, line)
    if not m:
        return None

    def convert_value(value_str, is_fp_angle):
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

        if is_fp_angle:
            if val >= 0x8000:
                val = val - 0x10000
            return f"{round_fp(val, 11.377778)}"
        return f"{process_fp_raw(val, 12)}"


    obj = m.group(1).strip()

    # extract raw args
    name = m.group(2)
    a1, a2, a3 = m.group(3), m.group(4), m.group(5)
    a4, a5, a6 = m.group(6), m.group(7), m.group(8)

    # convert values
    f1 = convert_value(a1, False)
    f2 = convert_value(a2, False)
    f3 = convert_value(a3, False)

    f4 = convert_value(a4, True)
    f5 = convert_value(a5, True)
    f6 = convert_value(a6, True)

    return (
        f"WorldObjectInit({obj}, {name}, "
        f"{f1}, {f2}, {f3}, {f4}, {f5}, {f6});"
    )


def convert_flag_expression(expr):
    """
    Convert eventFlags_168 bit ops into Savegame_EventFlag* calls.
    Rules:
      - '|='  -> Savegame_EventFlagSet(...)
      - '&'   -> Savegame_EventFlagGet(...) (if mask has multiple bits -> OR-combined gets)
      - '&='  -> Savegame_EventFlagClear(...) 
                * if written as '&= ~mask' -> mask gives bits to clear
                * if written as '&= mask'  -> mask is already negated: bits to clear = ~mask & 0xFFFFFFFF
    Returns a string (single call or multiple calls joined).
    """
    arr_pat = r'.*?(?:eventFlags_168|mapMarkingFlags_1D4)\[(0x[0-9a-fA-F]+|\d+)\]'
    mask_pat  = r'(0x[0-9a-fA-F]+(?:[uUlL]*)|\d+)'
    shift_pat = r'\(?\s*1\s*<<\s*(\d+)\s*\)?'

    isMapMarking = "mapMarkingFlags_1D4" in expr

    flag_macro_name = "Savegame_EventFlag" if not isMapMarking else "Savegame_MapMarking"

    # `(eventFlags_168 & xx) == xx` -> Get and possibly !Get
    m = re.search(arr_pat + r'\s*\(?\s*&\s*' + mask_pat + r'\s*\)?\s*==\s*' + mask_pat, expr)
    if m:
        array_idx = int(m.group(1), 0)
        mask = _parse_mask(m.group(2))
        value = _parse_mask(m.group(3))
        conditions = []
        for bit in range(32):
            if mask & (1 << bit):
                final_idx = array_idx * 32 + bit
                if value & (1 << bit):
                    conditions.append(f"{flag_macro_name}Get({get_flag_name(final_idx, isMapMarking)})")
                else:
                    conditions.append(f"!{flag_macro_name}Get({get_flag_name(final_idx, isMapMarking)})")
        return " && ".join(conditions) if conditions else None

    # |= (shift)
    m = re.search(arr_pat + r'\s*\|\=\s*' + shift_pat, expr)
    if m:
        array_idx, bit_idx = int(m.group(1), 0), int(m.group(2))
        return f"{flag_macro_name}Set({get_flag_name(array_idx * 32 + bit_idx, isMapMarking)})"

    # |= (literal)
    m = re.search(arr_pat + r'\s*\|\=\s*' + mask_pat, expr)
    if m:
        array_idx = int(m.group(1), 0)
        mask = _parse_mask(m.group(2))
        indices = _bit_indices(mask)
        return '; '.join(f"{flag_macro_name}Set({get_flag_name(array_idx * 32 + i, isMapMarking)})" for i in indices) if indices else None

    # &= ~(shift)
    m = re.search(arr_pat + r'\s*\&\=\s*~' + shift_pat, expr)
    if m:
        array_idx, bit_idx = int(m.group(1), 0), int(m.group(2))
        return f"{flag_macro_name}Clear({get_flag_name(array_idx * 32 + bit_idx, isMapMarking)})"

    # &= ~(literal)
    m = re.search(arr_pat + r'\s*\&\=\s*~' + mask_pat, expr)
    if m:
        array_idx = int(m.group(1), 0)
        mask = _parse_mask(m.group(2))
        indices = _bit_indices(mask)
        return '; '.join(f"{flag_macro_name}Clear({get_flag_name(array_idx * 32 + i, isMapMarking)})" for i in indices) if indices else None

    # &= (literal WITHOUT ~) -> mask is the negated form; bits to clear are zeros in mask
    m = re.search(arr_pat + r'\s*\&\=\s*' + mask_pat, expr)
    if m:
        array_idx = int(m.group(1), 0)
        mask = _parse_mask(m.group(2))
        inverted = (~mask) & 0xFFFFFFFF
        indices = _bit_indices(inverted)
        return '; '.join(f"{flag_macro_name}Clear({get_flag_name(array_idx * 32 + i, isMapMarking)})" for i in indices) if indices else None

    # &= (shift WITHOUT ~) -> uncommon, but handle by inverting the single-bit mask
    m = re.search(arr_pat + r'\s*\&\=\s*' + shift_pat, expr)
    if m:
        array_idx, bit_idx = int(m.group(1), 0), int(m.group(2))
        inverted = (~(1 << bit_idx)) & 0xFFFFFFFF
        indices = _bit_indices(inverted)
        return '; '.join(f"{flag_macro_name}Clear({get_flag_name(array_idx * 32 + i, isMapMarking)})" for i in indices) if indices else None

    # & (shift) -> Get
    m = re.search(arr_pat + r'\s*\&\s*' + shift_pat, expr)
    if m:
        array_idx, bit_idx = int(m.group(1), 0), int(m.group(2))
        return f"{flag_macro_name}Get({get_flag_name(array_idx * 32 + bit_idx, isMapMarking)})"

    # & (literal) -> Get (if multiple bits -> OR them)
    m = re.search(arr_pat + r'\s*\&\s*' + mask_pat, expr)
    if m:
        array_idx = int(m.group(1), 0)
        mask = _parse_mask(m.group(2))
        indices = _bit_indices(mask)
        if not indices:
            return None
        if len(indices) == 1:
            return f"{flag_macro_name}Get({get_flag_name(array_idx * 32 + indices[0], isMapMarking)})"
        return ' || '.join(f"{flag_macro_name}Get({get_flag_name(array_idx * 32 + i, isMapMarking)})" for i in indices)

    return None

# ---------- FP converter ----------
def to_signed(val, bits=32):
    """Convert unsigned int to signed (two's complement)."""
    if val & (1 << (bits - 1)):
        val -= 1 << bits
    return val

def trim_float(x, digits=7):
    """Format to fixed decimals, then drop trailing zeros/dot."""
    res = f"{x:.{digits}f}".rstrip('0').rstrip('.')
    if "." not in res:
        res += ".0"
    return res

def round_fp(val, scale):
    float_val = val / scale;

    # Find shortest decimal that round-trips correctly
    found = False

    for digits in range(1, 12):
        rounded = round(float_val, digits)
        increment = 10 ** (-digits)

        # Test the rounded value and its nearest neighbor
        candidates = [rounded, rounded + (increment if float_val >= 0 else -increment)]

        for candidate in candidates:
            scaled = candidate * scale
            reconverted = int(math.floor(scaled)) if candidate >= 0 else int(math.ceil(scaled))
            if reconverted == val:
                float_val = trim_float(candidate)
                found = True
                break

        if found:
            break

    return f"{float_val}f"

def process_fp_raw(val, qval = 12):
    scale = (1 << qval)
    float_val = round_fp(val, scale)

    return f"{float_val}"

def process_fp(val, qval = 12):
    return f"Q{qval}({process_fp_raw(val, qval)})"

def process_fp_angle_packed(val):
    return f"FP_ANGLE_PACKED({round_fp(val, 0.711111)})"

def process_fp_angle(val):
    return f"FP_ANGLE({round_fp(val, 11.377778)})"

def process_fp_text(text):
    qval = 12  # default Q-format is Q12

    # detect and strip Q modifier
    match = re.search(r'\bQ(\d+)\b', text)
    if match:
        qval = int(match.group(1))
        text = re.sub(r'\bQ\d+\b', '', text, count=1)

    is_fp_angle_packed = False
    is_fp_angle = False
    if "FP_ANGLE_PACKED" in text:
        is_fp_angle_packed = True
        text = text.replace("FP_ANGLE_PACKED", "")
    elif "FP_ANGLE" in text:
        is_fp_angle = True
        text = text.replace("FP_ANGLE", "")

    def convert_value(match):
        prefix = match.group(1) or ""   # may be None if start-of-string
        value_str = match.group(2)

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

        if is_fp_angle:
            return f"{prefix}{process_fp_angle(val)}"
        if is_fp_angle_packed:
            return f"{prefix}{process_fp_angle_packed(val)}"
        return f"{prefix}{process_fp(val, qval)}"

    # prefix can be: start-of-string, space, or a punctuation
    pattern = re.compile(r'(^|[\s,(=:{\[])([-+]?0x[0-9A-Fa-f]+|[-+]?\d+)')
    return pattern.sub(convert_value, text)

# ---------- Unified REPL ----------
if __name__ == "__main__":
    if len(sys.argv) > 1:
        # Join all arguments into a single input string
        line = " ".join(sys.argv[1:]).strip()

        result = convert_flag_expression(line)
        if result is None:
            result = process_fp_text(line)

        if result is not None:
            print(result)
            pyperclip.copy(result)
        sys.exit(0)

    print("Enter expressions like 'g_SavegamePtr->eventFlags_168[2] & 8' or 'g_SavegamePtr->eventFlags_168[2] |= (1 << 3))'.")
    print("Or enter a line containing decimal/hexadecimal Q12 numbers (0x7CCC, -0x1444, 4096, 0xFFFE0DDD) to convert to float")
    print("(change to other Q** formats by including Q format in the text, 'chara.field_48 = Q8(-0x1999)'")
    print()
    print("Type 'exit' to quit.")
    while True:
        try:
            line = input("> ").strip()
        except EOFError:
            break
        if line.lower() in ("quit", "exit", "q"):
            break
        if not line:
            continue

        # Try eventFlags conversion first
        result = convert_flag_expression(line)
        if result is None:
            result = convert_pose(line)
            if result is None:
                # fallback to FP converter
                result = process_fp_text(line)

        if result is not None:
            print(result)
            pyperclip.copy(result)
