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
    EntryType("Texture Image", "TIM"), EntryType("Sound Bank", "VAB"), EntryType("Overlay Data", "BIN"), EntryType("Animation Data?", "DMS"),
    EntryType("Animation Data", "ANM"), EntryType("PLM?", "PLM"), EntryType("Background Data?", "IPD"), EntryType("Character Data?", "ILM"),
    EntryType("Mesh Data", "TMD"), EntryType("Demo Data", "DAT"), EntryType("Audio Metadata?", "KDT"), EntryType("Compressed Data?", "CMP"),
    EntryType("Plaintext?", "TXT"), EntryType("Unused 1", "UU1"), EntryType("Unused 2", "UU2"), EntryType("XA Track Data", "")
]

DIRS = [ "1ST", "ANIM", "BG", "CHARA", "ITEM", "MISC", "SND", "TEST", "TIM", "VIN", "XA", "UNK11", "UNK12", "UNK13", "UNK14", "UNK15" ]

REGIONS = (
    Region("NTSC", "SLUS-00707", 0xDA0BFDF1, 0x8001b11c - 0x80010000 + 0x800, 2074),
    Region("PAL", "SLES-01514", 0xCBFD1A13, 0xB8FC, 0))

FILESIZE_STEP = 256

SILENT_LBA = 64
HILL_LBA = 39359

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
    else:
        logging.error(f"Executable {name} returned a unrecognized checksum! [{checksum:08X}]")
        logging.error("\tIt is not a valid Silent Hill executable.")
        return None
    logging.info(f"Determined the region as {region.id} ({region.name})")
    return region

def _parseEntry(entry):
    meta, file1, file2 = ENTRY_STRUCT.unpack(entry)
    
    name = "".join(chain(
        ( chr(32 + ((file1 >> shift) & 63)) for shift in range(4, 28, 6) ),
        ( chr(32 + ((file2 >> shift) & 63)) for shift in range(0, 24, 6) )
    )).strip()

    # size, lba, name, path, type
    return meta >> 19, meta & 0x7FFFF, name, DIRS[file1 & 15], FILE_TYPES[(file2 >> 24) & 15]

def _formatEntry(size, lba, name, path, type):
    name = name.ljust(8)
    namesep = ','.join(f"'{name[i]}'" for i in range(0, len(name)))
    return f'{{ {lba:#07x}, {size:4d}, {DIRS.index(path):2d}, FN({namesep}), {FILE_TYPES.index(type):2d} }}'

def _decryptOverlay(data: bytes):
    output   = bytearray(data)
    outArray = memoryview(output).cast("I") # uint32_t
    seed = 0

    for i, value in enumerate(outArray):
        seed = (seed + 0x01309125) & 0xffffffff
        seed = (seed * 0x03a452f7) & 0xffffffff
        outArray[i] ^= seed

    return output

def _extract(entries:Iterable[TableEntry], output: Path, file: BinaryIO, sectorSize: int, lbaOffset: int):
    index = 0
    for i in entries:
        outputPath = (output / i.path).absolute()
        if(not outputPath.parent.exists()):
            outputPath.parent.mkdir(parents = True)

        ext = "XA" if i.type == FILE_TYPES[15] else i.type.extension
        logging.info(f"{index} Extracting {i.type.name}(.{ext}) to {outputPath}...")

        file.seek((i.offset - lbaOffset) * sectorSize)
        data = file.read((i.size if not i.size == 0 else entries[index + 1].offset - i.offset) * FILESIZE_STEP)
        if(i.type == FILE_TYPES[2] and i.path.startswith("1ST")):
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

    headerText = ""
    entriesSilent = []
    entriesHill = []
    executable.seek(region.tocOffset)
    for i in range(region.fileCount):
        rawEntry = executable.read(ENTRY_STRUCT.size)
        size, lba, name, directory, type = _parseEntry(rawEntry)
        fullpath = os.path.join(directory, f"{name}.{type.extension}" if not type == FILE_TYPES[15] else f"{name}")
        headerText += f"/* {i:4d} */ {_formatEntry(size, lba, name, directory, type)}, // {fullpath}\n"
        entry = TableEntry(fullpath, type, size, lba)
        if(lba < HILL_LBA):
            entriesSilent.append(entry)
        else:
            entriesHill.append(entry)
    executable.close
    _extract(entriesSilent, args.outputFolder, args.silentFile, 2048, SILENT_LBA)
    _extract(entriesHill, args.outputFolder, args.hillFile, 2352, HILL_LBA)
    with open(os.path.join(args.outputFolder, "filetable.c.inc"), "w") as f:
        f.write(headerText)
    logging.info("All done!")


if __name__ == "__main__":
    main()