#!/usr/bin/env python3
"""
Hide splat's jtbl_* symbols in generated `expected` asm, before its assembled.

Splat names each jump table with a jtbl_* symbol, but our C compiler
never emits symbols for any jump tables it creates.

Unfortunately objdiff seems to try pairing data by symbol names, and
counts the data as missing if it can't find the same name in both the
`expected` and built code, even if data itself matches.
(additionally, any data section that isn't a 100% match gets treated as 0%, 
so if we fully matched a section but it included 1 jtbl, the whole % for 
that section would get treated as 0%...)

This rewrites the generated .s so jtbl symbols are hidden with no size instead,
preventing objdiff from trying to compare the data entirely.
(which is fine for us since C compiler can never emit symbols for them anyway.
and if the data in jtbl didn't match, we'd have a checksum error)

This also hides any hack_*_fix symbols that we've named, those are only given
named symbols to prevent spimdisasm from making relocations from them, and
we sometimes skip them entirely with `pad` sections, so they never existed
in C.

TODO: Need to find why other projects didn't need anything like this.
Maybe there's still a better way for us to get around this issue...

Usage:
    python3 tools/hide_jtbl_syms.py asm/USA
"""
import os
import re
import sys

# `dlabel jtbl_X` -> global object symbol; `enddlabel jtbl_X` -> `.size`;
# `nonmatching jtbl_X` -> a global `jtbl_X.NON_MATCHING` marker.
DLABEL = re.compile(r"^(\s*)dlabel\s+(jtbl_[0-9A-Fa-f]+|hack_\w+_fix)\s*$")
ENDDLABEL = re.compile(r"^\s*enddlabel\s+(jtbl_[0-9A-Fa-f]+|hack_\w+_fix)\s*$")
NONMATCHING = re.compile(r"^\s*nonmatching\s+(jtbl_[0-9A-Fa-f]+|hack_\w+_fix)\s*$")


def process(text):
    out, hidden = [], 0
    for line in text.splitlines(keepends=True):
        m = DLABEL.match(line.rstrip("\n"))
        if m:
            indent, name = m.groups()
            out.append(line)
            out.append("%s.hidden %s\n" % (indent, name))
            hidden += 1
            continue
        if ENDDLABEL.match(line.rstrip("\n")):
            # drop the `.size`, leaving st_size = 0 (what objdiff skips on)
            continue
        if NONMATCHING.match(line.rstrip("\n")):
            # would emit a global `jtbl_X.NON_MATCHING` the compiler never has
            continue
        out.append(line)
    return "".join(out), hidden


def main():
    if len(sys.argv) < 2:
        sys.exit("usage: %s <asm_dir> [...]" % sys.argv[0])
    files = total = 0
    for root_dir in sys.argv[1:]:
        for root, _, names in os.walk(root_dir):
            for n in names:
                if not n.endswith(".s"):
                    continue
                p = os.path.join(root, n)
                src = open(p).read()
                if "jtbl_" not in src and "hack_" not in src:
                    continue
                new, hidden = process(src)
                if hidden and new != src:
                    open(p, "w").write(new)
                    files += 1
                    total += hidden
    print("hide_jtbl_syms: hid %d jtbl/hack symbols across %d files" % (total, files))


if __name__ == "__main__":
    main()
