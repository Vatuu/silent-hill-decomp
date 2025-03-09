from dataclasses import dataclass
from itertools import chain
import logging
from pathlib import Path
from argparse import ArgumentParser, FileType
from struct import Struct
from typing import BinaryIO, Iterable
from zlib import crc32
import os

@dataclass
class Region:
    id: str
    name: str
    checksum: int
    tocOffset: int
    fileCount: int

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


FILE_TYPES = [
    EntryType("Texture Image", "TIM"), EntryType("Sound Bank", "VAB"), EntryType("Overlay Data", "BIN"), EntryType("DMS?", "DMS"), EntryType("Animation Data", "ANM"), EntryType("Map Geometry Data", "PLM"), EntryType("Map Data", "IPD"), EntryType("Character Data", "ILM"), EntryType("Mesh Data", "TMD"), EntryType("Demo Data", "DAT"), EntryType("Audio Metadata", "KDT"), EntryType("Compressed Data?", "CMP"), EntryType("Plaintext?", "TXT"), EntryType("Unused 1", "UU1"), EntryType("Unused 2", "UU2"), EntryType("XA Track Data", "")
]

DIRS = [ "1ST", "ANIM", "BG", "CHARA", "ITEM", "MISC", "SND", "TEST", "TIM", "VIN", "XA"]
DIRS_PAL = [ "1ST", "ANIM", "BG", "CHARA", "ITEM", "MISC", "SND", "TEST", "TIM", "VIN", "VIN2", "VIN3", "VIN4", "VIN5", "XA"]

REGIONS = (
    Region("NTSC 1.1", "SLUS-00707", 0xDA0BFDF1, 0xB91C, 2074),
    Region("PAL", "SLES-01514", 0xCBFD1A13, 0xB8FC, 2310),
    Region("NTSC-J Rev 2", "SLPM-86192", 0x7E03604D, 0xB91C, 2074),
    Region("NTSC Nov 24, 1998", "SLUS-45678", 0xEAEB4DF8, 0xB71C, 1926)
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
    return crc32(exe.read(128))

def _detectRegion(checksum: int, name: str) -> Region:
    if(checksum == REGIONS[0].checksum):
        region = REGIONS[0]
    elif(checksum == REGIONS[1].checksum):
        region = REGIONS[1]
    elif(checksum == REGIONS[2].checksum):
        region = REGIONS[2]
    elif(checksum == REGIONS[3].checksum):
        region = REGIONS[3]
    else:
        logging.error(f"Executable {name} returned a unrecognized checksum! [{checksum:08X}]")
        logging.error("\tIt is not a valid Silent Hill executable.")
        return None
    logging.info(f"Determined the region as {region.id} ({region.name})")
    return region

def _parseEntry(entry, isPal):
    meta, file1, file2 = ENTRY_STRUCT.unpack(entry)
    
    name = "".join(chain(
        ( chr(32 + ((file1 >> shift) & 63)) for shift in range(4, 28, 6) ),
        ( chr(32 + ((file2 >> shift) & 63)) for shift in range(0, 24, 6) )
    )).strip()

    if isPal == False:
        return meta >> 19, meta & 0x7FFFF, name, DIRS[file1 & 15], FILE_TYPES[(file2 >> 24) & 15]
    else:
        return meta >> 19, meta & 0x7FFFF, name, DIRS_PAL[file1 & 15], FILE_TYPES[(file2 >> 24) & 15]
    # size, lba, name, path, type

def _formatEntry(size, lba, name, path, type, isPal):
    name = name.ljust(8)
    namesep = ','.join(f"'{name[i]}'" for i in range(0, len(name)))
    if isPal == False:
        return f'{{ {lba:#07x}, {size:4d}, {DIRS.index(path):2d}, FN({namesep}), {FILE_TYPES.index(type):2d} }}'
    else:
        return f'{{ {lba:#07x}, {size:4d}, {DIRS_PAL.index(path):2d}, FN({namesep}), {FILE_TYPES.index(type):2d} }}'
        

def _decryptOverlay(data: bytes):
    output   = bytearray(data)
    outArray = memoryview(output).cast("I") # uint32_t
    seed = 0

    for i, value in enumerate(outArray):
        seed = (seed + 0x01309125) & 0xffffffff
        seed = (seed * 0x03a452f7) & 0xffffffff
        outArray[i] ^= seed

    return output

def _extract(entries:Iterable[TableEntry], output: Path, file: BinaryIO, sectorSize: int, regionID):
    index = 0
    for i in entries:
        outputPath = (output / i.path).absolute()
        if(not outputPath.parent.exists()):
            outputPath.parent.mkdir(parents = True)

        ext = "XA" if i.type == FILE_TYPES[15] else i.type.extension
        logging.info(f"{index} Extracting {i.type.name}(.{ext}) to {outputPath}...")
        
        file.seek((i.offset - entries[0].offset) * sectorSize)
        size = 0
        if not i.size == 0:
            size = i.size
        elif index+1 < len(entries):
            size = entries[index + 1].offset - i.offset
        data = file.read(size * FILESIZE_STEP)
        if(i.type == FILE_TYPES[2] and regionID != "NTSC Nov 24, 1998"):
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
    
    if(args.exeChecksum):
        logging.info(f"Checksum of {executable.name}: {checksum:08X}")
        return
    else:
        region = _detectRegion(checksum, executable.name)
        if(region == None):
            return


    isPal = False
    if region == REGIONS[1]:
        isPal = True
    originText = f"// Generated from {region.name} ({region.id})\n"
    headerText = originText
    enumText = f"    {originText}"
    entriesSilent = []
    entriesHill = []
    executable.seek(region.tocOffset)
    for i in range(region.fileCount):
        rawEntry = executable.read(ENTRY_STRUCT.size)
        size, lba, name, directory, type = _parseEntry(rawEntry, isPal)
        fullpath = os.path.join(directory, f"{name}.{type.extension}" if not type == FILE_TYPES[15] else f"{name}")
        headerText += f"/* {i:4d} */ {_formatEntry(size, lba, name, directory, type, isPal)}, // {fullpath}\n"
        enumText += f"    FILE_{fullpath.replace("/", "_").replace(".", "_")} = {i}, // {fullpath}\n"
        entry = TableEntry(fullpath, type, size, lba)
        
        match directory:
            case "XA":
                entriesHill.append(entry)
            case _:
                entriesSilent.append(entry)
    executable.close
    
    with open(os.path.join(args.outputFolder, "filetable.c.inc"), "w") as f:
        f.write(headerText)
    with open(os.path.join(args.outputFolder, "fileenum.h.inc"), "w") as f:
        f.write(enumText)
    
    _extract(entriesSilent, args.outputFolder, args.silentFile, 2048, region.id)
    
    if region.id != "NTSC Nov 24, 1998":
        _extract(entriesHill, args.outputFolder, args.hillFile, 2352, region.id)
    
    logging.info("All done!")


if __name__ == "__main__":
    main()