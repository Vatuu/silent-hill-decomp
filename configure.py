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

# Compilation flags
INCLUDE_FLAGS   = f"-Iinclude -I {BUILD_DIR} -Iinclude/psyq"
OPT_FLAGS       = "-O2"
ENDIAN          = "-EL"
DL_EXE_FLAGS    = "-G8"
DL_OVL_FLAGS    = "-G0"
DEFINE_FLAGS    = "-D_LANGUAGE_C -DUSE_INCLUDE_ASM"


YAML_FILES = [
    #"main.yaml",
    #"bodyprog.yaml",
    #"screens/b_konami.yaml",
    #"screens/stream.yaml",
    "screens/options.yaml",
    #"screens/credits.yaml",
    #"screens/saveload.yaml",
    #"maps/map0_s00.yaml",
]


def setup_ninja(linker_entries: List[LinkerEntry]):
    built_objects: Set[Path] = set()

    def build(
        object_paths: Union[Path, List[Path]],
        src_paths: List[Path],
        task: str
        
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
        elif task == "iconv":
            object_strs = [re.sub(".c.o$", ".sjis.i", str(obj)) for obj in object_paths]
            input_tar   = [re.sub(".c.o$", ".i", str(obj)) for obj in object_paths]
        elif task == "cpp":
            object_strs = [re.sub(".c.o$", ".i", str(obj)) for obj in object_paths]
            input_tar   = [str(s) for s in src_paths]
        elif task == "objdump":
            object_strs = [re.sub(".o$", ".dump.s", str(obj)) for obj in object_paths]
            input_tar   = [str(obj) for obj in object_paths]
        elif task == "maspsx":
            object_strs = [str(obj) for obj in object_paths]
            input_tar   = [re.sub(".o$", ".s", str(obj)) for obj in object_paths]
        else:
            object_strs = [str(obj) for obj in object_paths]
            input_tar   = [str(s) for s in src_paths]
        
        

        # Add object paths to built_objects
        for object_path in object_paths:
            if object_path.suffix == ".o" or object_path.suffix == ".i":
                built_objects.add(object_path)
            ninja.build(
                outputs=object_strs,
                rule=task,
                inputs=input_tar
            )

    ninja = ninja_syntax.Writer(open(str("build.ninja"), "w", encoding="utf-8"), width=9999)
    
    ninja.rule(
        "as",
        description="as $in",
        command=f"{AS} {ENDIAN} {INCLUDE_FLAGS} {OPT_FLAGS} {DL_OVL_FLAGS} -march=r3000 -mtune=r3000 -no-pad-sections",
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
        command=f"python3 tools/maspsx/maspsx.py --aspsx-version=2.77 --run-assembler -EL -Iinclude -I build -Iinclude/psyq -O2 -G0 -march=r3000 -mtune=r3000 -no-pad-sections -o $out $in",
    )
    
    ninja.rule(
        "ld",
        description="link $out",
        command=f"{LD} {ENDIAN} {OPT_FLAGS} -nostdlib --no-check-sections -r -b binary -o $out $in",
    )
    ninja.rule(
        "xd",
        description="link $out",
        command=f"{LD} {ENDIAN} {OPT_FLAGS} -nostdlib --no-check-sections -Map build/out/USA/VIN/OPTION.BIN.map -T linkers/screens/options.ld -T linkers/screens/undefined_syms_auto.options.txt -T linkers/screens/undefined_funcs_auto.options.txt -o $out",
    )
    
    mapId = ""
    
    # Build all the objects
    for entryArray in linker_entries:
        for entry in entryArray:
            seg = entry.segment

            if entry.object_path is None:
                continue

            if seg.type[0] == ".":
                continue


            if isinstance(seg, splat.segtypes.common.asm.CommonSegAsm) or isinstance(seg, splat.segtypes.common.data.CommonSegData):
                build(entry.object_path, entry.src_paths, "as")
            elif isinstance(seg, splat.segtypes.common.c.CommonSegC):
                if re.search("^src/maps.*", str(entry.src_paths[0])) and mapId != re.search("map\d_s\d\d", str(entry.src_paths[0]))[0]:
                    mapId = re.search("map\d_s\d\d", str(entry.src_paths[0]))[0]
                    ninja.variable(
                        "OVL_FLAGS",
                        f"-D{mapId}"
                    )
                
                build(entry.object_path, entry.src_paths, "cpp")
                build(entry.object_path, "", "iconv")
                    
                if re.search("^src/main.*", str(entry.src_paths[0])):
                    build(entry.object_path, "", "cc")
                else:
                    build(entry.object_path, "", "cc_ovl")
                
                build(entry.object_path, "", "maspsx")
                build(entry.object_path, "", "objdump")
                
            elif isinstance(seg, splat.segtypes.common.databin.CommonSegDatabin):
                build(entry.object_path, entry.src_paths, "as")
            elif isinstance(seg, splat.segtypes.common.rodatabin.CommonSegRodatabin):
                build(entry.object_path, entry.src_paths, "as")
            elif isinstance(seg, splat.segtypes.common.textbin.CommonSegTextbin):
                build(entry.object_path, entry.src_paths, "as")
            elif isinstance(seg, splat.segtypes.common.bin.CommonSegBin):
                build(entry.object_path, entry.src_paths, "ld")
            else:
                print(f"ERROR: Unsupported build segment type {seg.type}")
                sys.exit(1)
        
        ninja.build(
            PRE_ELF_PATH,
            "ld",
            LD_PATH,
            implicit=[str(obj) for obj in built_objects],
            variables={"mapfile": MAP_PATH},
        )

    #ninja.build(
    #    PRE_ELF_PATH,
    #    "ld",
    #    LD_PATH,
    #    implicit=[str(obj) for obj in built_objects],
    #    variables={"mapfile": MAP_PATH},
    #)
    #
    #ninja.build(
    #    ELF_PATH,
    #    "elf",
    #    PRE_ELF_PATH,
    #)


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
    linker_entries     = []
    
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
            #TODO MULT-VER-SUPPORT: Replace config dir to use multi-version support
            split.main([Path(f"{CONFIG_DIR}/{YAML_FILE}")], modes="all", verbose=False)
            linker_entries += [split.linker_writer.entries]
        
        setup_ninja(linker_entries)

if __name__ == "__main__":
    main()
