import argparse
import os
import shutil
import sys
import subprocess
import re


import ninja_syntax
from dataclasses import dataclass
from typing import Dict, List, Set, Union
from pathlib import Path
import splat
import spimdisasm
import splat.scripts.split as split
from splat.segtypes.linker_entry import LinkerEntry

if sys.platform == "linux" or sys.platform == "linux2":
    SYS_EXTENSION = ""
    GAMEFILE_EXTENSION = "."
else:
    SYS_EXTENSION = ".exe"
    GAMEFILE_EXTENSION = ""

# For multi-version support
GAMEVERSION = "USA"

@dataclass
class GAMEVERSIONINFO:
    GAME_NAME: str
    GAME_VERSION_DIR: str
    GAME_FILE_EXE: str
    GAME_FILE_SILENT: str
    GAME_FILE_HILL: str

GAMEVERSIONS = (
    # Retail
    GAMEVERSIONINFO("SLUS-00707", "USA", "SLUS_007.07", f"SILENT{GAMEFILE_EXTENSION}", f"HILL{GAMEFILE_EXTENSION}")
)

GAMEVERSIONINDEX = 0

# Version selected (made for future multi-version support)
def matchVersion(version):
    global GAMEVERSIONINDEX
    match version:
        case "USA": # Retail
            GAMEVERSIONINDEX = 0
        case _:
            GAMEVERSIONINDEX = -1
            print("Unknown version.")

@dataclass
class YAML_INFO:
    SPLIT_ENTRIES: List[str]
    SPLIT_BASENAME: str
    SPLIT_LINKER: str
    SPLIT_UNDEF_FUN: str
    SPLIT_UNDEF_SYM: str

CONFIG_FILES = [
    #"main.yaml",
    #"bodyprog.yaml",
    #"screens/b_konami.yaml",
    #"screens/stream.yaml",
    #"screens/options.yaml",
    #"screens/credits.yaml",
    #"screens/saveload.yaml",
    #"maps/map0_s00.yaml",
    #"maps/map0_s01.yaml",
    ##"maps/map0_s02.yaml", # Bugged
    #"maps/map1_s00.yaml",
    #"maps/map1_s01.yaml",
    #"maps/map1_s02.yaml",
    #"maps/map1_s03.yaml",
    #"maps/map1_s04.yaml",
    #"maps/map1_s05.yaml",
    #"maps/map1_s06.yaml",
    #"maps/map2_s00.yaml",
    #"maps/map2_s01.yaml",
    #"maps/map2_s02.yaml",
    #"maps/map2_s03.yaml",
    #"maps/map2_s04.yaml",
    #"maps/map3_s00.yaml",
    #"maps/map3_s01.yaml",
    #"maps/map3_s02.yaml",
    #"maps/map3_s03.yaml",
    #"maps/map3_s04.yaml",
    #"maps/map3_s05.yaml",
    #"maps/map3_s06.yaml",
    #"maps/map4_s00.yaml",
    #"maps/map4_s01.yaml",
    #"maps/map4_s02.yaml",
    #"maps/map4_s03.yaml",
    #"maps/map4_s04.yaml",
    #"maps/map4_s05.yaml",
    #"maps/map4_s06.yaml",
    #"maps/map5_s00.yaml",
    #"maps/map5_s01.yaml",
    #"maps/map5_s02.yaml",
    #"maps/map5_s03.yaml",
    #"maps/map6_s00.yaml",
    #"maps/map6_s01.yaml",
    #"maps/map6_s02.yaml",
    #"maps/map6_s03.yaml",
    #"maps/map6_s04.yaml",
    #"maps/map6_s05.yaml",
    #"maps/map7_s00.yaml",
    #"maps/map7_s01.yaml",
    #"maps/map7_s02.yaml",
    "maps/map7_s03.yaml"
]

# Directories
ASSETS_DIR   = "assets"
ASM_DIR      = "asm"
LINKER_DIR   = "linkers"
EXPECTED_DIR = "expected"
CONFIG_DIR   = "configs"
TOOLS_DIR    = "tools"
ROM_DIR      = "rom"
BUILD_DIR    = "build"
PERMUTER_DIR = "permuter"

# Sub-directories
IMAGE_DIR   = f"{ROM_DIR}/image"
OBJDIFF_DIR = f"{TOOLS_DIR}/objdiff"
PSXISO_DIR  = f"{TOOLS_DIR}/psxiso"

# Tooling Paths
PYTHON = "python3"
MASPSX = f"{PYTHON} tools/maspsx/maspsx.py"
if sys.platform == "linux" or sys.platform == "linux2":
    CROSS     = "mips-linux-gnu"
    AS        = f"{CROSS}-as"
    LD        = f"{CROSS}-ld"
    OBJCOPY   = f"{CROSS}-objcopy"
    OBJDUMP   = f"{CROSS}-objdump"
    CPP       = f"{CROSS}-cpp"
    CC        = f"{TOOLS_DIR}/gcc-2.8.1-psx/cc1"
    OBJDIFF   = f"{OBJDIFF_DIR}/objdiff"
    PREBUILD  = f"{TOOLS_DIR}/prebuild.sh"
    POSTBUILD = f"{TOOLS_DIR}/postbuild.sh"
    DUMPSXISO = f"{PSXISO_DIR}/dumpsxiso"
else:
    CROSS   = "tools/binutils-win"
    AS      = f"{CROSS}/as.exe"
    LD      = f"{CROSS}/ld.exe"
    OBJCOPY = f"{CROSS}/objcopy.exe"
    OBJDUMP = f"{CROSS}/objdump.exe"
    CPP     = f"{CROSS}/c++.exe"
    CC      = f"{TOOLS_DIR}/gcc-2.8.1-psx/cc1"
    OBJDIFF = f"{OBJDIFF_DIR}/objdiff.exe"

# Flags (for programs)
DUMPSXISO_FLAGS = f"-x {ROM_DIR}/{GAMEVERSIONS.GAME_VERSION_DIR} -s {ROM_DIR}/{GAMEVERSIONS.GAME_VERSION_DIR}/layout.xml {IMAGE_DIR}/{GAMEVERSIONS.GAME_NAME}.bin"

# Compilation flags (General)
INCLUDE_FLAGS   = f"-Iinclude -I {BUILD_DIR} -Iinclude/psyq"
OPT_FLAGS       = "-O2"
ENDIAN          = "-EL"
DL_EXE_FLAGS    = "-G8"
DL_OVL_FLAGS    = "-G0"

# Compilation flags (Tool specific)
CPP_FLAGS     = f"{INCLUDE_FLAGS} -D_LANGUAGE_C -DUSE_INCLUDE_ASM -P -MMD -MP -undef -Wall -lang-c -nostdinc"
CC_FLAGS      = f"{OPT_FLAGS} -mips1 -mcpu=3000 -w -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -mgas -fgnu-linker -quiet"
AS_FLAGS      = f"{ENDIAN} {INCLUDE_FLAGS} {OPT_FLAGS} {DL_OVL_FLAGS} -march=r3000 -mtune=r3000 -no-pad-sections"
OBJDUMP_FLAGS = f"--disassemble-all --reloc --disassemble-zeroes -Mreg-names=32"
# Note - MASPSX: Some of the files from SD library modifies the parameters, see `ninja_setup_list_add_source`
MASPSX_FLAGS  = f"--aspsx-version=2.77 --run-assembler"

def ninja_setup_list_add_source(target_path: str, source_path: str, ninja_file):
    global isExpandDivEnabled
    #print(f"{target_path} | {source_path} | {type(ninja_file)} | {mapId}")
    
    # Checks if the path indicates that the source file comes from a map file
    if re.search("^src/maps.*", source_path):
        mapId = (re.search("map\d_s\d\d", source_path)[0]).upper()
        ninja_file.build(
            outputs=f"{target_path}.i", rule="cpp", inputs=source_path,
            variables={
                "MAPIDFLAG": f"-D{mapId}"
            }
        )
    else:
        mapId = ""
        ninja_file.build(
            outputs=f"{target_path}.i", rule="cpp", inputs=source_path,
            variables={
                "MAPIDFLAG": ""
            }
        )
        
            
        
    ninja_file.build(
        outputs=f"{target_path}.sjis.i", rule="iconv", inputs=f"{target_path}.i", implicit=f"{target_path}.i"
    )
    
    if re.search("^src/main.*", source_path):
        ninja_file.build(
            outputs=f"{target_path}.c.s", rule="cc", inputs=f"{target_path}.sjis.i", implicit=f"{target_path}.sjis.i",
            variables={
                "DLFLAG": DL_EXE_FLAGS
            }
        )
    else:
        ninja_file.build(
            outputs=f"{target_path}.c.s", rule="cc", inputs=f"{target_path}.sjis.i", implicit=f"{target_path}.sjis.i",
            variables={
                "DLFLAG": DL_OVL_FLAGS
            }
        )
    
    if re.search("smf_io", source_path) or re.search("smf_mid", source_path):
        if isExpandDivEnabled != True:
            isExpandDivEnabled = True
            ninja_file.build(
                outputs=f"{target_path}.c.o", rule="maspsx", inputs=f"{target_path}.c.s", implicit=f"{target_path}.c.s",
                variables={
                    "EXPANDIVFLAG": "--expand-div"
                }
            )
        else:
            ninja_file.build(
                outputs=f"{target_path}.c.o", rule="maspsx", inputs=f"{target_path}.c.s", implicit=f"{target_path}.c.s"
            )
    else:
        if isExpandDivEnabled == True:
            isExpandDivEnabled = False
            ninja_file.build(
                outputs=f"{target_path}.c.o", rule="maspsx", inputs=f"{target_path}.c.s", implicit=f"{target_path}.c.s",
                variables={
                    "EXPANDIVFLAG": ""
                }
            )
        else:
            ninja_file.build(
                outputs=f"{target_path}.c.o", rule="maspsx", inputs=f"{target_path}.c.s", implicit=f"{target_path}.c.s"
            )

def ninja_setup(split_entries, skip_checksum: bool):
    global isExpandDivEnabled
    isExpandDivEnabled = False

    ninja = ninja_syntax.Writer(open(str("build.ninja"), "w", encoding="utf-8"), width=9999)
    
    ninja.rule(
        "as", description="as $in",
        command=f"{AS} {AS_FLAGS} -o $out $in",
    )

    ninja.rule(
        "cc", description="cc $in",
        command=f"{CC} {CC_FLAGS} $DLFLAG -o $out $in",
    )
    
    ninja.rule(
        "cpp", description="cpp $in",
        command=f"{CPP} -P -MMD -MP -MT $out -MF $out.d {CPP_FLAGS} $MAPIDFLAG $SKIPASMFLAG $NONMATCHINGFLAG -o $out $in",
    )

    ninja.rule(
        "iconv", description="iconv $in",
        command=f"iconv -f UTF-8 -t SHIFT-JIS $in -o $out",
    )

    ninja.rule(
        "objdump", description="objdump $in",
        command=f"{OBJDUMP} {OBJDUMP_FLAGS} $in > $out",
    )

    ninja.rule(
        "maspsx", description="maspsx $in",
        command=f"{MASPSX} {MASPSX_FLAGS} $EXPANDIVFLAG {AS_FLAGS} -o $out $in",
    )
    
    ninja.rule(
        "ld", description="link $out",
        command=f"{LD} {ENDIAN} {OPT_FLAGS} -nostdlib --no-check-sections -r -b binary -o $out $in",
    )
    
    ninja.rule(
        "elf", description="elf $out.elf",
        command=f"{LD} {ENDIAN} {OPT_FLAGS} -nostdlib --no-check-sections -Map $out.map -T $in -T $undef_sym_path -T $undef_fun_path -T {CONFIG_DIR}/{GAMEVERSIONS.GAME_VERSION_DIR}/lib_externs.ld -o $out",
    )
    
    ninja.rule(
        "objcopy", description="objcopy $out",
        command=f"{OBJCOPY} -O binary $in $out",
    )
    ninja.rule(
        "sha256sum", description="checksum",
        command=f"sha256sum --ignore-missing --check $in",
    )
    ninja.rule(
        "postbuild", description="postbuild script",
        command=f"{POSTBUILD} $in",
    )
    
    elfBuildRequirements = []
    checksumBuildRequirements = []
    
    # Build all the objects
    for split_config in split_entries:
        match split_config.SPLIT_BASENAME:
            case "STREAM.BIN":
                os.system(f"{PREBUILD} screens/stream")
            case "main":
                os.system(f"{PREBUILD} main")
            case "BODYPROG.BIN":
                os.system(f"{PREBUILD} bodyprog")
        
        for split_entry in split_config.SPLIT_ENTRIES:
            for entry in split_entry:
                seg = entry.segment
                
                if entry.object_path is None:
                    continue
                
                if seg.type[0] == ".":
                    continue
                    
                
                match seg.type:
                    case "asm" | "data" | "sdata" | "bss" | "sbss" | "rodata" | "header":
                        ninja.build(outputs=str(entry.object_path), rule="as", inputs=str(entry.src_paths[0]))
                    case "c":
                        ninja_setup_list_add_source(str(entry.object_path).removesuffix(".c.o"), str(entry.src_paths[0]), ninja)
                    case "bin":
                        ninja.build(outputs=str(entry.object_path), rule="ld", inputs=str(entry.src_paths[0]))
                    case "lib":
                        """Did you know that Silent Hill: Homecoming was meant to
                        have a seccion where Alex would have to go through a forest
                        and there he would have founded a hunter that would have
                        tried to kill him, but due lack of direction the whole
                        section was scrapped and the hunter model was repurpose for
                        Travis Grady"""
                    case _:
                        print(f"ERROR: Unsupported build segment type {seg.type}")
                        sys.exit(1)
                
                
                if isinstance(seg, splat.segtypes.common.lib.CommonSegLib) != True:
                    elfBuildRequirements += [str(s) for s in [entry.object_path]]
        
        if split_config.SPLIT_BASENAME == "BODYPROG.BIN" or split_config.SPLIT_BASENAME == "B_KONAMI.BIN":
            split_config.SPLIT_BASENAME = f"1ST/{split_config.SPLIT_BASENAME}"
        elif split_config.SPLIT_BASENAME != "main":
            split_config.SPLIT_BASENAME = f"VIN/{split_config.SPLIT_BASENAME}"
        
        
        if split_config.SPLIT_BASENAME != "main":
            output = f"{BUILD_DIR}/out/{split_config.SPLIT_BASENAME}"
        else:
            output = f"{BUILD_DIR}/out/SLUS_007.07"
        
        ninja.build(
            outputs=f"{output}.elf",
            rule="elf",
            inputs=split_config.SPLIT_LINKER,
            variables={
                "undef_sym_path": split_config.SPLIT_UNDEF_SYM,
                "undef_fun_path": split_config.SPLIT_UNDEF_FUN,
            },
            implicit=elfBuildRequirements
        )
        ninja.build(
            outputs=output,
            rule="objcopy",
            inputs=f"{output}.elf",
            implicit=f"{output}.elf"
        )
        
        if split_config.SPLIT_BASENAME == "1ST/BODYPROG.BIN":
            ninja.build(
                outputs=f"{output}.fix",
                rule="postbuild",
                inputs=output,
                implicit=output
            )
        elif split_config.SPLIT_BASENAME == "VIN/STREAM.BIN":
            ninja.build(
                outputs=f"{output}.fix",
                rule="postbuild",
                inputs=output,
                implicit=output
            )
        
        checksumBuildRequirements += [str(s) for s in [output]]
    
    if skip_checksum != True:
        for s in range(len(checksumBuildRequirements)):
            if checksumBuildRequirements[s] == f"{BUILD_DIR}/out/VIN/STREAM.BIN" or checksumBuildRequirements[s] == f"{BUILD_DIR}/out/1ST/BODYPROG.BIN":
                checksumBuildRequirements[s] = f"{checksumBuildRequirements[s]}.fix"
        
        ninja.build(
            f"{BUILD_DIR}/out/checksum.ok",
            "sha256sum",
            f"{CONFIG_DIR}/{GAMEVERSIONS.GAME_VERSION_DIR}/checksum.sha",
            implicit=checksumBuildRequirements
        )

def clean_files(clean_all):
    shutil.rmtree(BUILD_DIR, ignore_errors=True)
    shutil.rmtree(PERMUTER_DIR, ignore_errors=True)

    if clean_all:
        if os.path.exists(".splache"):
            os.remove(".splache")
        if os.path.exists(".ninja_log"):
            os.remove(".ninja_log")
        if os.path.exists("build.ninja"):
            os.remove("build.ninja")
        shutil.rmtree(ASM_DIR, ignore_errors=True)
        shutil.rmtree(EXPECTED_DIR, ignore_errors=True)
        shutil.rmtree(LINKER_DIR, ignore_errors=True)

def extract_files():
    matchVersion(GAMEVERSION)
    print(f"Extracting files for version {GAMEVERSION}")
    
    target_assets = f"{ASSETS_DIR}/{GAMEVERSIONS.GAME_VERSION_DIR}"
    target_rom    = f"{ROM_DIR}/{GAMEVERSIONS.GAME_VERSION_DIR}"
    
    shutil.rmtree(target_assets, ignore_errors=True)
    shutil.rmtree(target_rom, ignore_errors=True)
    
    os.system(f"{DUMPSXISO} {DUMPSXISO_FLAGS}")
    subprocess.call([PYTHON, f"{TOOLS_DIR}/silentassets/extract.py",
    "-exe", f"{target_rom}/{GAMEVERSIONS.GAME_FILE_EXE}",
    "-fs", f"{target_rom}/{GAMEVERSIONS.GAME_FILE_SILENT}",
    "-fh", f"{target_rom}/{GAMEVERSIONS.GAME_FILE_HILL}",
    target_assets])

def main():
    parser = argparse.ArgumentParser(description="Configure the project")
    parser.add_argument(
        "-c", "--clean",
        help="Clean build and permuter files",
        action="store_true",
    )
    parser.add_argument(
        "-iso_e", "--iso_extract",
        help="Extract game files",
        action="store_true",
    )
    parser.add_argument(
        "-set", "--setup",
        choices=["extract", "insert"],
        help="Setup individual overlays or the executable only"
    )
    parser.add_argument(
        "-sc", "--skip_checksum",
        help="Skip checksum",
        action="store_true",
    )
    parser.add_argument(
        "-obj", "--objdiff_config",
        help="Builds setup for Objdiff",
        action="store_true",
    )
    args = parser.parse_args()

    clean_compilation_files = (args.clean) or False
    extract_game_files      = (args.iso_extract) or False
    splits_yaml_info        = []
    skip_checksum_option    = (args.skip_checksum) or False
    objdiff_config_option   = (args.objdiff_config) or False
    
    if clean_compilation_files:
        print("Cleaning compilation files")
        clean_files(False)
        return
    
    if extract_game_files:
        extract_files()
        return
    
    if args.setup == None:
        clean_files(True)
        for yaml in CONFIG_FILES:
            splat.util.symbols.spim_context = spimdisasm.common.Context()
            splat.util.symbols.reset_symbols()
            split.main([Path(f"{CONFIG_DIR}/{GAMEVERSIONS.GAME_VERSION_DIR}/{yaml}")], modes="all", use_cache=False, verbose=False, disassemble_all=True, make_full_disasm_for_code=True)
            splits_yaml_info.append(YAML_INFO([split.linker_writer.entries], split.config['options']['basename'], split.config['options']['ld_script_path'], split.config['options']['undefined_funcs_auto_path'], split.config['options']['undefined_syms_auto_path']))
        
        ninja_setup(splits_yaml_info, skip_checksum_option)

if __name__ == "__main__":
    main()
