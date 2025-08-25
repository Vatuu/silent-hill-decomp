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
# - datatypes for global vars, Ghidra adds the struct/types for them but seems to ignore the actual `extern`s, might need to fetch those from headers ourselves

from ghidra.program.model.data import FunctionDefinitionDataType
from ghidra.program.model.symbol import SourceType
from ghidra.app.cmd.function import ApplyFunctionSignatureCmd
from ghidra.program.disassemble import Disassembler
from ghidra.util.task import ConsoleTaskMonitor
import re

verbose = False

def run():
    dtm = currentProgram.getDataTypeManager()
    st = currentProgram.getSymbolTable()
    monitor = ConsoleTaskMonitor()
    disassembler = Disassembler.getDisassembler(currentProgram, monitor, None)

    all_dts = list(dtm.getAllDataTypes())
    func_defs = [dt for dt in all_dts if "FunctionDefinition" in dt.getClass().getSimpleName()]
    print("[*] Found %d function definitions in DataTypeManager" % len(func_defs))

    total_defs = 0
    applied = 0
    funcs_updated = 0

    for dt in dtm.getAllDataTypes():
        # Check for function definitions
        if "FunctionDefinition" in dt.getClass().getSimpleName():
            total_defs += 1
            func_name = dt.getName()
            if verbose:
                print("[>] Found FunctionDefinition: %s" % func_name)

            matched = False

            # First try searching for symbol name as-is, should work for funcs we've added names for
            symbols = st.getSymbols(func_name)
            if verbose:
                print("Checking symbol table for name: %s" % func_name)
            for sym in symbols:
                if verbose:
                    print("Symbol: %s @ %s type: %s" % (sym.getName(), sym.getAddress(), sym.getSymbolType()))
                if sym.getSymbolType().toString() == "Function":
                    func = getFunctionAt(sym.getAddress())
                    if func:
                        try:
                            cmd = ApplyFunctionSignatureCmd(func.getEntryPoint(), dt, SourceType.USER_DEFINED)
                            if cmd.applyTo(currentProgram):
                                print("[+] Applied prototype to %s at %s" % (func.getName(), func.getEntryPoint()))
                            else:
                                print("    [-] Failed to apply prototype to %s at %s" % (func.getName(), func.getEntryPoint()))
                        except Exception as e:
                            print("    [!] Exception while applying prototype to %s: %s" % (func.getName(), e))
                        matched = True
                        funcs_updated += 1

            # If not matched, try extracting address from symbol name instead
            # (Our unnamed symbols in decomp are called something like `func_80012345`, but Ghidra uses `FUN_80012345` instead, this should let us find them)
            # Ghidra name will also be updated to match name from decomp
            if not matched:
                m = re.match(r"func_([0-9A-Fa-f]+)", func_name)
                if m:
                    addr_str = m.group(1)
                    addr_val = int(addr_str, 16)
                    addr = toAddr(addr_val)

                    # Only try applying func_XXX prototypes for funcs inside main/bodyprog, since func_XXX inside maps would likely have conflicts
                    # (ideally map funcs will be renamed to have unique names later, or sharedFunc names that all share same prototype)
                    if addr_val >= 0x80010000 and addr_val < 0x800C9578:
                        if verbose:
                            print("[*] Trying address fallback: parsed %s as %s" % (addr_str, addr))
                        func = getFunctionAt(addr)

                        if func is None:
                            # If no func at the address, it might be a func Ghidra hadn't marked as func yet (maybe unused/unrefed, or only refed by data)
                            # Try creating a func for it
                            if verbose:
                                print("[*] Creating func for %s at %s" % (addr_str, addr))
                            currentProgram.getSymbolTable().createLabel(addr, func_name, currentProgram.getGlobalNamespace(), SourceType.USER_DEFINED)
                            disassembler.disassemble(addr, None)

                            if getFunctionAt(addr) is None:
                                createFunction(addr, func_name)

                            func = getFunctionAt(addr)

                        if func:
                            if verbose:
                                print("[+] Matched by address: %s at %s" % (func_name, addr))
                            try:
                                cmd = ApplyFunctionSignatureCmd(func.getEntryPoint(), dt, SourceType.USER_DEFINED)
                                if cmd.applyTo(currentProgram):
                                    print("[+] Applied prototype to %s at %s" % (func.getName(), func.getEntryPoint()))
                                else:
                                    print("    [-] Failed to apply prototype to %s at %s" % (func.getName(), func.getEntryPoint()))
                            except Exception as e:
                                print("    [!] Exception while applying prototype to %s: %s" % (func.getName(), e))

                            try:
                                func.setName(func_name, SourceType.USER_DEFINED)
                                if verbose:
                                    print("[+] Renamed function at %s to %s" % (addr, func_name))
                            except Exception as e:
                                print("    [!] Rename failed at %s: %s" % (addr, e))
                            matched = True
                            funcs_updated += 1
                        else:
                            if verbose:
                                print("    [-] No function defined at address %s" % addr)

            if not matched:
                print("    [-] No match found for %s" % func_name)
            else:
                applied += 1

    print("\n[*] Scan complete")
    print("[*] Found %d FunctionDefinitionDataTypes in DataTypeManager" % total_defs)
    print("[*] Applied %d prototypes to %d functions" % (applied, funcs_updated))

run()
