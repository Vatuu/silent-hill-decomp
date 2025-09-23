#!/usr/bin/env python3

# Converts `g_SavegamePtr->eventFlags_168[X] & Y` expressions to `Savegame_EventFlagGet(Z)`
# Also converts Q12 integers (0x7CCC, -0x1444, 0xFFFE0DDD, 4096) into float equivalents (may need to be rounded afterward)
# (mostly GPT written)

import re

# ---------- EventFlags converter ----------
def _parse_mask(mask_str):
    """Strip integer suffixes (U/L) and parse mask as int."""
    mask_clean = re.sub(r'[uUlL]+$', '', mask_str)
    return int(mask_clean, 0)

def _bit_indices(mask, width=32):
    """Return list of bit indices (0..width-1) that are set in mask."""
    return [i for i in range(width) if (mask >> i) & 1]

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
    arr_pat   = r'.*?eventFlags_168\[(\d+)\]'
    mask_pat  = r'(0x[0-9a-fA-F]+(?:[uUlL]*)|\d+)'
    shift_pat = r'\(\s*1\s*<<\s*(\d+)\s*\)'

    # `(eventFlags_168 & xx) == xx` -> Get and possibly !Get
    m = re.search(arr_pat + r'\s*\(?\s*&\s*' + mask_pat + r'\s*\)?\s*==\s*' + mask_pat, expr)
    if m:
        array_idx = int(m.group(1))
        mask = _parse_mask(m.group(2))
        value = _parse_mask(m.group(3))
        conditions = []
        for bit in range(32):
            if mask & (1 << bit):
                final_idx = array_idx * 32 + bit
                if value & (1 << bit):
                    conditions.append(f"Savegame_EventFlagGet({final_idx})")
                else:
                    conditions.append(f"!Savegame_EventFlagGet({final_idx})")
        return " && ".join(conditions) if conditions else None

    # |= (shift)
    m = re.search(arr_pat + r'\s*\|\=\s*' + shift_pat, expr)
    if m:
        array_idx, bit_idx = int(m.group(1)), int(m.group(2))
        return f"Savegame_EventFlagSet(EventFlag_{array_idx * 32 + bit_idx})"

    # |= (literal)
    m = re.search(arr_pat + r'\s*\|\=\s*' + mask_pat, expr)
    if m:
        array_idx = int(m.group(1))
        mask = _parse_mask(m.group(2))
        indices = _bit_indices(mask)
        return '; '.join(f"Savegame_EventFlagSet(EventFlag_{array_idx * 32 + i})" for i in indices) if indices else None

    # &= ~(shift)
    m = re.search(arr_pat + r'\s*\&\=\s*~' + shift_pat, expr)
    if m:
        array_idx, bit_idx = int(m.group(1)), int(m.group(2))
        return f"Savegame_EventFlagClear(EventFlag_{array_idx * 32 + bit_idx})"

    # &= ~(literal)
    m = re.search(arr_pat + r'\s*\&\=\s*~' + mask_pat, expr)
    if m:
        array_idx = int(m.group(1))
        mask = _parse_mask(m.group(2))
        indices = _bit_indices(mask)
        return '; '.join(f"Savegame_EventFlagClear(EventFlag_{array_idx * 32 + i})" for i in indices) if indices else None

    # &= (literal WITHOUT ~) -> mask is the negated form; bits to clear are zeros in mask
    m = re.search(arr_pat + r'\s*\&\=\s*' + mask_pat, expr)
    if m:
        array_idx = int(m.group(1))
        mask = _parse_mask(m.group(2))
        inverted = (~mask) & 0xFFFFFFFF
        indices = _bit_indices(inverted)
        return '; '.join(f"Savegame_EventFlagClear(EventFlag_{array_idx * 32 + i})" for i in indices) if indices else None

    # &= (shift WITHOUT ~) -> uncommon, but handle by inverting the single-bit mask
    m = re.search(arr_pat + r'\s*\&\=\s*' + shift_pat, expr)
    if m:
        array_idx, bit_idx = int(m.group(1)), int(m.group(2))
        inverted = (~(1 << bit_idx)) & 0xFFFFFFFF
        indices = _bit_indices(inverted)
        return '; '.join(f"Savegame_EventFlagClear(EventFlag_{array_idx * 32 + i})" for i in indices) if indices else None

    # & (shift) -> Get
    m = re.search(arr_pat + r'\s*\&\s*' + shift_pat, expr)
    if m:
        array_idx, bit_idx = int(m.group(1)), int(m.group(2))
        return f"Savegame_EventFlagGet(EventFlag_{array_idx * 32 + bit_idx})"

    # & (literal) -> Get (if multiple bits -> OR them)
    m = re.search(arr_pat + r'\s*\&\s*' + mask_pat, expr)
    if m:
        array_idx = int(m.group(1))
        mask = _parse_mask(m.group(2))
        indices = _bit_indices(mask)
        if not indices:
            return None
        if len(indices) == 1:
            return f"Savegame_EventFlagGet(EventFlag_{array_idx * 32 + indices[0]})"
        return ' || '.join(f"Savegame_EventFlagGet(EventFlag_{array_idx * 32 + i})" for i in indices)

    return None

# ---------- FP converter ----------
def to_signed(val, bits=32):
    """Convert unsigned int to signed (two's complement)."""
    if val & (1 << (bits - 1)):
        val -= 1 << bits
    return val

def process_fp_text(text):
    qval = 12  # default Q-format is Q12

    # detect and strip Q modifier
    match = re.search(r'\bQ(\d+)\b', text)
    if match:
        qval = int(match.group(1))
        text = re.sub(r'\bQ\d+\b', '', text, count=1)

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

        return f"Q{qval}({val / (1 << qval)}f)"

    pattern = re.compile(r'[-+]?0x[0-9A-Fa-f]+|[-+]?\d+')
    return pattern.sub(convert_value, text)

# ---------- Unified REPL ----------
if __name__ == "__main__":
    print("Enter expressions like '(g_SavegamePtr->eventFlags_168[2] & 8)' or '(g_SavegamePtr->eventFlags_168[2] & (1 << 3))'.")
    print("Or enter a line containing decimal/hexadecimal Q12 numbers (0x7CCC, -0x1444, 4096, 0xFFFE0DDD) to convert to float")
    print("(change to other Q** formats by including Q format in the text, `chara.field_48 = Q8(-0x1999)'")
    print()
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
