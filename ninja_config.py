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
    GAMEVERSIONINFO(1, "EUR",
        GAMEVERSIONSETUPINFO("SLES-01514", "EUR", "SLES_015.14", f"SILENT{GAMEFILE_EXTENSION}", f"HILL{GAMEFILE_EXTENSION}")
    ),
    GAMEVERSIONINFO(2, "JAP0",
        GAMEVERSIONSETUPINFO("SLPM-86192", "JAP0", "SLPM_861.92", f"SILENT{GAMEFILE_EXTENSION}", f"HILL{GAMEFILE_EXTENSION}")
    ),
    GAMEVERSIONINFO(3, "JAP1",
        GAMEVERSIONSETUPINFO("SLPM-86498", "JAP1", "SLPM_861.92", f"SILENT{GAMEFILE_EXTENSION}", f"HILL{GAMEFILE_EXTENSION}")
    ),
    GAMEVERSIONINFO(4, "JAP2",
        GAMEVERSIONSETUPINFO("SLPM-87029", "JAP2", "SLPM_861.92", f"SILENT{GAMEFILE_EXTENSION}", f"HILL{GAMEFILE_EXTENSION}")
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
YAML_ITEMS = [
    "items/item_eng.yaml",
    "items/item_ger.yaml",
    "items/item_frn.yaml",
    "items/item_itl.yaml",
    "items/item_spn.yaml"
]
YAML_MAPS_0 = [
    "maps/map0_s00.yaml",
    "maps/map0_s01.yaml",
    "maps/map0_s02.yaml"
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
    PYTHON = "python"
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
    CC272             = f"{TOOLS_DIR}/gcc-2.7.2-cdk/cc1"
    OBJDIFF           = f"{OBJDIFF_DIR}/objdiff"
    OBJDIFF_GENSCRIPT = f"{OBJDIFF_DIR}/objdiff_generate.py"
    POSTBUILD         = f"{PYTHON} {TOOLS_DIR}/postbuild.py"
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
    CC272             = f"{TOOLS_DIR}/win-build/gcc-2.7.2-win/cc1psx.exe"
    OBJDIFF           = f"{OBJDIFF_DIR}\\objdiff.exe"
    OBJDIFF_GENSCRIPT = f"{OBJDIFF_DIR}\\objdiff_generate.py"
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
    MASPSX_FLAGS  = f"--gnu-as-path {AS} --run-assembler"
    ICONV_FLAGS = f"$in $out"
CC_FLAGS      = f"{OPT_FLAGS} -mips1 -mcpu=3000 -w -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -mgas -fgnu-linker -quiet"
AS_FLAGS      = f"{ENDIAN} {INCLUDE_FLAGS} {OPT_FLAGS} -march=r3000 -mtune=r3000 -no-pad-sections"
OBJDUMP_FLAGS = f"--disassemble-all --reloc --disassemble-zeroes -Mreg-names=32"

TARGETS_POSTBUILD = ["1ST/BODYPROG.BIN", "VIN/STREAM.BIN", "VIN/MAP3_S06.BIN", "VIN/MAP4_S05.BIN", "VIN/MAP5_S01.BIN"]

def ninja_setup_list_add_source(target_path: str, source_path: str, ninjaFile, objdiff_file, non_matching_enabled, game_version_idx: int):
    
    skipAsm = ""
    nonMatching = ""
    
    if objdiff_file != None:
        skipAsm = "-DSKIP_ASM"
        nonMatching = "-DNON_MATCHING"
        if sys.platform == "linux" or sys.platform == "linux2":
            source_target_path = re.sub(r"^src", fr"asm/{GAMEVERSIONS[game_version_idx].GAME_NAME_VERSION}", source_path)
        elif sys.platform == "win32":
            source_target_path = re.sub(r"^src", fr"asm\\{GAMEVERSIONS[game_version_idx].GAME_NAME_VERSION}", source_path)
        source_target_path = re.sub(r".c$", r".s", source_target_path)
        if sys.platform == "linux" or sys.platform == "linux2":
            expected_path = re.sub(fr"^build/{GAMEVERSIONS[game_version_idx].GAME_NAME_VERSION}/src", fr"expected/{GAMEVERSIONS[game_version_idx].GAME_NAME_VERSION}", target_path)
        elif sys.platform == "win32":
            expected_path = re.sub(fr"^build\\{GAMEVERSIONS[game_version_idx].GAME_NAME_VERSION}\\src", fr"expected\\{GAMEVERSIONS[game_version_idx].GAME_NAME_VERSION}", target_path)
        
        if os.path.exists(source_target_path):
            if re.search("^asm.(USA|EUR|JAP0|JAP1|JAP2).main.*", source_path):
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
    
    if non_matching_enabled:
        nonMatching = "-DNON_MATCHING"
    
    
    if sys.platform == "win32":
        source_path = re.sub(r"\\", r"/", source_path)
        target_path = re.sub(r"\\", r"/", target_path)
    
    # Checks if the path indicates that the source file comes from a map file
    # in order to asign map flag
    if re.search("^src.maps.*", source_path):
        mapId = (re.search("map\d_s\d\d", source_path)[0]).upper()
        ninjaFile.build(
            outputs=f"{target_path}.i", rule="cpp", inputs=source_path,
            variables={
                "VERSION": f"-DVER_{GAMEVERSIONS[game_version_idx].GAME_NAME_VERSION}",
                "MAPIDFLAG": f"-D{mapId}",
                "SKIPASMFLAG": skipAsm,
                "NONMATCHINGFLAG": nonMatching
            }
        )
    else:
        mapId = ""
        ninjaFile.build(
            outputs=f"{target_path}.i", rule="cpp", inputs=source_path,
            variables={
                "VERSION": f"-DVER_{GAMEVERSIONS[game_version_idx].GAME_NAME_VERSION}",
                "MAPIDFLAG": "",
                "SKIPASMFLAG": skipAsm,
                "NONMATCHINGFLAG": nonMatching
            }
        )
    
    # Checks:
    # Enables SHIFT-JIS conversion if the file is part from a memcard file (bodyprog)
    # Assign proper DL flag for the executable or the overlays
    # Assign proper compiler version for the `lib_unk` compilation
    if re.search("^src.bodyprog.memcard*", source_path):
        ninjaFile.build(
            outputs=f"{target_path}.sjis.i", rule="iconv", inputs=f"{target_path}.i", implicit=f"{target_path}.i"
        )
        ninjaFile.build(
            outputs=f"{target_path}.c.s", rule="cc", inputs=f"{target_path}.sjis.i", implicit=f"{target_path}.sjis.i",
            variables={
                "DLFLAG": DL_OVL_FLAGS
            }
        )
    elif re.search("^src.main.*", source_path):
        ninjaFile.build(
            outputs=f"{target_path}.c.s", rule="cc", inputs=f"{target_path}.i",
            variables={
                "DLFLAG": DL_EXE_FLAGS
            }
        )
    elif re.search("^src.bodyprog.lib_unk.*", source_path):
        ninjaFile.build(
            outputs=f"{target_path}.c.s", rule="cc272", inputs=f"{target_path}.i",
            variables={
                "DLFLAG": DL_OVL_FLAGS
            }
        )
    else:
        ninjaFile.build(
            outputs=f"{target_path}.c.s", rule="cc", inputs=f"{target_path}.i",
            variables={
                "DLFLAG": DL_OVL_FLAGS
            }
        )
    
    # Checks:
    # Enables `--expand-div` for `smf_io` or `smf_mid`
    # Assign proper DL flag for the executable or the overlays
    # Assign proper assembler version for the `lib_unk` compilation
    maspxVersion = "2.77"
    if re.search("smf_io", source_path) or re.search("smf_mid", source_path):
        ninjaFile.build(
            outputs=f"{target_path}.c.o", rule="maspsx", inputs=f"{target_path}.c.s",
            variables={
                "EXPANDIVFLAG": "--expand-div",
                "DLFLAG": DL_OVL_FLAGS,
                "MASPSXVER": maspxVersion
            }
        )
    elif re.search("^src.main.*", source_path):
        ninjaFile.build(
            outputs=f"{target_path}.c.o", rule="maspsx", inputs=f"{target_path}.c.s",
            variables={
                "EXPANDIVFLAG": "",
                "DLFLAG": DL_EXE_FLAGS,
                "MASPSXVER": maspxVersion
            }
        )
    elif re.search("^src.bodyprog.lib_unk.*", source_path):
        maspxVersion = "2.67"
        ninjaFile.build(
            outputs=f"{target_path}.c.o", rule="maspsx", inputs=f"{target_path}.c.s",
            variables={
                "EXPANDIVFLAG": "",
                "DLFLAG": DL_OVL_FLAGS,
                "MASPSXVER": maspxVersion
            }
        )
    else:
        ninjaFile.build(
            outputs=f"{target_path}.c.o", rule="maspsx", inputs=f"{target_path}.c.s",
            variables={
                "EXPANDIVFLAG": "",
                "DLFLAG": DL_OVL_FLAGS,
                "MASPSXVER": maspxVersion
            }
        )
    
    
    if objdiff_file != None:
        return f"{expected_path}.s.o"

def ninja_build(split_entries, game_version_idx: int, objdiff_mode: bool, skip_checksum: bool, non_matching: bool):

    if objdiff_mode:
        ninjaFile            = ninja_syntax.Writer(open("matching.ninja", "w", encoding="utf-8"), width=9999)
        ninjaDiffFile        = ninja_syntax.Writer(open("objdiff.ninja", "w", encoding="utf-8"), width=9999)
        ninjaDiffFile.include("rules.ninja")
        ninjaNonmatchingFile = ninja_syntax.Writer(open("build.ninja", "w", encoding="utf-8"), width=9999)
        ninjaNonmatchingFile.include("rules.ninja")
    else:
        ninjaFile = ninja_syntax.Writer(open("build.ninja", "w", encoding="utf-8"), width=9999)
    
    ninjaFile.include("rules.ninja")
    
    ninjaRulesFile = ninja_syntax.Writer(open("rules.ninja", "w", encoding="utf-8"), width=9999)
    
    ninjaRulesFile.rule(
        "as", description="as $in",
        command=f"{AS} {AS_FLAGS} $DLFLAG -o $out $in"
    )

    ninjaRulesFile.rule(
        "cc", description="cc $in",
        command=f"{CC} {CC_FLAGS} $DLFLAG -o $out $in",
    )
    
    ninjaRulesFile.rule(
        "cc272", description="cc272 $in",
        command=f"{CC272} {CC_FLAGS} $DLFLAG -o $out $in",
    )
    
    ninjaRulesFile.rule(
        "cpp", description="cpp $in",
        command=f"{CPP} -P -MMD -MP -MT $out -MF $out.d {CPP_FLAGS} $VERSION $MAPIDFLAG $SKIPASMFLAG $NONMATCHINGFLAG -o $out $in",
        depfile="$out.d"
    )

    ninjaRulesFile.rule(
        "iconv", description="iconv $in",
        command=f"{ICONV} {ICONV_FLAGS}",
    )

    ninjaRulesFile.rule(
        "objdump", description="objdump $in",
        command=f"{OBJDUMP} {OBJDUMP_FLAGS} $in > $out",
    )

    ninjaRulesFile.rule(
        "maspsx", description="maspsx $in",
        command=f"{MASPSX} {MASPSX_FLAGS} --aspsx-version=$MASPSXVER $EXPANDIVFLAG {AS_FLAGS} $DLFLAG -o $out $in",
    )
    
    ninjaRulesFile.rule(
        "ld", description="link $out",
        command=f"{LD} {ENDIAN} {OPT_FLAGS} -nostdlib --no-check-sections -r -b binary -o $out $in",
    )
    if game_version_idx == 0:
        ninjaRulesFile.rule(
            "elf", description="elf $out",
            command=f"{LD} {ENDIAN} {OPT_FLAGS} -nostdlib --no-check-sections -Map $out.map -T $in -T $undef_sym_path -T $undef_fun_path -T {CONFIG_DIR}/{GAMEVERSIONS[game_version_idx].GAME_SETUP_INFO.GAME_VERSION_DIR}/lib_externs.ld -o $out",
        )
    else:
        ninjaRulesFile.rule(
            "elf", description="elf $out",
            command=f"{LD} {ENDIAN} {OPT_FLAGS} -nostdlib --no-check-sections -Map $out.map -T $in -T $undef_sym_path -T $undef_fun_path -o $out",
        )
    
    ninjaRulesFile.rule(
        "objcopy", description="objcopy $out",
        command=f"{OBJCOPY} -O binary $in $out",
    )
    
    if sys.platform == "linux" or sys.platform == "linux2":
        ninjaRulesFile.rule(
            "sha256sum", description="checksum",
            command=f"sha256sum --ignore-missing --check $in",
        )
    elif sys.platform == "win32":
        ninjaRulesFile.rule(
            "sha256sum", description="checksum",
            command=f"cmd.exe /c {TOOLS_DIR}\\sha256sum.bat $in",
        )
    
    ninjaRulesFile.rule(
        "postbuild", description="postbuild script $in",
        command=f"{POSTBUILD} $in",
    )
    
    ninjaRulesFile.rule(
        "objdiff-config", description="objdiff-config",
        command=f"{PYTHON} {OBJDIFF_GENSCRIPT} --ninja $in $version",
    )
    
    elfBuildRequirements = []
    checksumBuildRequirements = []
    entriesPaths = []
    objdiffConfigRequirements = []
    
    # Build all the objects
    for split_config in split_entries:        
        for split_entry in split_config.SPLIT_ENTRIES:
            for entry in split_entry:
                seg = entry.segment
                
                if entry.object_path is None:
                    continue
                
                if seg.type[0] == ".":
                    continue
                    
                source_path = str(entry.src_paths[0])
                target_path = str(entry.object_path)
                
                match seg.type:
                    case "asm" | "data" | "sdata" | "bss" | "sbss" | "rodata" | "header":
                        if re.search("^asm.(USA|EUR|JAP0|JAP1|JAP2).main.*", source_path):
                            ninjaFile.build(outputs=target_path, rule="as", inputs=source_path,
                                variables={
                                    "DLFLAG": DL_EXE_FLAGS
                                }
                            )
                        else:
                            ninjaFile.build(outputs=target_path, rule="as", inputs=source_path,
                                variables={
                                    "DLFLAG": DL_OVL_FLAGS
                                }
                            )
                    case "c":
                        ninja_setup_list_add_source(target_path.removesuffix(".c.o"), source_path, ninjaFile, None, non_matching, game_version_idx)
                        
                        if objdiff_mode:
                            if sys.platform == "linux" or sys.platform == "linux2":
                                expected_path = re.sub(fr"^build/{GAMEVERSIONS[game_version_idx].GAME_NAME_VERSION}/src", fr"expected/{GAMEVERSIONS[game_version_idx].GAME_NAME_VERSION}/asm", f"{target_path}.s.o")
                            elif sys.platform == "win32":
                                expected_path = re.sub(fr"^build\\{GAMEVERSIONS[game_version_idx].GAME_NAME_VERSION}\\src", fr"expected\\{GAMEVERSIONS[game_version_idx].GAME_NAME_VERSION}\\asm", f"{target_path}.s.o")
                            
                            tempVar = [ninja_setup_list_add_source(target_path.removesuffix(".c.o"), source_path, ninjaNonmatchingFile, ninjaDiffFile, True, game_version_idx)]
                            if tempVar != [None]:
                                objdiffConfigRequirements += tempVar
                    case "bin":
                        ninjaFile.build(outputs=target_path, rule="ld", inputs=source_path)
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
        
        
        if split_config.SPLIT_BASENAME == "main":
            output = f"{BUILD_DIR}/{GAMEVERSIONS[game_version_idx].GAME_SETUP_INFO.GAME_VERSION_DIR}/out/SLUS_007.07"
        else:
            output = f"{BUILD_DIR}/{GAMEVERSIONS[game_version_idx].GAME_SETUP_INFO.GAME_VERSION_DIR}/out/{split_config.SPLIT_BASENAME}"
        
        ninjaFile.build(
            outputs=f"{output}.elf",
            rule="elf",
            inputs=split_config.SPLIT_LINKER,
            variables={
                "undef_sym_path": split_config.SPLIT_UNDEF_SYM,
                "undef_fun_path": split_config.SPLIT_UNDEF_FUN,
            },
            implicit=elfBuildRequirements
        )
        ninjaFile.build(
            outputs=output,
            rule="objcopy",
            inputs=f"{output}.elf",
            implicit=f"{output}.elf"
        )
        
        if split_config.SPLIT_BASENAME in TARGETS_POSTBUILD:
            ninjaFile.build(
                outputs=f"{output}.fix",
                rule="postbuild",
                inputs=output,
                implicit=output
            )
        
        checksumBuildRequirements += [str(s) for s in [output]]
    
    if objdiff_mode:
        if sys.platform == "linux" or sys.platform == "linux2":
            ninjaDiffFile.build(outputs=f"{EXPECTED_DIR}/{GAMEVERSIONS[game_version_idx].GAME_NAME_VERSION}/objdiff.ok", rule="objdiff-config", inputs=f"{OBJDIFF_DIR}/config-retail.yaml", variables={ "version": GAMEVERSIONS[game_version_idx].GAME_SETUP_INFO.GAME_VERSION_DIR }, implicit=objdiffConfigRequirements)
        elif sys.platform == "win32":
            ninjaDiffFile.build(outputs=f"{EXPECTED_DIR}\\{GAMEVERSIONS[game_version_idx].GAME_NAME_VERSION}\\objdiff.ok", rule="objdiff-config", inputs=f"{OBJDIFF_DIR}\\config-retail.yaml",
            variables={ "version": GAMEVERSIONS[game_version_idx].GAME_SETUP_INFO.GAME_VERSION_DIR }, implicit=objdiffConfigRequirements)
    
    if skip_checksum != True:
        for s in range(len(checksumBuildRequirements)):
            if checksumBuildRequirements[s] == f"{BUILD_DIR}/out/VIN/STREAM.BIN" or checksumBuildRequirements[s] == f"{BUILD_DIR}/out/1ST/BODYPROG.BIN":
                checksumBuildRequirements[s] = f"{checksumBuildRequirements[s]}.fix"
        
        if sys.platform == "linux" or sys.platform == "linux2":
            checksumTarget = f"{CONFIG_DIR}/{GAMEVERSIONS[game_version_idx].GAME_SETUP_INFO.GAME_VERSION_DIR}/checksum.sha"
        elif sys.platform == "win32":
            checksumTarget = f"{CONFIG_DIR}/{GAMEVERSIONS[game_version_idx].GAME_SETUP_INFO.GAME_VERSION_DIR}"
        
        ninjaFile.build(
            outputs=f"{BUILD_DIR}/{GAMEVERSIONS[game_version_idx].GAME_SETUP_INFO.GAME_VERSION_DIR}/out/checksum.ok",
            rule="sha256sum",
            inputs=checksumTarget,
            implicit=checksumBuildRequirements
        )

def ninja_append(split_entries, skip_checksum: bool, non_matching: bool, game_version_idx: int, build_matching_nall_mode: bool):
    """Horrid code - Will"""
    
    ninjaMatchingPrefix = "build"
    objdiff_mode = False
    
    if os.path.exists("objdiff.ninja") and build_matching_nall_mode == False:
        objdiff_mode = True
    elif build_matching_nall_mode:
        ninjaMatchingPrefix = "matching"
    
    if objdiff_mode:
        ninjaFileRead     = open("build.ninja", "r", encoding="utf-8").read()
        ninjaFile         = open("build.ninja", "w", encoding="utf-8")
        ninjaFile.write(ninjaFileRead)
        ninjaFileSyntax   = ninja_syntax.Writer(ninjaFile, width=9999)
        objdiffFileRead   = open(f"objdiff.ninja", "r", encoding="utf-8").read()
        objdiffFile       = open(f"objdiff.ninja", "w", encoding="utf-8")
        if sys.platform == "linux" or sys.platform == "linux2":
            objdiffFileEndPos = re.search(r"build expected/objdiff", objdiffFileRead).start()
        elif sys.platform == "win32":
            objdiffFileEndPos = re.search(r"build expected\\objdiff", objdiffFileRead).start()
        
        objdiffFileRule   = objdiffFileRead[objdiffFileEndPos:len(objdiffFileRead)]
        objdiffFile.write(objdiffFileRead[0:objdiffFileEndPos])
        objdiffFileSyntax = ninja_syntax.Writer(objdiffFile, width=9999)
        objdiffConfigRequirements = []
    else:
        elfBuildRequirements      = []
        checksumBuildRequirements = []
        entriesPaths              = []
        ninjaFileRead             = open(f"{ninjaMatchingPrefix}.ninja", "r", encoding="utf-8").read()
        ninjaFile                 = open(f"{ninjaMatchingPrefix}.ninja", "w", encoding="utf-8")
        if non_matching:
            print("Enabled #IFDEF NON_MATCHING build.")
            ninjaFileRead = re.sub("NONMATCHINGFLAG = \r\n", "NONMATCHINGFLAG = -DNON_MATCHING\r\n", ninjaFileRead)
        
        if re.search("checksum.ok", ninjaFileRead):
            ninjaFileEndPos = re.search("build build/out/checksum.ok", ninjaFileRead).start()
        else:
            ninjaFileEndPos = len(ninjaFileRead)
        ninjaFile.write(ninjaFileRead[0:ninjaFileEndPos])
        ninjaFileSyntax   = ninja_syntax.Writer(ninjaFile, width=9999)
        if skip_checksum == False:
            checksumBuildRequirements = re.findall(r"build/out/.+\.BIN:", ninjaFileRead)
            for i in range(len(checksumBuildRequirements)):
                fixedStr = re.sub(":", "", checksumBuildRequirements[i])
                if "BODYPROG.BIN" in fixedStr or "STREAM.BIN" in fixedStr:
                    checksumBuildRequirements[i] = f"{fixedStr}.fix"
                else:
                    checksumBuildRequirements[i] = fixedStr
    
    for split_config in split_entries:                
        for split_entry in split_config.SPLIT_ENTRIES:
            for entry in split_entry:
                seg = entry.segment
                
                if entry.object_path is None or seg.type[0] == ".":
                    continue
                
                source_path = str(entry.src_paths[0])
                target_path = str(entry.object_path).removesuffix(".c.o")
                
                if objdiff_mode:
                    if sys.platform == "linux" or sys.platform == "linux2":
                        expected_path = re.sub(r"^build/src", r"expected/asm", f"{target_path}.s.o")
                    elif sys.platform == "win32":
                        expected_path = re.sub(r"^build\\src", r"expected\\asm", f"{target_path}.s.o")
                    
                    if source_path in ninjaFileRead or expected_path in objdiffFileRead or source_path in objdiffFileRead or expected_path in ninjaFileRead:
                        continue
                    else:
                        if seg.type == "c":
                            tempVar = [ninja_setup_list_add_source(target_path, source_path, ninjaFileSyntax, objdiffFileSyntax, True, game_version_idx)]
                            if tempVar != [None]:
                                objdiffConfigRequirements += tempVar
                else:
                    testVar0 = entry.src_paths[0].as_posix()
                    testVar1 = str(entry.object_path.as_posix()).removesuffix(".c.o")
                    if testVar0 in ninjaFileRead or testVar1 in ninjaFileRead:
                        continue
                    
                    match seg.type:
                        case "asm" | "data" | "sdata" | "bss" | "sbss" | "rodata" | "header":
                            if re.search("^asm.main.*", source_path):
                                ninjaFileSyntax.build(outputs=str(entry.object_path), rule="as", inputs=str(entry.src_paths[0]),
                                    variables={
                                        "DLFLAG": DL_EXE_FLAGS
                                    }
                                )
                            else:
                                ninjaFileSyntax.build(outputs=str(entry.object_path), rule="as", inputs=str(entry.src_paths[0]),
                                    variables={
                                        "DLFLAG": DL_OVL_FLAGS
                                    }
                                )
                        case "c":
                            ninja_setup_list_add_source(str(entry.object_path).removesuffix(".c.o"), str(entry.src_paths[0]), ninjaFileSyntax, None, non_matching, game_version_idx)
                        case "bin":
                            ninjaFileSyntax.build(outputs=str(entry.object_path), rule="ld", inputs=str(entry.src_paths[0]))
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
        
        if objdiff_mode != True:
            if split_config.SPLIT_BASENAME == "BODYPROG.BIN" or split_config.SPLIT_BASENAME == "B_KONAMI.BIN":
                split_config.SPLIT_BASENAME = f"1ST/{split_config.SPLIT_BASENAME}"
            elif split_config.SPLIT_BASENAME != "main":
                split_config.SPLIT_BASENAME = f"VIN/{split_config.SPLIT_BASENAME}"
            
            
            if split_config.SPLIT_BASENAME != "main":
                output = f"{BUILD_DIR}/out/{split_config.SPLIT_BASENAME}"
            else:
                output = f"{BUILD_DIR}/out/SLUS_007.07"
            
            if split_config.SPLIT_BASENAME == "1ST/BODYPROG.BIN" and game_version_idx == 0 or split_config.SPLIT_BASENAME == "VIN/STREAM.BIN" and game_version_idx == 0:
                checksumBuildRequirements += [f"{output}.fix"]
            else:
                checksumBuildRequirements += [output]
            
            ninjaFileSyntax.build(
                outputs=f"{output}.elf",
                rule="elf",
                inputs=split_config.SPLIT_LINKER,
                variables={
                    "undef_sym_path": split_config.SPLIT_UNDEF_SYM,
                    "undef_fun_path": split_config.SPLIT_UNDEF_FUN,
                },
                implicit=elfBuildRequirements
            )
            ninjaFileSyntax.build(
                outputs=output,
                rule="objcopy",
                inputs=f"{output}.elf",
                implicit=f"{output}.elf"
            )
            
            if game_version_idx == 0:
                if split_config.SPLIT_BASENAME == "1ST/BODYPROG.BIN" or split_config.SPLIT_BASENAME == "VIN/STREAM.BIN":
                    ninjaFileSyntax.build(
                        outputs=f"{output}.fix",
                        rule="postbuild",
                        inputs=output,
                        implicit=output
                    )
            
                    
    
    if objdiff_mode:
        pos = re.search("\|", objdiffFileRule).start() + 1
        dumbVar = ""
        for item in objdiffConfigRequirements:
            dumbVar += " " + str(item)
        tempVar = objdiffFileRule[:pos] + f"{dumbVar}" + objdiffFileRule[pos:]
        objdiffFile.write(tempVar)
    
    
    if skip_checksum != True and objdiff_mode != True:
        if sys.platform == "linux" or sys.platform == "linux2":
            checksumTarget = f"{CONFIG_DIR}/{GAMEVERSIONS[game_version_idx].GAME_SETUP_INFO.GAME_VERSION_DIR}/checksum.sha"
        elif sys.platform == "win32":
            checksumTarget = f"{CONFIG_DIR}/{GAMEVERSIONS[game_version_idx].GAME_SETUP_INFO.GAME_VERSION_DIR}"
        
        ninjaFileSyntax.build(
            outputs=f"{BUILD_DIR}/out/checksum.ok",
            rule="sha256sum",
            inputs=checksumTarget,
            implicit=checksumBuildRequirements
        )

def clean_working_files(clean_build_files: bool, clean_target_files: bool):
    shutil.rmtree(BUILD_DIR, ignore_errors=True)
    shutil.rmtree(PERMUTER_DIR, ignore_errors=True)
    if os.path.exists(".splache"):
        os.remove(".splache")

    if clean_build_files:
        if os.path.exists("build.ninja"):
            os.remove("build.ninja")
        if os.path.exists("matching.ninja"):
            os.remove("matching.ninja")
        if os.path.exists("objdiff.ninja"):
            os.remove("objdiff.ninja")
        if os.path.exists("rules.ninja"):
            os.remove("rules.ninja")
        if os.path.exists(".ninja_log"):
            os.remove(".ninja_log")
        shutil.rmtree(ASM_DIR, ignore_errors=True)
        shutil.rmtree(LINKER_DIR, ignore_errors=True)
        
    if clean_target_files:
        shutil.rmtree(EXPECTED_DIR, ignore_errors=True)

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
        action="store_true"
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
    yamlMaps              = []
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
        clean_working_files(False, False)
        return
    
    if args.iso_extract:
        extract_files(gameVersionOption)
        return
    
    
    if args.setup == None:
        yamlsPaths.extend(YAML_EXECUTABLE)
        yamlsPaths.extend(YAML_ENGINE)
        yamlsPaths.extend(YAML_SCREENS)
        yamlMaps.extend(YAML_MAPS_0)
        yamlMaps.extend(YAML_MAPS_1)
        yamlMaps.extend(YAML_MAPS_2)
        yamlMaps.extend(YAML_MAPS_3)
        yamlMaps.extend(YAML_MAPS_4)
        yamlMaps.extend(YAML_MAPS_5)
        yamlMaps.extend(YAML_MAPS_6)
        yamlMaps.extend(YAML_MAPS_7)
        if gameVersionOption == 1:
            yamlsPaths.extend(YAML_ITEMS)
            for yamlMap in yamlMaps:
                for x in range(1,4):
                    yamlsPaths.extend([f"{yamlMap[:-7]}{x}{yamlMap[-6:]}"])
        else:
            yamlsPaths.extend(yamlMaps)
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
            case "itm":
                if gameVersionOption == 1:
                    yamlsPaths.extend(YAML_ITEMS)
                else:
                    print("Overlays only available for the European release.")
                    sys.exit(1)
            case "map":
                yamlMaps.extend(YAML_MAPS_0)
                yamlMaps.extend(YAML_MAPS_1)
                yamlMaps.extend(YAML_MAPS_2)
                yamlMaps.extend(YAML_MAPS_3)
                yamlMaps.extend(YAML_MAPS_4)
                yamlMaps.extend(YAML_MAPS_5)
                yamlMaps.extend(YAML_MAPS_6)
                yamlMaps.extend(YAML_MAPS_7)
                if gameVersionOption == 1:
                    for yamlMap in yamlMaps:
                        for x in range(1,4):
                            yamlsPaths.extend([f"{yamlMap[:-7]}{x}{yamlMap[-6:]}"])
                else:
                    yamlsPaths.extend(yamlMaps)
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
                    print("Overlay(s) not found.")
                    sys.exit(1)
    
    if regenMode == False:
        clean_working_files(True, objdiffConfigOption)
    else:
        appendSplits = []
        for asm_path in yamlsPaths:
            shutil.rmtree(f"{BUILD_DIR}/src/{asm_path.split('.yaml')[0]}", ignore_errors=True)
            if os.path.exists(f"{ASM_DIR}/{asm_path.split('.yaml')[0]}") == False:
                appendSplits += [asm_path]
            else:
                shutil.rmtree(f"{ASM_DIR}/{asm_path.split('.yaml')[0]}", ignore_errors=True)
    
    for yaml in yamlsPaths:
        splat.util.symbols.spim_context = spimdisasm.common.Context()
        splat.util.symbols.reset_symbols()
        split.main([Path(f"{CONFIG_DIR}/{GAMEVERSIONS[gameVersionOption].GAME_SETUP_INFO.GAME_VERSION_DIR}/{yaml}")], modes="all", use_cache=False, verbose=False, disassemble_all=True, make_full_disasm_for_code=objdiffConfigOption)
        if regenMode == True and appendSplits != []:
            for splitToAppend in appendSplits:
                if yaml == splitToAppend:
                    splitsYamlInfo.append(YAML_INFO([split.linker_writer.entries], split.config['options']['basename'], split.config['options']['ld_script_path'], split.config['options']['undefined_funcs_auto_path'], split.config['options']['undefined_syms_auto_path']))
        elif regenMode == False:
            splitsYamlInfo.append(YAML_INFO([split.linker_writer.entries], split.config['options']['basename'], split.config['options']['ld_script_path'], split.config['options']['undefined_funcs_auto_path'], split.config['options']['undefined_syms_auto_path']))
    
    
    if regenMode == False:
        ninja_build(splitsYamlInfo, gameVersionOption, objdiffConfigOption, skipChecksumOption, nonMatchingOption)
    else:
        ninja_append(splitsYamlInfo, skipChecksumOption, nonMatchingOption, gameVersionOption, False)
        if os.path.exists("matching.ninja"):
            ninja_append(splitsYamlInfo, False, False, gameVersionOption, True)
    
    if objdiffConfigOption:
        subprocess.call([PYTHON, "-m", "ninja", "-f", "objdiff.ninja"])
        

if __name__ == "__main__":
    main()
