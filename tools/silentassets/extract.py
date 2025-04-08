from dataclasses import dataclass
from itertools import chain
import logging
from pathlib import Path
from argparse import ArgumentParser, FileType
from struct import Struct
from typing import BinaryIO, Iterable
from zlib import crc32
import os
from enum import IntFlag

class Flags(IntFlag):
    NONE = 0
    ENCRYPTED_1ST_FOLDER = 1
    NO_XA_CONTAINER = 2
    ALT_FILE_STRUCT = 4

@dataclass
class Region:
    id: str
    name: str
    checksum: int
    tocOffset: int
    fileCount: int
    dirs: list[str]
    filetypes: list[str]
    flags: Flags

@dataclass
class EntryType:
    name: str 
    extension: str

@dataclass
class TableEntry:
    path: Path
    type: EntryType
    size: int
    offset: int

# Description of each file type extension
FILE_TYPE_NAMES = {
    "TIM": "Texture Image",
    "VAB": "Sound Bank",
    "BIN": "Overlay Data",
    "DMS": "Cutscene Data",
    "ANM": "Animation Data",
    "PLM": "Map Geometry Data",
    "IPD": "Map Data",
    "ILM": "Character Data",
    "TMD": "Mesh Data",
    "DAT": "Demo Data",
    "KDT": "Audio Metadata",
    "CMP": "Compressed Data",
    "TXT": "Dummy Plaintext",
    "UU1": "Unused 1",
    "UU2": "Unused 2",
    "UU3": "Unused 3",
    "UU4": "Unused 4",
    "": "XA Track Data"
}

# Mapping of type index -> type string, mappings change in certain releases
FILE_TYPES = [
    "TIM", "VAB", "BIN", "DMS", "ANM", "PLM", "IPD", "ILM", 
    "TMD", "DAT", "KDT", "CMP", "TXT", "UU1", "UU2", ""
]

FILE_TYPES_DEMO = [
    "TIM", "VAB", "BIN", "ANM", "DMS", "PLM", "IPD", "ILM", 
    "TMD", "DAT", "KDT", "CMP", "TXT", "UU1", "UU2", ""
]

FILE_TYPES_OPM16 = [
    "TIM", "VAB", "BIN", "ANM", "DMS", "PLM", "IPD", "ILM", 
    "TMD", "KDT", "CMP", "UU1", "UU2", "UU3", "UU4", ""
]

# Mapping of directory index -> dir string, mappings change in certain releases
DIRS_NTSC = [
    "1ST", "ANIM", "BG", "CHARA", "ITEM", "MISC", "SND", "TEST", 
    "TIM", "VIN", "XA"
]

DIRS_PAL = [
    "1ST", "ANIM", "BG", "CHARA", "ITEM", "MISC", "SND", "TEST", 
    "TIM", "VIN", "VIN2", "VIN3", "VIN4", "VIN5", "XA"
]

DIRS_DEMO = [
    "1ST", "ANIM", "BG", "CHARA", "ITEM", "MISC", "SND", "TIM",
    "VIN", "XA"
]

DIRS_OPM16 = [
    "1ST", "ANIM", "BG", "CHARA", "ITEM", "SND", "TEST", "TIM", 
    "VIN", "XA"
]

REGIONS = (
# Partial demo releases
    Region("NTSC OPM16 Demo 98-10-19", "SCUS-94278", 0x2534D4BE, 0xAA90, 886, DIRS_OPM16, FILE_TYPES_OPM16, Flags.ALT_FILE_STRUCT),
    Region("NTSC-J Trial Version 98-11-06", "SLPM-80363", 0xBE8E95CF, 0xB780, 849, DIRS_DEMO, FILE_TYPES_DEMO, Flags.ALT_FILE_STRUCT),
    Region("PAL Demo 98-12-16", "SLED-01735", 0x9AE067D4, 0xB648, 850, DIRS_DEMO, FILE_TYPES_DEMO, 0),
    Region("NTSC Demo 99-01-16", "SLUS-90050", 0x55E85F78, 0xB648, 849, DIRS_DEMO, FILE_TYPES_DEMO, 0),
    Region("PAL Demo 99-06-08", "SLED-02190", 0x08E0B752, 0xC8FC, 1015, DIRS_PAL, FILE_TYPES, Flags.ENCRYPTED_1ST_FOLDER),
    Region("PAL Demo 99-06-16", "SLED-02186", 0x1782AA0A, 0xB8FC, 1015, DIRS_PAL, FILE_TYPES, Flags.ENCRYPTED_1ST_FOLDER),
# Prototypes
    Region("NTSC Preview 98-11-24", "SLUS-45678", 0x8B88326C, 0xB71C, 1926, DIRS_NTSC, FILE_TYPES, Flags.NO_XA_CONTAINER),
    Region("NTSC Review 99-01-07", "SLUS-00707", 0xCC454534, 0xB7B8, 2076, DIRS_NTSC, FILE_TYPES, Flags.NO_XA_CONTAINER),
    Region("NTSC Trade Demo 99-01-17", "SLUS-80707", 0xC9FFEF2A, 0xB850, 2040, DIRS_NTSC, FILE_TYPES, 0),
    Region("NTSC Beta 99-01-22", "SLUS-00707", 0x84AB9750, 0xB850, 2072, DIRS_NTSC, FILE_TYPES, 0),
# Final releases
    Region("NTSC-J Rev 0 99-01-26", "SLPM-86192", 0x1532C55C, 0xB91C, 2074, DIRS_NTSC, FILE_TYPES, Flags.ENCRYPTED_1ST_FOLDER),
    Region("NTSC 1.1 99-02-10", "SLUS-00707", 0xCF9CD8E5, 0xB91C, 2074, DIRS_NTSC, FILE_TYPES, Flags.ENCRYPTED_1ST_FOLDER),
    Region("NTSC-J Rev 1/Rev 2 99-06-02", "SLPM-86192", 0xEB733CAA, 0xB91C, 2074, DIRS_NTSC, FILE_TYPES, Flags.ENCRYPTED_1ST_FOLDER),
    Region("PAL 99-06-07", "SLES-01514", 0x337E4A60, 0xB8FC, 2310, DIRS_PAL, FILE_TYPES, Flags.ENCRYPTED_1ST_FOLDER),
)

FILESIZE_STEP = 256

ENTRY_STRUCT = Struct("<3I")

def _createParser():
    parser = ArgumentParser()
    parser.add_argument("--executable", "-exe", type = FileType("rb"))
    parser.add_argument("--silentFile", "-fs", type = FileType("rb"))
    parser.add_argument("--hillFile", "-fh", type = FileType("rb"))
    parser.add_argument("outputFolder", type = Path, default = ".")
    parser.add_argument("--exeChecksum", "-c", action = "store_true")
    return parser

def _getChecksum(exe: BinaryIO):
    exe.seek(0)
    return crc32(exe.read(4096))

def _detectRegion(checksum: int, name: str) -> Region:
    for region in REGIONS:
        if checksum == region.checksum:
            logging.info(f"Determined the region as {region.id} ({region.name})")
            return region
    logging.error(f"Executable {name} returned an unrecognized checksum! [{checksum:08X}]")
    logging.error("\tIt is not a valid Silent Hill executable.")
    return None

def _parseEntry(entry, region):
    meta, file1, file2 = ENTRY_STRUCT.unpack(entry)
    
    if not region.flags & Flags.ALT_FILE_STRUCT:
        name = "".join(chain(
            ( chr(32 + ((file1 >> shift) & 63)) for shift in range(4, 28, 6) ),
            ( chr(32 + ((file2 >> shift) & 63)) for shift in range(0, 24, 6) )
        )).strip()

        # size, lba, name, path, type
        return meta >> 19, meta & 0x7FFFF, name, region.dirs[file1 & 15], region.filetypes[(file2 >> 24) & 15]
    else:
        directoryIndex0 = (meta >> 31) & 0x1
        directoryIndex1 = file1 & 0x7

        name0 = (file1 >> 3) & 0x1FFFFFFF
        name1 = file2 & 0x7FFFF

        extensionIndex = (file2 >> 19) & 0xFF
        directoryIndex = (directoryIndex1 << 1) | directoryIndex0

        nameBits = (name1 << 29) | name0

        name = "".join(
            chr(32 + ((nameBits >> shift) & 0x3F))
            for shift in range(0, 48, 6)
        ).strip()

        # size, lba, name, path, type
        return (meta >> 19) & 0xFFF, meta & 0x7FFFF, name, region.dirs[directoryIndex], region.filetypes[extensionIndex]

def _formatEntry(size, lba, name, path, type, region):
    name = name.ljust(8)
    namesep = ','.join(f"'{name[i]}'" for i in range(0, len(name)))

    return f'{{ {lba:#07x}, {size:4d}, {region.dirs.index(path):2d}, FN({namesep}), {region.filetypes.index(type):2d} }}'
        

def _decryptOverlay(data: bytes):
    output   = bytearray(data)
    outArray = memoryview(output).cast("I") # uint32_t
    seed = 0

    for i, value in enumerate(outArray):
        seed = (seed + 0x01309125) & 0xffffffff
        seed = (seed * 0x03a452f7) & 0xffffffff
        outArray[i] ^= seed

    return output

def _extract(entries:Iterable[TableEntry], output: Path, file: BinaryIO, sectorSize: int, regionFlags: int):
    index = 0
    for i in entries:
        outputPath = (output / i.path).absolute()
        if not outputPath.parent.exists():
            outputPath.parent.mkdir(parents = True)

        ext = "XA" if i.type == "" else i.type
        logging.info(f"{index} Extracting {FILE_TYPE_NAMES[i.type]}(.{ext}) to {outputPath}...")
        
        file.seek((i.offset - entries[0].offset) * sectorSize)
        size = 0
        if not i.size == 0 and (i.type != ""):
            size = i.size * FILESIZE_STEP
        elif index+1 < len(entries):
            size = (entries[index + 1].offset - i.offset) * sectorSize
        else:
            size = -1 # read until end of file
        data = file.read(size)
        if i.type == "BIN" and (regionFlags & Flags.ENCRYPTED_1ST_FOLDER):
            if i.path.startswith("1ST"):
                logging.info("\tDecrypting Overlay...")
                data = _decryptOverlay(data)
        with outputPath.open("wb") as _file:
            _file.write(data)
        index = index + 1

def main():
    logging.basicConfig(level = logging.INFO)
    args = _createParser().parse_args()
    executable: BinaryIO = args.executable
    checksum = _getChecksum(executable)
    
    if args.exeChecksum:
        logging.info(f"Checksum of {executable.name}: {checksum:08X}")
        return
    else:
        region = _detectRegion(checksum, executable.name)
        if region == None:
            return

    originText = f"// Generated from {region.name} ({region.id})\n"
    headerText = originText
    enumText = f"    {originText}"
    entriesSilent = []
    entriesHill = []
    executable.seek(region.tocOffset)
    for i in range(region.fileCount):
        rawEntry = executable.read(ENTRY_STRUCT.size)
        size, lba, name, directory, type = _parseEntry(rawEntry, region)
        fullpath = os.path.join(directory, f"{name}.{type}" if not type == "" else f"{name}").replace("\\", "/")
        headerText += f"/* {i:4d} */ {_formatEntry(size, lba, name, directory, type, region)}, // {fullpath}\n"
        enumName = fullpath.replace("/", "_").replace("\\", "_").replace(".", "_")
        enumText += f"    FILE_{enumName} = {i}, // {fullpath}\n"
        entry = TableEntry(fullpath, type, size, lba)
        
        match directory:
            case "XA":
                entriesHill.append(entry)
            case _:
                entriesSilent.append(entry)
    executable.close
    
    _extract(entriesSilent, args.outputFolder, args.silentFile, 2048, region.flags)
    
    if not region.flags & Flags.NO_XA_CONTAINER and args.hillFile:
        _extract(entriesHill, args.outputFolder, args.hillFile, 2336, region.flags)

    with open(os.path.join(args.outputFolder, "filetable.c.inc"), "a+") as f:
        f.truncate(0)
        f.write(headerText)
    with open(os.path.join(args.outputFolder, "fileenum.h.inc"), "a+") as f:
        f.truncate(0)
        f.write(enumText)
    
    logging.info("All done!")


if __name__ == "__main__":
    main()
