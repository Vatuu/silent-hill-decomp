import argparse
import os
import shutil
import sys
import subprocess
import re


from ninja import ninja_syntax
from dataclasses import dataclass
from typing import Dict, List, Set, Union
from pathlib import Path
import splat
import spimdisasm
import splat.scripts.split as split
from splat.segtypes.linker_entry import LinkerEntry

if sys.platform == "linux" or sys.platform == "linux2":
    GAMEFILE_EXTENSION = "."
elif sys.platform == "win32":
    GAMEFILE_EXTENSION = ""

# For multi-version support
@dataclass
class GAMEVERSIONSETUPINFO:
    GAME_NAME: str
    GAME_VERSION_DIR: str
    GAME_FILE_EXE: str
    GAME_FILE_SILENT: str
    GAME_FILE_HILL: str

@dataclass
class GAMEVERSIONINFO:
    GAME_IDX: int
    GAME_NAME_VERSION: str
    GAME_SETUP_INFO: GAMEVERSIONSETUPINFO


GAMEVERSIONS = (
    # Retail
    GAMEVERSIONINFO(0, "USA",
        GAMEVERSIONSETUPINFO("SLUS-00707", "USA", "SLUS_007.07", f"SILENT{GAMEFILE_EXTENSION}", f"HILL{GAMEFILE_EXTENSION}")
    ),
    GAMEVERSIONINFO(3, "JAP2",
        GAMEVERSIONSETUPINFO("SLPM-86192", "JAP-2", "SLPM_861.92", f"SILENT{GAMEFILE_EXTENSION}", f"HILL{GAMEFILE_EXTENSION}")
    )
)

@dataclass
class YAML_INFO:
    SPLIT_ENTRIES: List[str]
    SPLIT_BASENAME: str
    SPLIT_LINKER: str
    SPLIT_UNDEF_FUN: str
    SPLIT_UNDEF_SYM: str

YAML_EXECUTABLE = ["main.yaml"]
YAML_ENGINE = ["bodyprog.yaml"]

YAML_SCREENS = [
    "screens/b_konami.yaml",
    "screens/stream.yaml",
    "screens/options.yaml",
    "screens/credits.yaml",
    "screens/saveload.yaml"
]
YAML_MAPS_0 = [
    "maps/map0_s00.yaml",
    "maps/map0_s01.yaml",
    "maps/map0_s02.yaml",
]
YAML_MAPS_1 = [
    "maps/map1_s00.yaml",
    "maps/map1_s01.yaml",
    "maps/map1_s02.yaml",
    "maps/map1_s03.yaml",
    "maps/map1_s04.yaml",
    "maps/map1_s05.yaml",
    "maps/map1_s06.yaml"
]
YAML_MAPS_2 = [
    "maps/map2_s00.yaml",
    "maps/map2_s01.yaml",
    "maps/map2_s02.yaml",
    "maps/map2_s03.yaml",
    "maps/map2_s04.yaml"
]
YAML_MAPS_3 = [
    "maps/map3_s00.yaml",
    "maps/map3_s01.yaml",
    "maps/map3_s02.yaml",
    "maps/map3_s03.yaml",
    "maps/map3_s04.yaml",
    "maps/map3_s05.yaml",
    "maps/map3_s06.yaml"
]
YAML_MAPS_4 = [
    "maps/map4_s00.yaml",
    "maps/map4_s01.yaml",
    "maps/map4_s02.yaml",
    "maps/map4_s03.yaml",
    "maps/map4_s04.yaml",
    "maps/map4_s05.yaml",
    "maps/map4_s06.yaml"
]
YAML_MAPS_5 = [
    "maps/map5_s00.yaml",
    "maps/map5_s01.yaml",
    "maps/map5_s02.yaml",
    "maps/map5_s03.yaml"
]
YAML_MAPS_6 = [
    "maps/map6_s00.yaml",
    "maps/map6_s01.yaml",
    "maps/map6_s02.yaml",
    "maps/map6_s03.yaml",
    "maps/map6_s04.yaml",
    "maps/map6_s05.yaml"
]
YAML_MAPS_7 = [
    "maps/map7_s00.yaml",
    "maps/map7_s01.yaml",
    "maps/map7_s02.yaml",
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
if sys.platform == "linux" or sys.platform == "linux2":
    IMAGE_DIR   = f"{ROM_DIR}/image"
    OBJDIFF_DIR = f"{TOOLS_DIR}/objdiff"
    PSXISO_DIR  = f"{TOOLS_DIR}/psxiso"
elif sys.platform == "win32":
    IMAGE_DIR   = f"{ROM_DIR}\\image"
    OBJDIFF_DIR = f"{TOOLS_DIR}\\objdiff"
    PSXISO_DIR  = f"{TOOLS_DIR}\\psxiso"

# Tooling Paths
if sys.platform == "win32":
    PYTHON = "py"
else:
    PYTHON = "python3"
MASPSX = f"{PYTHON} tools/maspsx/maspsx.py"
if sys.platform == "linux" or sys.platform == "linux2":
    CROSS             = "mips-linux-gnu"
    AS                = f"{CROSS}-as"
    LD                = f"{CROSS}-ld"
    OBJCOPY           = f"{CROSS}-objcopy"
    OBJDUMP           = f"{CROSS}-objdump"
    CPP               = f"{CROSS}-cpp"
    CC                = f"{TOOLS_DIR}/gcc-2.8.1-psx/cc1"
    OBJDIFF           = f"{OBJDIFF_DIR}/objdiff"
    OBJDIFF_GENSCRIPT = f"{OBJDIFF_DIR}/objdiff_generate.py"
    PREBUILD          = f"{TOOLS_DIR}/prebuild.sh"
    POSTBUILD         = f"{TOOLS_DIR}/postbuild.sh"
    DUMPSXISO         = f"{PSXISO_DIR}/dumpsxiso"
    ICONV             = f"iconv"
elif sys.platform == "win32":
    CROSS             = f"{TOOLS_DIR}/win-build/binutils/mips-linux-gnu"
    AS                = f"{CROSS}-as.exe"
    LD                = f"{CROSS}-ld.exe"
    OBJCOPY           = f"{CROSS}-objcopy.exe"
    OBJDUMP           = f"{CROSS}-objdump.exe"
    CPP               = f"{TOOLS_DIR}/win-build/mcpp/mcpp.exe"
    CC                = f"{TOOLS_DIR}/win-build/gcc-psx/cc1psx.exe"
    OBJDIFF           = f"{OBJDIFF_DIR}\\objdiff.exe"
    OBJDIFF_GENSCRIPT = f"{OBJDIFF_DIR}\\objdiff_generate.py"
    PREBUILD          = f"cmd.exe /c {TOOLS_DIR}\\prebuild.bat"
    POSTBUILD         = f"{PYTHON} {TOOLS_DIR}\\postbuild.py"
    DUMPSXISO         = f"{PSXISO_DIR}\\dumpsxiso.exe"
    ICONV             = f"{TOOLS_DIR}\\win-build\\iconv\\iconv.bat"

# Compilation flags (General)
INCLUDE_FLAGS   = f"-Iinclude -I {BUILD_DIR} -Iinclude/psyq"
OPT_FLAGS       = "-O2"
ENDIAN          = "-EL"
DL_EXE_FLAGS    = "-G8"
DL_OVL_FLAGS    = "-G0"

# Compilation flags (Tool specific)
# Note - MASPSX: Some of the files from SD library modifies the parameters, see `ninja_setup_list_add_source`
if sys.platform == "linux" or sys.platform == "linux2":
    CPP_FLAGS = f"{INCLUDE_FLAGS} -D_LANGUAGE_C -DUSE_INCLUDE_ASM -P -MMD -MP -undef -Wall -lang-c -nostdinc"
    MASPSX_FLAGS  = f"--aspsx-version=2.77 --run-assembler"
    ICONV_FLAGS = f"-f UTF-8 -t SHIFT-JIS $in -o $out"
elif sys.platform == "win32":
    CPP_FLAGS = f"{INCLUDE_FLAGS} -D_LANGUAGE_C -DUSE_INCLUDE_ASM -P -MMD -MP -N -Wall -I-"
    MASPSX_FLAGS  = f"--gnu-as-path {AS} --aspsx-version=2.77 --run-assembler"
    ICONV_FLAGS = f"$in $out"
CC_FLAGS      = f"{OPT_FLAGS} -mips1 -mcpu=3000 -w -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -mgas -fgnu-linker -quiet"
AS_FLAGS      = f"{ENDIAN} {INCLUDE_FLAGS} {OPT_FLAGS} -march=r3000 -mtune=r3000 -no-pad-sections"
OBJDUMP_FLAGS = f"--disassemble-all --reloc --disassemble-zeroes -Mreg-names=32"

def ninja_setup_list_add_source(target_path: str, source_path: str, ninja_file, objdiff_file, non_matching_enabled):
    
    skipAsm = ""
    nonMatching = ""
    
    if objdiff_file != None:
        skipAsm = "-DSKIP_ASM"
        nonMatching = "-DNON_MATCHING"
        source_target_path = re.sub(r"^src", r"asm", source_path)
        source_target_path = re.sub(r".c$", r".s", source_target_path)
        if sys.platform == "linux" or sys.platform == "linux2":
            expected_path = re.sub(r"^build/src", r"expected/asm", target_path)
        elif sys.platform == "win32":
            expected_path = re.sub(r"^build\\src", r"expected\\asm", target_path)
        
        if os.path.exists(source_target_path):
            if re.search("^asm.main.*", source_path):
                objdiff_file.build(outputs=f"{expected_path}.o", rule="as", inputs=source_target_path,
                    variables={
                        "DLFLAG": DL_EXE_FLAGS
                    }
                )
            else:
                objdiff_file.build(outputs=f"{expected_path}.s.o", rule="as", inputs=source_target_path,
                    variables={
                        "DLFLAG": DL_OVL_FLAGS
                    }
                )
        else:
            return
    elif non_matching_enabled != False:
        nonMatching = "-DNON_MATCHING"
    
    
    if sys.platform == "win32":
        source_path = re.sub(r"\\", r"/", source_path)
        target_path = re.sub(r"\\", r"/", target_path)
    
    # Checks if the path indicates that the source file comes from a map file
    # in order to asign map flag
    if re.search("^src.maps.*", source_path):
        mapId = (re.search("map\d_s\d\d", source_path)[0]).upper()
        ninja_file.build(
            outputs=f"{target_path}.i", rule="cpp", inputs=source_path,
            variables={
                "MAPIDFLAG": f"-D{mapId}",
                "SKIPASMFLAG": skipAsm,
                "NONMATCHINGFLAG": nonMatching
            }
        )
    else:
        mapId = ""
        ninja_file.build(
            outputs=f"{target_path}.i", rule="cpp", inputs=source_path,
            variables={
                "MAPIDFLAG": "",
                "SKIPASMFLAG": skipAsm,
                "NONMATCHINGFLAG": nonMatching
            }
        )
    
    # Checks if the file is part from a memcard file (bodyprog) in order
    # to enable iconv conversion, otherwise checks if the files is from
    # the executable or an overlay in order to asign the intended DL flag
    if re.search("^src.bodyprog.memcard*", source_path):
        ninja_file.build(
            outputs=f"{target_path}.sjis.i", rule="iconv", inputs=f"{target_path}.i", implicit=f"{target_path}.i"
        )
        ninja_file.build(
            outputs=f"{target_path}.c.s", rule="cc", inputs=f"{target_path}.sjis.i", implicit=f"{target_path}.sjis.i",
            variables={
                "DLFLAG": DL_OVL_FLAGS
            }
        )
    elif re.search("^src.main.*", source_path):
        ninja_file.build(
            outputs=f"{target_path}.c.s", rule="cc", inputs=f"{target_path}.i",
            variables={
                "DLFLAG": DL_EXE_FLAGS
            }
        )
    else:
        ninja_file.build(
            outputs=f"{target_path}.c.s", rule="cc", inputs=f"{target_path}.i",
            variables={
                "DLFLAG": DL_OVL_FLAGS
            }
        )
    
    # Checks if the file are either `smf_io` or `smf_mid` (bodyprog) in order
    # to enable `--expand-div` parameter, otherwise checks if the files is
    # from the executable or an overlay in order to asign the intended DL flag
    if re.search("smf_io", source_path) or re.search("smf_mid", source_path):
        ninja_file.build(
            outputs=f"{target_path}.c.o", rule="maspsx", inputs=f"{target_path}.c.s",
            variables={
                "EXPANDIVFLAG": "--expand-div",
                "DLFLAG": DL_OVL_FLAGS
            }
        )
    elif re.search("^src.main.*", source_path):
        ninja_file.build(
            outputs=f"{target_path}.c.o", rule="maspsx", inputs=f"{target_path}.c.s",
            variables={
                "EXPANDIVFLAG": "",
                "DLFLAG": DL_EXE_FLAGS
            }
        )
    else:
        ninja_file.build(
            outputs=f"{target_path}.c.o", rule="maspsx", inputs=f"{target_path}.c.s",
            variables={
                "EXPANDIVFLAG": "",
                "DLFLAG": DL_OVL_FLAGS
            }
        )

def ninja_setup_main(game_version_idx: int, split_entries, skip_checksum: bool, non_matching: bool):

    ninja = ninja_syntax.Writer(open(str("build.ninja"), "w", encoding="utf-8"), width=9999)
    
    ninja.rule(
        "as", description="as $in",
        command=f"{AS} {AS_FLAGS} $DLFLAG -o $out $in",
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
        command=f"{ICONV} {ICONV_FLAGS}",
    )

    ninja.rule(
        "objdump", description="objdump $in",
        command=f"{OBJDUMP} {OBJDUMP_FLAGS} $in > $out",
    )

    ninja.rule(
        "maspsx", description="maspsx $in",
        command=f"{MASPSX} {MASPSX_FLAGS} $EXPANDIVFLAG {AS_FLAGS} $DLFLAG -o $out $in",
    )
    
    ninja.rule(
        "ld", description="link $out",
        command=f"{LD} {ENDIAN} {OPT_FLAGS} -nostdlib --no-check-sections -r -b binary -o $out $in",
    )
    
    ninja.rule(
        "elf", description="elf $out.elf",
        command=f"{LD} {ENDIAN} {OPT_FLAGS} -nostdlib --no-check-sections -Map $out.map -T $in -T $undef_sym_path -T $undef_fun_path -T {CONFIG_DIR}/{GAMEVERSIONS[game_version_idx].GAME_SETUP_INFO.GAME_VERSION_DIR}/lib_externs.ld -o $out",
    )
    
    ninja.rule(
        "objcopy", description="objcopy $out",
        command=f"{OBJCOPY} -O binary $in $out",
    )
    
    if sys.platform == "linux" or sys.platform == "linux2":
        ninja.rule(
            "sha256sum", description="checksum",
            command=f"sha256sum --ignore-missing --check $in",
        )
    elif sys.platform == "win32":
        ninja.rule(
            "sha256sum", description="checksum",
            command=f"cmd.exe /c {TOOLS_DIR}\\sha256sum.bat $in",
        )
    
    ninja.rule(
        "postbuild", description="postbuild script $in",
        command=f"{POSTBUILD} $in",
    )
    
    elfBuildRequirements = []
    checksumBuildRequirements = []
    entriesPaths = []
    
    # Build all the objects
    for split_config in split_entries:
        match split_config.SPLIT_BASENAME:
            case "main":
                os.system(f"{PREBUILD} main")
            case "BODYPROG.BIN":
                os.system(f"{PREBUILD} bodyprog")
            case "STREAM.BIN":
                os.system(f"{PREBUILD} stream")
        
        for split_entry in split_config.SPLIT_ENTRIES:
            for entry in split_entry:
                seg = entry.segment
                
                if entry.object_path is None:
                    continue
                
                if seg.type[0] == ".":
                    continue
                    
                
                match seg.type:
                    case "asm" | "data" | "sdata" | "bss" | "sbss" | "rodata" | "header":
                        if re.search("^asm.main.*", str(entry.src_paths[0])):
                            ninja.build(outputs=str(entry.object_path), rule="as", inputs=str(entry.src_paths[0]),
                                variables={
                                    "DLFLAG": DL_EXE_FLAGS
                                }
                            )
                        else:
                            ninja.build(outputs=str(entry.object_path), rule="as", inputs=str(entry.src_paths[0]),
                                variables={
                                    "DLFLAG": DL_OVL_FLAGS
                                }
                            )
                    case "c":
                        ninja_setup_list_add_source(str(entry.object_path).removesuffix(".c.o"), str(entry.src_paths[0]), ninja, None, non_matching)
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
        
        if split_config.SPLIT_BASENAME == "1ST/BODYPROG.BIN" or split_config.SPLIT_BASENAME == "VIN/STREAM.BIN":
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
        
        if sys.platform == "linux" or sys.platform == "linux2":
            checksumTarget = f"{CONFIG_DIR}/{GAMEVERSIONS[game_version_idx].GAME_SETUP_INFO.GAME_VERSION_DIR}/checksum.sha"
        elif sys.platform == "win32":
            checksumTarget = f"{CONFIG_DIR}/{GAMEVERSIONS[game_version_idx].GAME_SETUP_INFO.GAME_VERSION_DIR}"
        
        ninja.build(
            outputs=f"{BUILD_DIR}/out/checksum.ok",
            rule="sha256sum",
            inputs=checksumTarget,
            implicit=checksumBuildRequirements
        )

def ninja_setup_objdiff(split_entries):

    ninja = ninja_syntax.Writer(open(str("build.ninja"), "w", encoding="utf-8"), width=9999)
    objdiff = ninja_syntax.Writer(open(str("objdiff.ninja"), "w", encoding="utf-8"), width=9999)
    
    objdiff.rule(
        "as", description="as $in",
        command=f"{AS} {AS_FLAGS} $DLFLAG -o $out $in",
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
        command=f"{ICONV} {ICONV_FLAGS}",
    )

    ninja.rule(
        "maspsx", description="maspsx $in",
        command=f"{MASPSX} {MASPSX_FLAGS} $EXPANDIVFLAG {AS_FLAGS} $DLFLAG -o $out $in",
    )
    
    objdiff.rule(
        "objdiff-config", description="objdiff-config",
        command=f"{PYTHON} {OBJDIFF_GENSCRIPT} --ninja $in",
    )
    
    # Build all the objects
    for split_config in split_entries:
        for split_entry in split_config.SPLIT_ENTRIES:
            for entry in split_entry:
                seg = entry.segment
                
                if entry.object_path is None:
                    continue
                
                if seg.type[0] == ".":
                    continue
                    
                if seg.type == "c":
                    ninja_setup_list_add_source(str(entry.object_path).removesuffix(".c.o"), str(entry.src_paths[0]), ninja, objdiff, False)
    
    if sys.platform == "linux" or sys.platform == "linux2":
        objdiff.build(outputs=f"{EXPECTED_DIR}/objdiff.ok", rule="objdiff-config", inputs=f"{OBJDIFF_DIR}/config.yaml")
    elif sys.platform == "win32":
        objdiff.build(outputs=f"{EXPECTED_DIR}\\objdiff.ok", rule="objdiff-config", inputs=f"{OBJDIFF_DIR}\\config.yaml")

def ninja_append(split_entries, objdiff_mode: bool):
    """Horrid code - Will"""
    if objdiff_mode:
        ninjaFileRead   = open("build.ninja", "r", encoding="utf-8").read()
        ninjaFile       = open("build.ninja", "w", encoding="utf-8")
        ninjaFile.write(ninjaFileRead)
        ninjaFileSyntax = ninja_syntax.Writer(ninjaFile, width=9999)
        objdiffFileRead   = open("objdiff.ninja", "r", encoding="utf-8").read()
        objdiffFile       = open("objdiff.ninja", "w", encoding="utf-8")
        objdiffFileEndPos = re.search(r"build expected\\objdiff", objdiffFileRead).start()
        print(f"objdiffFileEndPos: {objdiffFileEndPos}")
        objdiffFile.write(objdiffFileRead[0:objdiffFileEndPos])
        objdiffFileSyntax = ninja_syntax.Writer(objdiffFile, width=9999)
    else:
        print("Normal append mode uninplemented")
        return
    
    for split_config in split_entries:
        for split_entry in split_config.SPLIT_ENTRIES:
            for entry in split_entry:
                seg = entry.segment
                
                if entry.object_path is None or seg.type[0] == ".":
                    continue
                
                if objdiff_mode:
                    source_path = str(entry.src_paths[0])
                    if sys.platform == "linux" or sys.platform == "linux2":
                        expected_path = re.sub(r"^build/src", r"expected/asm", f"{str(entry.object_path).removesuffix(".c.o")}.s.o")
                    elif sys.platform == "win32":
                        expected_path = re.sub(r"^build\\src", r"expected\\asm", f"{str(entry.object_path).removesuffix(".c.o")}.s.o")
                    
                    if source_path in ninjaFileRead or expected_path in objdiffFileRead or source_path in objdiffFileRead or expected_path in ninjaFileRead:
                        #print(f"{source_path} / {expected_path} | PREVIOUSLY ADDED")
                        continue
                    else:
                        #print(f"{source_path} / {expected_path} | NEWLY ADDED")
                        if seg.type == "c":
                            ninja_setup_list_add_source(str(entry.object_path).removesuffix(".c.o"), str(entry.src_paths[0]), ninjaFileSyntax, objdiffFileSyntax, True)
    
    if objdiff_mode:
        if sys.platform == "linux" or sys.platform == "linux2":
            objdiffFileSyntax.build(outputs=f"{EXPECTED_DIR}/objdiff.ok", rule="objdiff-config", inputs=f"{OBJDIFF_DIR}/config.yaml")
        elif sys.platform == "win32":
            objdiffFileSyntax.build(outputs=f"{EXPECTED_DIR}\\objdiff.ok", rule="objdiff-config", inputs=f"{OBJDIFF_DIR}\\config.yaml")
    
    
    

def clean_working_files(clean_build_files: bool):
    shutil.rmtree(BUILD_DIR, ignore_errors=True)
    shutil.rmtree(PERMUTER_DIR, ignore_errors=True)
    if os.path.exists(".splache"):
        os.remove(".splache")

    if clean_build_files:
        if os.path.exists("build.ninja"):
            os.remove("build.ninja")
        if os.path.exists("objdiff.ninja"):
            os.remove("objdiff.ninja")
        if os.path.exists(".ninja_log"):
            os.remove(".ninja_log")
        shutil.rmtree(ASM_DIR, ignore_errors=True)
        shutil.rmtree(EXPECTED_DIR, ignore_errors=True)
        shutil.rmtree(LINKER_DIR, ignore_errors=True)

def extract_files(version: int):
    print(f"Extracting files for version {GAMEVERSIONS[version].GAME_NAME_VERSION}")
    
    targetAssets = f"{ASSETS_DIR}/{GAMEVERSIONS[version].GAME_SETUP_INFO.GAME_VERSION_DIR}"
    targetRom    = f"{ROM_DIR}/{GAMEVERSIONS[version].GAME_SETUP_INFO.GAME_VERSION_DIR}"
    
    shutil.rmtree(targetAssets, ignore_errors=True)
    shutil.rmtree(targetRom, ignore_errors=True)
    
    dumpsxisoFlags = f"-x {ROM_DIR}/{GAMEVERSIONS[version].GAME_SETUP_INFO.GAME_VERSION_DIR} -s {ROM_DIR}/{GAMEVERSIONS[version].GAME_SETUP_INFO.GAME_VERSION_DIR}/layout.xml {IMAGE_DIR}/{GAMEVERSIONS[version].GAME_SETUP_INFO.GAME_NAME}.bin"

    os.system(f"{DUMPSXISO} {dumpsxisoFlags}")
    subprocess.call([PYTHON, f"{TOOLS_DIR}/silentassets/extract.py",
    "-exe", f"{targetRom}/{GAMEVERSIONS[version].GAME_SETUP_INFO.GAME_FILE_EXE}",
    "-fs", f"{targetRom}/{GAMEVERSIONS[version].GAME_SETUP_INFO.GAME_FILE_SILENT}",
    "-fh", f"{targetRom}/{GAMEVERSIONS[version].GAME_SETUP_INFO.GAME_FILE_HILL}",
    targetAssets])

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
        type=str
    )
    parser.add_argument(
        "-set", "--setup",
        help="Setup individual overlays or the executable only",
        type=str
    )
    parser.add_argument(
        "-sc", "--skip_checksum",
        help="Skip checksum",
        action="store_true",
    )
    parser.add_argument(
        "-nm", "--non_matching",
        help="Compile functions labeled as Non Matching",
        action="store_true",
    )
    parser.add_argument(
        "-obj", "--objdiff_config",
        help="Builds setup for Objdiff",
        action="store_true",
    )
    parser.add_argument(
        "-ver", "--game_version",
        help="Extract and work under a specific version of the game (NOT IMPLEMENTED)",
        type=str,
    )
    args = parser.parse_args()

    cleanCompilationFiles = (args.clean) or False
    skipChecksumOption    = (args.skip_checksum) or False
    objdiffConfigOption   = (args.objdiff_config) or False
    nonMatchingOption     = (args.non_matching) or False
    gameVersionOption     = 0 # USA by default
    yamlsPaths            = []
    splitsYamlInfo        = []
    regenMode             = False
    
    
    if args.game_version != None:
        for gameVersionInfo in GAMEVERSIONS:
            if args.game_version.upper() == gameVersionInfo.GAME_NAME_VERSION:
                print(f"Version selected: {gameVersionInfo.GAME_NAME_VERSION}")
                gameVersionOption = gameVersionInfo.GAME_IDX
                break
        else:
            print("Version not supported.")
            sys.exit(1)
    
    if cleanCompilationFiles:
        print("Cleaning compilation files")
        clean_working_files(False)
        return
    
    if args.iso_extract != None:
        extract_files(gameVersionOption)
        return
    
    if gameVersionOption != 0:
        print("Support for other versions of the game haven't been implemented as we are still focused on the USA retail release.")
        sys.exit(1)
    
    if args.setup == None:
        yamlsPaths.extend(YAML_EXECUTABLE)
        yamlsPaths.extend(YAML_ENGINE)
        yamlsPaths.extend(YAML_SCREENS)
        yamlsPaths.extend(YAML_MAPS_0)
        yamlsPaths.extend(YAML_MAPS_1)
        yamlsPaths.extend(YAML_MAPS_2)
        yamlsPaths.extend(YAML_MAPS_3)
        yamlsPaths.extend(YAML_MAPS_4)
        yamlsPaths.extend(YAML_MAPS_5)
        yamlsPaths.extend(YAML_MAPS_6)
        yamlsPaths.extend(YAML_MAPS_7)
    else:
        matchSet = ""
        if len(args.setup) == 3:
            matchSet = args.setup.lower()
        elif len(args.setup) == 4:
            matchSet = args.setup.lower()[0:3]
            if args.setup.lower()[3] == "r":
                regenMode = True
        
        match matchSet:
            case "exe":
                yamlsPaths.extend(YAML_EXECUTABLE)
            case "eng":
                yamlsPaths.extend(YAML_ENGINE)
            case "bko":
                yamlsPaths.extend([YAML_SCREENS[0]])
            case "fmv" | "str":
                yamlsPaths.extend([YAML_SCREENS[1]])
            case "opt":
                yamlsPaths.extend([YAML_SCREENS[2]])
            case "cre":
                yamlsPaths.extend([YAML_SCREENS[3]])
            case "sav":
                yamlsPaths.extend([YAML_SCREENS[4]])
            case "scr":
                yamlsPaths.extend(YAML_SCREENS)
            case "map":
                yamlsPaths.extend(YAML_MAPS_0)
                yamlsPaths.extend(YAML_MAPS_1)
                yamlsPaths.extend(YAML_MAPS_2)
                yamlsPaths.extend(YAML_MAPS_3)
                yamlsPaths.extend(YAML_MAPS_4)
                yamlsPaths.extend(YAML_MAPS_5)
                yamlsPaths.extend(YAML_MAPS_6)
                yamlsPaths.extend(YAML_MAPS_7)
            case _:
                try:
                    if re.match(r"m\d\dr?", matchSet):
                        yamlsPaths.extend([globals()[f"YAML_MAPS_{int(args.setup[1])}"][int(args.setup[2])]])
                    elif re.match(r"m\dxr?", matchSet):
                        yamlsPaths.extend(globals()[f"YAML_MAPS_{int(args.setup[1])}"])
                    else:
                        print("No recognizable overlay has been assigned.")
                        sys.exit(1)
                except:
                    print("Map overlay(s) not found.")
                    sys.exit(1)
    
    if regenMode == False:
        clean_working_files(True)
    else:
        appendSplits = []
        for asm_path in yamlsPaths:
            shutil.rmtree(f"{BUILD_DIR}/src/{asm_path.split(".yaml")[0]}", ignore_errors=True)
            if os.path.exists(f"{ASM_DIR}/{asm_path.split(".yaml")[0]}") == False:
                appendSplits += [asm_path]
            else:
                shutil.rmtree(f"{ASM_DIR}/{asm_path.split(".yaml")[0]}", ignore_errors=True)
    
    for yaml in yamlsPaths:
        splat.util.symbols.spim_context = spimdisasm.common.Context()
        splat.util.symbols.reset_symbols()
        split.main([Path(f"{CONFIG_DIR}/{GAMEVERSIONS[gameVersionOption].GAME_SETUP_INFO.GAME_VERSION_DIR}/{yaml}")], modes="all", use_cache=False, verbose=False, disassemble_all=True, make_full_disasm_for_code=True)
        if regenMode == True and appendSplits != []:
            for splitToAppend in appendSplits:
                if yaml == splitToAppend:
                    splitsYamlInfo.append(YAML_INFO([split.linker_writer.entries], split.config['options']['basename'], split.config['options']['ld_script_path'], split.config['options']['undefined_funcs_auto_path'], split.config['options']['undefined_syms_auto_path']))
        elif regenMode == False:
            splitsYamlInfo.append(YAML_INFO([split.linker_writer.entries], split.config['options']['basename'], split.config['options']['ld_script_path'], split.config['options']['undefined_funcs_auto_path'], split.config['options']['undefined_syms_auto_path']))
    
    
    if regenMode == False:
        if objdiffConfigOption == False:
            ninja_setup_main(gameVersionOption, splitsYamlInfo, skipChecksumOption, nonMatchingOption)
        else:
            ninja_setup_objdiff(splitsYamlInfo)
    else:
        ninja_append(splitsYamlInfo, objdiffConfigOption)
    
    if objdiffConfigOption:
        subprocess.call([PYTHON, "-m", "ninja", "-f", "objdiff.ninja"])
        

if __name__ == "__main__":
    main()
