#!/usr/bin/env python3
"""
Drop-in iconv wrapper that converts UTF-8 to SJIS and escapes all
multi-byte SJIS sequences so cc1 (GCC 2.8.1) doesn't misinterpret
trail bytes like 0x5C (backslash), 0x22 (quote), 0x0A (newline).

Usage: iconv_sjis_wrapper.py -f UTF-8 -t SHIFT-JIS input.i -o output.sjis.i
"""

import argparse
import subprocess
import sys

def is_sjis_lead(b: int) -> bool:
    return (0x81 <= b <= 0x9F) or (0xE0 <= b <= 0xFC)

def escape_sjis_multibyte(data: bytes) -> bytes:
    """Replace all SJIS multi-byte sequences with \\xNN\\xNN escapes."""
    out = []
    i = 0
    while i < len(data):
        b = data[i]
        if is_sjis_lead(b) and i + 1 < len(data):
            trail = data[i + 1]
            # Replace entire multi-byte char with explicit hex escapes
            out += list(f'\\x{b:02X}\\x{trail:02X}'.encode('ascii'))
            i += 2
        else:
            out.append(b)
            i += 1
    return bytes(out)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', '--from-code', default='UTF-8')
    parser.add_argument('-t', '--to-code', default='SHIFT-JIS')
    parser.add_argument('-o', '--output', required=True)
    parser.add_argument('input')
    args = parser.parse_args()

    # Step 1: call real iconv to do the encoding conversion
    result = subprocess.run(
        ['iconv', '-f', args.from_code, '-t', args.to_code, args.input],
        capture_output=True
    )
    if result.returncode != 0:
        sys.stderr.write(result.stderr.decode(errors='replace'))
        sys.exit(result.returncode)

    # Step 2: escape all multi-byte SJIS sequences
    escaped = escape_sjis_multibyte(result.stdout)

    with open(args.output, 'wb') as f:
        f.write(escaped)

if __name__ == '__main__':
    main()
