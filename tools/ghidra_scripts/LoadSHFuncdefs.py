#@author emoose
#@category PSX

# Hacky script that applies loaded function datatypes onto the functions themselves
# This should be used after loading in C headers into Ghidra, so that func datatypes from header can be applied to the DB
#
# Usage:
# - Copy the silent-hill-decomp.prf file from the repo to Ghidra parserprofiles folder
#  (either %AppData%/ghidra/ghidra_XXX_PUBLIC/parserprofiles/, or Ghidra/Features/Base/data/parserprofiles/ folder)
# - After loading SH in with the LoadSHOverlays.py script, go to File > Parse C Source
# - Select silent-hill-decomp.prf in the Parse Configuration dropdown
# - In the Include Paths section, double-click each of the paths and change them to use the correct repo path
# - Click Parse to Program, if asked about open archives, pick Don't Use Open Archives
# - Once the headers have been parsed, go to Window > Script Manager > PSX, click on LoadSHFuncdefs.py, and press the green Play icon
# - Allow script to run, hopefully once it's finished most functions should now have the correct definition applied.

# TODO:
# - sharedFunc support, not sure if this can apply funcdefs to multiple of the same symbol name properly
# - datatypes for global vars, Ghidra adds the struct/types for them but seems to ignore the actual `extern`s, might need to fetch those from headers ourselves

from ghidra.program.model.data import FunctionDefinitionDataType
from ghidra.program.model.symbol import SourceType
from ghidra.app.cmd.function import ApplyFunctionSignatureCmd
import re

verbose = False

def run():
    dtm = currentProgram.getDataTypeManager()
    st = currentProgram.getSymbolTable()

    all_dts = list(dtm.getAllDataTypes())
    func_defs = [dt for dt in all_dts if "FunctionDefinition" in dt.getClass().getSimpleName()]
    print("[*] Found %d function definitions in DataTypeManager" % len(func_defs))

    total_defs = 0
    applied = 0

    for dt in dtm.getAllDataTypes():
        # Check for function definitions
        if "FunctionDefinition" in dt.getClass().getSimpleName():
            total_defs += 1
            func_name = dt.getName()
            if verbose:
                print("\n[>] Found FunctionDefinition: ", func_name)

            matched = False

            # First try searching for symbol name as-is, should work for funcs we've added names for
            symbols = st.getSymbols(func_name)
            if verbose:
                print("    Checking symbol table for name:", func_name)
            for sym in symbols:
                if verbose:
                    print("        Symbol:", sym.getName(), "@", sym.getAddress(), "type:", sym.getSymbolType())
                if sym.getSymbolType().toString() == "Function":
                    func = getFunctionAt(sym.getAddress())
                    if func:
                        try:
                            cmd = ApplyFunctionSignatureCmd(func.getEntryPoint(), dt, SourceType.USER_DEFINED)
                            if cmd.applyTo(currentProgram):
                                print("[+] Applied prototype to", func.getName(), "at", func.getEntryPoint())
                            else:
                                print("[-] Failed to apply prototype to", func.getName(), "at", func.getEntryPoint())
                        except Exception as e:
                            print("[!] Exception while applying prototype to", func.getName(), ":", e)
                        applied += 1
                        matched = True
                        break

            # If not matched, try extracting address from symbol name instead
            # (Our unnamed symbols in decomp are called something like `func_80012345`, but Ghidra uses `FUN_80012345` instead, this should let us find them)
            # Ghidra name will also be updated to match name from decomp
            if not matched:
                m = re.match(r"func_([0-9A-Fa-f]+)", func_name)
                if m:
                    addr_str = m.group(1)
                    addr_val = int(addr_str, 16)
                    addr = toAddr(addr_val)
                    if verbose:
                        print("    [*] Trying address fallback: parsed %s to %s" % (addr_str, addr))
                    func = getFunctionAt(addr)
                    if func:
                        if verbose:
                            print("    [+] Matched by address:", func_name, "at", addr)
                        try:
                            cmd = ApplyFunctionSignatureCmd(func.getEntryPoint(), dt, SourceType.USER_DEFINED)
                            if cmd.applyTo(currentProgram):
                                print("[+] Applied prototype to", func.getName(), "at", func.getEntryPoint())
                            else:
                                print("[-] Failed to apply prototype to", func.getName(), "at", func.getEntryPoint())
                        except Exception as e:
                            print("[!] Exception while applying prototype to", func.getName(), ":", e)

                        try:
                            func.setName(func_name, SourceType.USER_DEFINED)
                            if verbose:
                                print("    [+] Renamed function at %s to %s" % (addr, func_name))
                        except Exception as e:
                            print("    [!] Rename failed at %s: %s" % (addr, e))
                        applied += 1
                        matched = True
                    else:
                        if verbose:
                            print("    [-] No function defined at address", addr)

            if not matched:
                print("    [-] No match found for", func_name)

    print("\n[*] Scan complete")
    print("[*] Found %d FunctionDefinitionDataTypes in DataTypeManager" % total_defs)
    print("[*] Applied %d prototypes" % applied)

run()
