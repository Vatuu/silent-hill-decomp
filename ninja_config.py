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
IMAGE_DIR     = f"{ROM_DIR}/image"
OBJDIFF_DIR   = f"{TOOLS_DIR}/objdiff"
DUMPSXISO_DIR = f"{TOOLS_DIR}/psxiso/dumpsxiso{SYS_EXTENSION}"

# Flags (for programs)
DUMPSXISO_FLAGS = f"-x {ROM_DIR}/{GAMEVERSIONS.GAME_VERSION_DIR} -s {ROM_DIR}/{GAMEVERSIONS.GAME_VERSION_DIR}/layout.xml {IMAGE_DIR}/{GAMEVERSIONS.GAME_NAME}.bin"

# Compilation tools
if sys.platform == "linux" or sys.platform == "linux2":
    CROSS   = "mips-linux-gnu"
    AS      = f"{CROSS}-as"
    LD      = f"{CROSS}-ld"
    OBJCOPY = f"{CROSS}-objcopy"
    OBJDUMP = f"{CROSS}-objdump"
    CPP     = f"{CROSS}-cpp"
    CC      = f"{TOOLS_DIR}/gcc-2.8.1-psx/cc1"
    OBJDIFF = f"{OBJDIFF_DIR}/objdiff"
else:
    CROSS   = "tools/binutils-win"
    AS      = f"{CROSS}/as.exe"
    LD      = f"{CROSS}/ld.exe"
    OBJCOPY = f"{CROSS}/objcopy.exe"
    OBJDUMP = f"{CROSS}/objdump.exe"
    CPP     = f"{CROSS}/c++.exe"
    CC      = f"{TOOLS_DIR}/gcc-2.8.1-psx/cc1"
    OBJDIFF = f"{OBJDIFF_DIR}/objdiff.exe"

@dataclass
class SPLITINFO:
    SPLIT_ENTRIES: List[str]
    SPLIT_BASENAME: str
    SPLIT_LINKER: str
    SPLIT_UNDEF_FUN: str
    SPLIT_UNDEF_SYM: str

# Compilation flags
INCLUDE_FLAGS   = f"-Iinclude -I {BUILD_DIR} -Iinclude/psyq"
OPT_FLAGS       = "-O2"
ENDIAN          = "-EL"
DL_EXE_FLAGS    = "-G8"
DL_OVL_FLAGS    = "-G0"
DEFINE_FLAGS    = "-D_LANGUAGE_C -DUSE_INCLUDE_ASM"


YAML_FILES = [
    "main.yaml",
    "bodyprog.yaml",
    "screens/b_konami.yaml",
    "screens/stream.yaml",
    "screens/options.yaml",
    "screens/credits.yaml",
    "screens/saveload.yaml",
    "maps/map0_s00.yaml",
    "maps/map0_s01.yaml",
    #"maps/map0_s02.yaml", # Bugged
    "maps/map1_s00.yaml",
    "maps/map1_s01.yaml",
    "maps/map1_s02.yaml",
    "maps/map1_s03.yaml",
    "maps/map1_s04.yaml",
    "maps/map1_s05.yaml",
    "maps/map1_s06.yaml",
    "maps/map2_s00.yaml",
    "maps/map2_s01.yaml",
    "maps/map2_s02.yaml",
    "maps/map2_s03.yaml",
    "maps/map2_s04.yaml",
    "maps/map3_s00.yaml",
    "maps/map3_s01.yaml",
    "maps/map3_s02.yaml",
    "maps/map3_s03.yaml",
    "maps/map3_s04.yaml",
    "maps/map3_s05.yaml",
    "maps/map3_s06.yaml",
    "maps/map4_s00.yaml",
    "maps/map4_s01.yaml",
    "maps/map4_s02.yaml",
    "maps/map4_s03.yaml",
    "maps/map4_s04.yaml",
    "maps/map4_s05.yaml",
    "maps/map4_s06.yaml",
    "maps/map5_s00.yaml",
    "maps/map5_s01.yaml",
    "maps/map5_s02.yaml",
    "maps/map5_s03.yaml",
    "maps/map6_s00.yaml",
    "maps/map6_s01.yaml",
    "maps/map6_s02.yaml",
    "maps/map6_s03.yaml",
    "maps/map6_s04.yaml",
    "maps/map6_s05.yaml",
    "maps/map7_s00.yaml",
    "maps/map7_s01.yaml",
    "maps/map7_s02.yaml",
    "maps/map7_s03.yaml"
]


#def setup_ninja(linker_entries: List[LinkerEntry]):
def setup_ninja(split_entries):
    built_objects: Set[Path] = set()

    def build(
        object_paths: Union[Path, List[Path]],
        src_paths: List[Path],
        task: str,
        ovl_map_flag: str = ""
        ):
        """
        Helper function to build objects.
        """

        # Convert object_paths to list if it is not already
        if not isinstance(object_paths, list):
            object_paths = [object_paths]

        # Convert paths to strings
        if task == "cc_ovl" or task == "cc":
            object_strs = [re.sub(".o$", ".s", str(obj)) for obj in object_paths]
            input_tar   = [re.sub(".c.o$", ".sjis.i", str(obj)) for obj in object_paths]
            implicit1   = [re.sub(".c.o$", ".sjis.i", str(obj)) for obj in object_paths]
        elif task == "iconv":
            object_strs = [re.sub(".c.o$", ".sjis.i", str(obj)) for obj in object_paths]
            input_tar   = [re.sub(".c.o$", ".i", str(obj)) for obj in object_paths]
            implicit1   = [re.sub(".c.o$", ".i", str(obj)) for obj in object_paths]
        elif task == "cpp":
            object_strs = [re.sub(".c.o$", ".i", str(obj)) for obj in object_paths]
            input_tar   = [str(s) for s in src_paths]
            implicit1   = ''
        elif task == "objdump":
            object_strs = [re.sub(".o$", ".dump.s", str(obj)) for obj in object_paths]
            input_tar   = [str(obj) for obj in object_paths]
            implicit1   = [str(obj) for obj in object_paths]
        elif task == "maspsx":
            object_strs = [str(obj) for obj in object_paths]
            input_tar   = [re.sub(".o$", ".s", str(obj)) for obj in object_paths]
            implicit1   = [re.sub(".o$", ".s", str(obj)) for obj in object_paths]
        else:
            object_strs = [str(obj) for obj in object_paths]
            input_tar   = [str(s) for s in src_paths]
            implicit1   = ''
        
        

        # Add object paths to built_objects
        for object_path in object_paths:
            if object_path.suffix == ".o" or object_path.suffix == ".i":
                built_objects.add(object_path)
            if implicit1 != "" and task != "maspsx":
                ninja.build(
                    outputs=object_strs,
                    rule=task,
                    inputs=input_tar,
                    implicit=implicit1
                )
            elif task == "cpp":
                ninja.build(
                    outputs=object_strs,
                    rule=task,
                    inputs=input_tar,
                    variables={
                        "OVL_FLAGS": ovl_map_flag
                    }
                )
            elif task == "maspsx":
                ninja.build(
                    outputs=object_strs,
                    rule=task,
                    inputs=input_tar,
                    variables={
                        "MAPSXFLAG": ovl_map_flag
                    }
                )
            else:
                ninja.build(
                    outputs=object_strs,
                    rule=task,
                    inputs=input_tar
                )

    ninja = ninja_syntax.Writer(open(str("build.ninja"), "w", encoding="utf-8"), width=9999)
    
    ninja.rule(
        "as",
        description="as $in",
        command=f"{AS} {ENDIAN} {INCLUDE_FLAGS} {OPT_FLAGS} {DL_OVL_FLAGS} -march=r3000 -mtune=r3000 -no-pad-sections -o $out $in",
    )

    ninja.rule(
        "cc",
        description="cc $in",
        command=f"{CC} {OPT_FLAGS} {DL_EXE_FLAGS} -mips1 -mcpu=3000 -w -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -mgas -fgnu-linker -quiet -o $out $in",
    )
    ninja.rule(
        "cc_ovl",
        description="cc $in",
        command=f"{CC} {OPT_FLAGS} {DL_OVL_FLAGS} -mips1 -mcpu=3000 -w -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -mgas -fgnu-linker -quiet -o $out $in",
    )
    
    ninja.rule(
        "cpp",
        description="cpp $in",
        command=f"{CPP} -P -MMD -MP -MT $out -MF $out.d {INCLUDE_FLAGS} {DEFINE_FLAGS} -P -MMD -MP -undef -Wall -lang-c -nostdinc $OVL_FLAGS -o $out $in",
    )

    ninja.rule(
        "iconv",
        description="iconv $in",
        command=f"iconv -f UTF-8 -t SHIFT-JIS $in -o $out",
    )

    ninja.rule(
        "objdump",
        description="objdump $in",
        command=f"{OBJDUMP} --disassemble-all --reloc --disassemble-zeroes -Mreg-names=32 $in > $out",
    )

    ninja.rule(
        "maspsx",
        description="maspsx $in",
        command=f"python3 tools/maspsx/maspsx.py --aspsx-version=2.77 --run-assembler $MAPSXFLAG -EL -Iinclude -I build -Iinclude/psyq -O2 -G0 -march=r3000 -mtune=r3000 -no-pad-sections -o $out $in",
    )
    
    ninja.rule(
        "ld",
        description="link $out",
        command=f"{LD} {ENDIAN} {OPT_FLAGS} -nostdlib --no-check-sections -r -b binary -o $out $in",
    )
    
    ninja.rule(
        "elf",
        description="elf $out.elf",
        command=f"{LD} {ENDIAN} {OPT_FLAGS} -nostdlib --no-check-sections -Map $out.map -T $in -T $undef_sym_path -T $undef_fun_path -T {CONFIG_DIR}/USA/lib_externs.ld -o $out",
    )
    
    ninja.rule(
        "objcopy",
        description="objcopy $out",
        command=f"{OBJCOPY} -O binary $in $out",
    )
    ninja.rule(
        "sha256sum",
        description="checksum",
        command=f"sha256sum --ignore-missing --check $in",
    )
    ninja.rule(
        "postbuild",
        description="postbuild script",
        command=f"tools/postbuild.sh $in",
    )
    
    mapId = ""
    implicits = []
    outbuilds = []
    
    # Build all the objects
    for split_config in split_entries:
        if split_config.SPLIT_BASENAME == "STREAM.BIN":
            os.system(f"tools/prebuild.sh screens/stream")
        elif split_config.SPLIT_BASENAME == "main":
            os.system(f"tools/prebuild.sh main")
        elif split_config.SPLIT_BASENAME == "BODYPROG.BIN":
            os.system(f"tools/prebuild.sh bodyprog")
        
        for split_entry in split_config.SPLIT_ENTRIES:
            for entry in split_entry:
                seg = entry.segment
                
                if entry.object_path is None:
                    continue
                
                if seg.type[0] == ".":
                    continue
                
                if isinstance(seg, splat.segtypes.common.asm.CommonSegAsm) or isinstance(seg, splat.segtypes.common.data.CommonSegData):
                    build(entry.object_path, entry.src_paths, "as")
                elif isinstance(seg, splat.segtypes.common.c.CommonSegC):
                    if re.search("^src/maps.*", str(entry.src_paths[0])):
                        mapId = re.search("map\d_s\d\d", str(entry.src_paths[0]))[0]
                        build(entry.object_path, entry.src_paths, "cpp", f"-D{mapId}".upper())
                    else:
                        build(entry.object_path, entry.src_paths, "cpp")
                    
                    build(entry.object_path, "", "iconv")
                        
                    if re.search("^src/main.*", str(entry.src_paths[0])):
                        build(entry.object_path, "", "cc")
                    else:
                        build(entry.object_path, "", "cc_ovl")
                    
                    if re.search("smf_io", str(entry.src_paths[0])) or re.search("smf_mid", str(entry.src_paths[0])):
                        build(entry.object_path, "", "maspsx", "--expand-div")
                    else:
                        build(entry.object_path, "", "maspsx")
                    
                    build(entry.object_path, "", "objdump")
                    
                elif isinstance(seg, splat.segtypes.common.databin.CommonSegDatabin) or seg.type == "header":
                    build(entry.object_path, entry.src_paths, "as")
                elif isinstance(seg, splat.segtypes.common.rodatabin.CommonSegRodatabin):
                    build(entry.object_path, entry.src_paths, "as")
                elif isinstance(seg, splat.segtypes.common.textbin.CommonSegTextbin):
                    build(entry.object_path, entry.src_paths, "as")
                elif isinstance(seg, splat.segtypes.common.bin.CommonSegBin):
                    build(entry.object_path, entry.src_paths, "ld")
                elif isinstance(seg, splat.segtypes.common.lib.CommonSegLib):
                    """Did you know that Silent Hill: Homecoming was meant to
                    have a seccion where Alex would have to go through a forest
                    and there he would have founded a hunter that would have
                    tried to kill him, but due lack of direction the whole
                    section was scrap and the hunter model was repurpose for
                    Travis Grady"""
                else:
                    print(f"ERROR: Unsupported build segment type {seg.type}")
                    sys.exit(1)
                
                if isinstance(seg, splat.segtypes.common.lib.CommonSegLib) != True:
                    implicits += [str(s) for s in [entry.object_path]]
        
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
            implicit=implicits
        )
        ninja.build(
            outputs=output,
            rule="objcopy",
            inputs=f"{output}.elf",
            implicit=f"{output}.elf"
        )
        implicits=[]
        
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
        
        outbuilds += [str(s) for s in [output]]
    
    for s in range(len(outbuilds)):
        if outbuilds[s] == "build/out/VIN/STREAM.BIN" or outbuilds[s] == "build/out/1ST/BODYPROG.BIN":
            outbuilds[s] = f"{outbuilds[s]}.fix"
    
    ninja.build(
        "build/out/checksum.ok",
        "sha256sum",
        "configs/USA/checksum.sha",
        implicit=outbuilds
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
    
    os.system(f"{DUMPSXISO_DIR} {DUMPSXISO_FLAGS}")
    subprocess.call(["python3", f"{TOOLS_DIR}/silentassets/extract.py",
    "-exe", f"{target_rom}/{GAMEVERSIONS.GAME_FILE_EXE}",
    "-fs", f"{target_rom}/{GAMEVERSIONS.GAME_FILE_SILENT}",
    "-fh", f"{target_rom}/{GAMEVERSIONS.GAME_FILE_HILL}",
    target_assets])


def main():
    parser = argparse.ArgumentParser(description="Configure the project")
    parser.add_argument(
        "-c",
        "--clean",
        help="Clean build and permuter files",
        action="store_true",
    )
    parser.add_argument(
        "-iso_e",
        "--iso_extract",
        help="Extract game files",
        action="store_true",
    )
    parser.add_argument(
        "-set",
        "--setup",
        choices=["extract", "insert"],
        help="Setup individual overlays or the executable only"
    )
    args = parser.parse_args()

    clean_test         = (args.clean) or False
    extract_files_test = (args.iso_extract) or False
    SPLITS_INFO        = []
    
    if clean_test:
        print("Cleaning compilation files")
        clean_files(False)
        return
    
    if extract_files_test:
        extract_files()
        return
    
    if args.setup == None:
        clean_files(True)
        for YAML_FILE in YAML_FILES:
            splat.util.symbols.spim_context = spimdisasm.common.Context()
            splat.util.symbols.reset_symbols()
            split.main([Path(f"{CONFIG_DIR}/USA/{YAML_FILE}")], modes="all", use_cache=False, verbose=False, disassemble_all=True, make_full_disasm_for_code=True)
            SPLITS_INFO += [SPLITINFO([split.linker_writer.entries], split.config['options']['basename'], split.config['options']['ld_script_path'], split.config['options']['undefined_funcs_auto_path'], split.config['options']['undefined_syms_auto_path'])]
        
        setup_ninja([SPLITS_INFO][0])

if __name__ == "__main__":
    main()
