#!/usr/bin/env python3

# Slow script that searches .c files in src/maps/ for functions with missing .h decls
# (adding decls may help improve m2c output)

import subprocess
from pathlib import Path
from pycparser import c_ast, parse_file

CTX_FILE = "ctx.c"

class FuncDefVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.defs = set()

    def visit_FuncDef(self, node):
        storage = node.decl.storage or []
        if "static" not in storage:
            self.defs.add(node.decl.name)
        # DO NOT recurse into children

class FuncDeclVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.decls = set()
        self._def_names = set()

    def visit_FuncDef(self, node):
        # record definition names so we can ignore their Decl
        self._def_names.add(node.decl.name)

    def visit_Decl(self, node):
        if not isinstance(node.type, c_ast.FuncDecl):
            return

        if node.name in self._def_names:
            return  # this Decl belongs to a definition

        storage = node.storage or []
        if "static" not in storage:
            self.decls.add(node.name)

def run_m2ctx(c_file):
    subprocess.run(
        ["python3", "tools/m2ctx.py", str(c_file)],
        check=True,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )

def parse_ctx():
    return parse_file(
        CTX_FILE,
        use_cpp=True,
        cpp_args=["-E", "-Ipycparser/utils/fake_libc_include"],
    )

def check_file(c_file):
    #print(str(c_file))
    run_m2ctx(c_file)

    ast = parse_ctx()

    def_v = FuncDefVisitor()
    decl_v = FuncDeclVisitor()

    def_v.visit(ast)
    decl_v.visit(ast)

    missing = def_v.defs - decl_v.decls

    for name in sorted(missing):
        print(f"{c_file}: missing decl for {name}")

    return bool(missing)

def main():
    src_root = Path("src/maps")

    had_errors = False

    for subdir in sorted(src_root.iterdir()):
        if not subdir.is_dir():
            continue

        for c_file in sorted(subdir.glob("*.c")):
            if "characters/" not in str(c_file):
                had_errors |= check_file(c_file)

    raise SystemExit(1 if had_errors else 0)

if __name__ == "__main__":
    main()
