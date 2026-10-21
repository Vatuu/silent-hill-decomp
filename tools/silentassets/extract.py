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
class Release:
    id: str
    name: str
    checksum: int
    tocOffset: int
    fileCount: int
    dirs: list[str]
    filetypes: list[str]
    flags: Flags


@dataclass
class TableEntry:
    path: Path
    type: str
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

RELEASES = (
    # Partial demo releases
    Release("NTSC OPM16 Demo 98-10-19", "SCUS-94278", 0x2534D4BE, 0xAA90, 886, DIRS_OPM16, FILE_TYPES_OPM16,
            Flags.ALT_FILE_STRUCT),
    Release("NTSC-J Demo 98-11-06", "SLPM-80366", 0x1BCE20E4, 0xB9B0, 849, DIRS_DEMO, FILE_TYPES_DEMO,
            Flags.ALT_FILE_STRUCT),
    Release("NTSC-J Demo 98-11-06", "SLPM-80363", 0xBE8E95CF, 0xB780, 849, DIRS_DEMO, FILE_TYPES_DEMO,
            Flags.ALT_FILE_STRUCT),
    Release("PAL Demo 98-12-16", "SLED-01735", 0x9AE067D4, 0xB648, 850, DIRS_DEMO, FILE_TYPES_DEMO, Flags.NONE),
    Release("NTSC Demo 99-01-16", "SLUS-90050", 0x55E85F78, 0xB648, 849, DIRS_DEMO, FILE_TYPES_DEMO, Flags.NONE),
    Release("PAL Demo 99-06-08", "SLED-02190", 0x08E0B752, 0xC8FC, 1015, DIRS_PAL, FILE_TYPES,
            Flags.ENCRYPTED_1ST_FOLDER),
    Release("PAL Demo 99-06-16", "SLED-02186", 0x1782AA0A, 0xB8FC, 1015, DIRS_PAL, FILE_TYPES,
            Flags.ENCRYPTED_1ST_FOLDER),
    # Prototypes
    Release("NTSC Preview 98-11-24", "SLUS-45678", 0x8B88326C, 0xB71C, 1926, DIRS_NTSC, FILE_TYPES,
            Flags.NO_XA_CONTAINER),
    Release("NTSC Review 99-01-07", "SLUS-00707", 0xCC454534, 0xB7B8, 2076, DIRS_NTSC, FILE_TYPES,
            Flags.NO_XA_CONTAINER),
    Release("NTSC Trade Demo 99-01-17", "SLUS-80707", 0xC9FFEF2A, 0xB850, 2040, DIRS_NTSC, FILE_TYPES, Flags.NONE),
    Release("NTSC Beta 99-01-22", "SLUS-00707", 0x84AB9750, 0xB850, 2072, DIRS_NTSC, FILE_TYPES, Flags.NONE),
    # Final releases
    Release("NTSC-J Rev 0 99-01-26", "SLPM-86192", 0x1532C55C, 0xB91C, 2074, DIRS_NTSC, FILE_TYPES,
            Flags.ENCRYPTED_1ST_FOLDER),
    Release("NTSC 1.1 99-02-10", "SLUS-00707", 0xCF9CD8E5, 0xB91C, 2074, DIRS_NTSC, FILE_TYPES,
            Flags.ENCRYPTED_1ST_FOLDER),
    Release("NTSC-J Rev 1/Rev 2 99-06-02", "SLPM-86192", 0xEB733CAA, 0xB91C, 2074, DIRS_NTSC, FILE_TYPES,
            Flags.ENCRYPTED_1ST_FOLDER),
    Release("PAL 99-06-07", "SLES-01514", 0x337E4A60, 0xB8FC, 2310, DIRS_PAL, FILE_TYPES, Flags.ENCRYPTED_1ST_FOLDER),
)

# Files referenced by `g_AudioData` in BODYPROG.BIN, in table order, with each entry's `e_AudioType`.
# Used to regenerate `g_AudioData` table.
# `None` entries are empty rows in the table.
AUDIO_DATA_FILES = [
    ("1ST/BASE.VAB", "AudioType_BaseAudio"),
    ("1ST/COATION.VAB", "AudioType_Ambient"),
    ("SND/FIRST.VAB", "AudioType_Ambient"),
    ("SND/DRILL.VAB", "AudioType_Weapon"), ("SND/FUEL.VAB", "AudioType_Weapon"), ("SND/HYPER.VAB", "AudioType_Weapon"), ("SND/PISTOL.VAB", "AudioType_Weapon"), ("SND/RIFEL.VAB", "AudioType_Weapon"),
    ("SND/SHOTGUN.VAB", "AudioType_Weapon"), ("SND/SAW.VAB", "AudioType_Weapon"),
    ("SND/MAP000.VAB", "AudioType_Ambient"), ("SND/MAP001.VAB", "AudioType_Ambient"), ("SND/MAP100.VAB", "AudioType_Ambient"), ("SND/MAP101.VAB", "AudioType_Ambient"), ("SND/MAP102.VAB", "AudioType_Ambient"),
    ("SND/MAP103.VAB", "AudioType_Ambient"), ("SND/MAP105.VAB", "AudioType_Ambient"), ("SND/MAP106.VAB", "AudioType_Ambient"), ("SND/MAP200.VAB", "AudioType_Ambient"), ("SND/MAP201.VAB", "AudioType_Ambient"),
    ("SND/MAP300.VAB", "AudioType_Ambient"), ("SND/MAP301.VAB", "AudioType_Ambient"), ("SND/MAP302.VAB", "AudioType_Ambient"), ("SND/MAP303.VAB", "AudioType_Ambient"), ("SND/MAP304.VAB", "AudioType_Ambient"),
    ("SND/MAP305.VAB", "AudioType_Ambient"), ("SND/MAP306.VAB", "AudioType_Ambient"), ("SND/MAP401.VAB", "AudioType_Ambient"), ("SND/MAP402.VAB", "AudioType_Ambient"), ("SND/MAP403.VAB", "AudioType_Ambient"),
    ("SND/MAP405.VAB", "AudioType_Ambient"), ("SND/MAP500.VAB", "AudioType_Ambient"), ("SND/MAP501.VAB", "AudioType_Ambient"), ("SND/MAP502.VAB", "AudioType_Ambient"), ("SND/MAP503.VAB", "AudioType_Ambient"),
    ("SND/MAP600.VAB", "AudioType_Ambient"), ("SND/MAP601.VAB", "AudioType_Ambient"), ("SND/MAP602.VAB", "AudioType_Ambient"), ("SND/MAP603.VAB", "AudioType_Ambient"), ("SND/MAP604.VAB", "AudioType_Ambient"),
    ("SND/MAP700.VAB", "AudioType_Ambient"), ("SND/MAP701.VAB", "AudioType_Ambient"), ("SND/MAP702.VAB", "AudioType_Ambient"), ("SND/MAP703.VAB", "AudioType_Ambient"), ("SND/MAP001_2.VAB", "AudioType_Ambient"),
    ("SND/A2.VAB", "AudioType_MusicKeys"), ("SND/B.VAB", "AudioType_MusicKeys"), ("SND/B2.VAB", "AudioType_MusicKeys"), ("SND/C.VAB", "AudioType_MusicKeys"), ("SND/C2.VAB", "AudioType_MusicKeys"),
    ("SND/D.VAB", "AudioType_MusicKeys"), ("SND/D2.VAB", "AudioType_MusicKeys"), ("SND/E.VAB", "AudioType_MusicKeys"), ("SND/E2.VAB", "AudioType_MusicKeys"), ("SND/F.VAB", "AudioType_MusicKeys"),
    ("SND/F2.VAB", "AudioType_MusicKeys"), ("SND/G.VAB", "AudioType_MusicKeys"), ("SND/G2.VAB", "AudioType_MusicKeys"), ("SND/H.VAB", "AudioType_MusicKeys"), ("SND/H2.VAB", "AudioType_MusicKeys"),
    ("SND/I.VAB", "AudioType_MusicKeys"), ("SND/J.VAB", "AudioType_MusicKeys"), ("SND/J2.VAB", "AudioType_MusicKeys"), ("SND/K.VAB", "AudioType_MusicKeys"), ("SND/K2.VAB", "AudioType_MusicKeys"),
    ("SND/L.VAB", "AudioType_MusicKeys"), ("SND/M.VAB", "AudioType_MusicKeys"), ("SND/N.VAB", "AudioType_MusicKeys"), ("SND/O.VAB", "AudioType_MusicKeys"), ("SND/P.VAB", "AudioType_MusicKeys"),
    ("SND/Q.VAB", "AudioType_MusicKeys"), ("SND/R.VAB", "AudioType_MusicKeys"), ("SND/S.VAB", "AudioType_MusicKeys"), ("SND/T.VAB", "AudioType_MusicKeys"), ("SND/T2.VAB", "AudioType_MusicKeys"),
    ("SND/U.VAB", "AudioType_MusicKeys"), ("SND/UFO.VAB", "AudioType_MusicKeys"), ("SND/V.VAB", "AudioType_MusicKeys"), ("SND/W2.VAB", "AudioType_MusicKeys"), ("SND/X.VAB", "AudioType_MusicKeys"),
    ("SND/Y.VAB", "AudioType_MusicKeys"), ("SND/Z.VAB", "AudioType_MusicKeys"), ("SND/Z2.VAB", "AudioType_MusicKeys"), ("SND/Z3.VAB", "AudioType_MusicKeys"), ("SND/Z4.VAB", "AudioType_MusicKeys"),
    None,
    ("SND/A2.KDT", "AudioType_MusicSheet"), ("SND/B.KDT", "AudioType_MusicSheet"), ("SND/B2.KDT", "AudioType_MusicSheet"), ("SND/C.KDT", "AudioType_MusicSheet"), ("SND/C2.KDT", "AudioType_MusicSheet"),
    ("SND/D.KDT", "AudioType_MusicSheet"), ("SND/D2.KDT", "AudioType_MusicSheet"), ("SND/E.KDT", "AudioType_MusicSheet"), ("SND/E2.KDT", "AudioType_MusicSheet"), ("SND/F.KDT", "AudioType_MusicSheet"),
    ("SND/F2.KDT", "AudioType_MusicSheet"), ("SND/G.KDT", "AudioType_MusicSheet"), ("SND/G2.KDT", "AudioType_MusicSheet"), ("SND/H.KDT", "AudioType_MusicSheet"), ("SND/H2.KDT", "AudioType_MusicSheet"),
    ("SND/I.KDT", "AudioType_MusicSheet"), ("SND/J.KDT", "AudioType_MusicSheet"), ("SND/J2.KDT", "AudioType_MusicSheet"), ("SND/K.KDT", "AudioType_MusicSheet"), ("SND/K2.KDT", "AudioType_MusicSheet"),
    ("SND/L.KDT", "AudioType_MusicSheet"), ("SND/M.KDT", "AudioType_MusicSheet"), ("SND/N.KDT", "AudioType_MusicSheet"), ("SND/O.KDT", "AudioType_MusicSheet"), ("SND/P.KDT", "AudioType_MusicSheet"),
    ("SND/Q.KDT", "AudioType_MusicSheet"), ("SND/R.KDT", "AudioType_MusicSheet"), ("SND/S.KDT", "AudioType_MusicSheet"), ("SND/T.KDT", "AudioType_MusicSheet"), ("SND/T2.KDT", "AudioType_MusicSheet"),
    ("SND/U.KDT", "AudioType_MusicSheet"), ("SND/UFO.KDT", "AudioType_MusicSheet"), ("SND/V.KDT", "AudioType_MusicSheet"), ("SND/W2.KDT", "AudioType_MusicSheet"), ("SND/X.KDT", "AudioType_MusicSheet"),
    ("SND/Y.KDT", "AudioType_MusicSheet"), ("SND/Z.KDT", "AudioType_MusicSheet"), ("SND/Z2.KDT", "AudioType_MusicSheet"), ("SND/Z3.KDT", "AudioType_MusicSheet"), ("SND/Z4.KDT", "AudioType_MusicSheet"),
    None,
]

# Release-specific audio file swaps.
AUDIO_FILE_REPLACEMENTS = {
    "NTSC 1.1 99-02-10": {
        "SND/MAP000.VAB": "SND/MEP000.VAB",
        "SND/MAP100.VAB": "SND/MEP100.VAB",
        "SND/MAP101.VAB": "SND/MEP101.VAB",
        "SND/MAP102.VAB": "SND/MEP102.VAB",
        "SND/MAP103.VAB": "SND/MEP103.VAB",
        "SND/MAP502.VAB": "SND/MEP502.VAB",
        "SND/MAP604.VAB": "SND/MEP604.VAB",
    },
}

# Some g_AudioData sizes don't match actual audio data in NTSC, override with what the table has for them here.
AUDIO_VAG_OFFSET_OVERRIDES = {
    "NTSC 1.1 99-02-10": {
        "SND/MEP102.VAB": 5664,
        "SND/MEP103.VAB": 5664,
    },
}

VAB_HEADER_SIZE = 32
VAB_PROGRAM_ATTRS_SIZE = 128 * 16
VAB_TONE_ATTRS_SIZE_PER_PROGRAM = 16 * 32
VAB_VAG_OFFSETS_SIZE = 256 * 2

FILESIZE_STEP = 256

ENTRY_STRUCT = Struct("<3I")


def _createParser():
    parser = ArgumentParser()
    parser.add_argument("--executable", "-exe", type=FileType("rb"))
    parser.add_argument("--silentFile", "-fs", type=FileType("rb"))
    parser.add_argument("--hillFile", "-fh", type=FileType("rb"))
    parser.add_argument("outputFolder", type=Path, default=".")
    parser.add_argument("--exeChecksum", "-c", action="store_true")
    return parser


def _getChecksum(exe: BinaryIO):
    exe.seek(0)
    return crc32(exe.read(4096))


def _detectRelease(checksum: int, name: str) -> Release | None:
    for release in RELEASES:
        if checksum == release.checksum:
            logging.info(f"Determined the release as {release.id} ({release.name})")
            return release
    logging.error(f"Executable {name} has an unrecognized checksum! [{checksum:08X}]")
    logging.error("\tIt is not a supported Silent Hill executable.")
    return None


def _parseEntry(entry, release):
    meta, file1, file2 = ENTRY_STRUCT.unpack(entry)

    if not release.flags & Flags.ALT_FILE_STRUCT:
        name = "".join(chain(
            (chr(32 + ((file1 >> shift) & 63)) for shift in range(4, 28, 6)),
            (chr(32 + ((file2 >> shift) & 63)) for shift in range(0, 24, 6))
        )).strip()

        # size, lba, name, path, type
        return meta >> 19, meta & 0x7FFFF, name, release.dirs[file1 & 15], release.filetypes[(file2 >> 24) & 15]
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
        return (meta >> 19) & 0xFFF, meta & 0x7FFFF, name, release.dirs[directoryIndex], release.filetypes[
            extensionIndex]


def _formatEntry(size, lba, name, path, type, release):
    name = name.ljust(8)
    namesep = ','.join(f"'{name[i]}'" for i in range(0, len(name)))

    return f'{{ {lba:#07x}, {size:4d}, {release.dirs.index(path):2d}, FN({namesep}), {release.filetypes.index(type):2d} }}'


def _decryptOverlay(data: bytes):
    output = bytearray(data)
    outArray = memoryview(output).cast("I")  # uint32_t
    seed = 0

    for i, value in enumerate(outArray):
        seed = (seed + 0x01309125) & 0xffffffff
        seed = (seed * 0x03a452f7) & 0xffffffff
        outArray[i] ^= seed

    return output


# LZSS decompressor based on JP1.0 0x800CC924 code.
# Used (pointlessly) to compress the encrypted HP_SAFE1.BIN / S__SAFE2.BIN files, making them larger than the uncompressed versions.
# Also used (pointlessly) to compress the .CMP files in TEST folder, which also have the uncompressed versions alongside them.
def _decompressLzssFile(data: bytes) -> bytes:
    # Read the expected output size from the first 4 bytes
    expected_size = int.from_bytes(data[0:4], byteorder='little')

    input_ptr = 4  # Start after the size header
    output = bytearray()

    # Ring buffer (Sliding Window)
    window = bytearray([0] * 4096)
    window_ptr = 0xFEE  # Standard initial window pointer

    tag_register = 0

    while input_ptr < len(data) and expected_size > len(output):
        # "Tag Reload" Trick
        # Shift the register; if the 'sentinel' bit at 0x100 is gone, 
        # we've processed 8 bits and need a new tag byte.
        tag_register >>= 1

        if (tag_register & 0x100) == 0:
            if input_ptr >= len(data): break
            # Load new tag and set the sentinel bit at the 9th position
            tag_register = data[input_ptr] | 0xFF00
            input_ptr += 1

        # The LSB now contains our current flag
        if tag_register & 1:
            # 1 = Literal byte
            if input_ptr >= len(data): break
            byte = data[input_ptr]
            input_ptr += 1

            output.append(byte)
            window[window_ptr] = byte
            window_ptr = (window_ptr + 1) & 0xFFF
        else:
            # 0 = Reference (2 bytes)
            if input_ptr + 1 >= len(data): break

            b1 = data[input_ptr]
            b2 = data[input_ptr + 1]
            input_ptr += 2

            offset = b1 | ((b2 & 0xF0) << 4)
            length = (b2 & 0x0F) + 3

            for _ in range(length):
                byte = window[offset]
                output.append(byte)

                # Write to window and move window_ptr
                window[window_ptr] = byte
                window_ptr = (window_ptr + 1) & 0xFFF

                # Move reference offset forward (circularly)
                offset = (offset + 1) & 0xFFF

    return bytes(output)


def _extract(entries: Iterable[TableEntry], output: Path, file: BinaryIO, sectorSize: int, releaseFlags: int):
    index = 0
    for i in entries:
        outputPath = (output / i.path).absolute()
        if not outputPath.parent.exists():
            outputPath.parent.mkdir(parents=True)

        ext = i.type or "XA"
        logging.info(f"{index} Extracting {FILE_TYPE_NAMES[i.type]}(.{ext}) to {outputPath}...")

        file.seek((i.offset - entries[0].offset) * sectorSize)
        if not i.size == 0 and (i.type != ""):
            size = i.size * FILESIZE_STEP
        elif index + 1 < len(entries):
            size = (entries[index + 1].offset - i.offset) * sectorSize
        else:
            size = -1  # read until end of file
        data = file.read(size)
        if i.type == "BIN" and (releaseFlags & Flags.ENCRYPTED_1ST_FOLDER):
            if i.path.startswith("1ST"):
                logging.info(f"\tDecrypting {i.path}...")
                data = _decryptOverlay(data)
            elif "HP_SAFE1" in i.path or "S__SAFE2" in i.path:
                logging.info(f"\tDecompressing/decrypting {i.path}...")
                data = _decryptOverlay(_decompressLzssFile(data))
        elif i.type == "CMP":
            logging.info(f"\tDecompressing {i.path}...")
            decData = _decompressLzssFile(data)
            outputDecPath = outputPath.with_name(outputPath.name + ".dec")
            with outputDecPath.open("wb") as _file:
                _file.write(decData)

        with outputPath.open("wb") as _file:
            _file.write(data)
        index = index + 1


def _formatAudioData(entries: Iterable[TableEntry], output: Path, release: Release) -> str | None:
    lbas = {entry.path: entry.offset for entry in entries}
    replacements = AUDIO_FILE_REPLACEMENTS.get(release.id, {})
    files = [None if item is None else (replacements.get(item[0], item[0]), item[1]) for item in AUDIO_DATA_FILES]
    if any(item is not None and item[0] not in lbas for item in files):
        logging.info("Release does not contain every audio file of the final releases, skipping audio data")
        return None

    overrides = AUDIO_VAG_OFFSET_OVERRIDES.get(release.id, {})
    text = f"// Generated from {release.name} ({release.id})\n"
    for item in files:
        if item is None:
            text += f"/* {'':12s} */ {{ 0, 0, 0, 0, 0 }},\n"
            continue

        path, audioType = item
        with (output / path).open("rb") as file:
            header = file.read(VAB_HEADER_SIZE)

        if path.endswith(".VAB"):
            # VAB header: `fsize` at 0x0C, `ps` (program count) at 0x12.
            fileSize = int.from_bytes(header[12:16], "little")
            programCount = int.from_bytes(header[18:20], "little")
            vagDataOffset = (VAB_HEADER_SIZE + VAB_PROGRAM_ATTRS_SIZE +
                             (programCount * VAB_TONE_ATTRS_SIZE_PER_PROGRAM) + VAB_VAG_OFFSETS_SIZE)
        else:
            # KDT header: data size at 0x04, stored rounded up to 4 bytes.
            fileSize = (int.from_bytes(header[4:8], "little") + 3) & ~3
            vagDataOffset = 0

        vagDataOffset = overrides.get(path, vagDataOffset)
        text += f"/* {os.path.basename(path):12s} */ {{ {audioType + ',':21s} 0, {vagDataOffset:4d}, {fileSize:6d}, {lbas[path]:5d} }},\n"

    return text


def main():
    logging.basicConfig(level=logging.INFO)
    args = _createParser().parse_args()
    executable: BinaryIO = args.executable
    checksum = _getChecksum(executable)

    if args.exeChecksum:
        logging.info(f"Checksum of {executable.name}: {checksum:08X}")
        return
    else:
        release = _detectRelease(checksum, executable.name)
        if release is None:
            return

    originText = f"// Generated from {release.name} ({release.id})\n"
    headerText = originText
    enumText = f"    {originText}"
    entriesSilent = []
    entriesHill = []
    executable.seek(release.tocOffset)
    for i in range(release.fileCount):
        rawEntry = executable.read(ENTRY_STRUCT.size)
        size, lba, name, directory, type = _parseEntry(rawEntry, release)
        fullpath = os.path.join(directory, f"{name}.{type}" if type else f"{name}").replace("\\", "/")
        headerText += f"/* {i:4d} */ {_formatEntry(size, lba, name, directory, type, release)}, // {fullpath}\n"
        enumName = fullpath.replace("/", "_").replace("\\", "_").replace(".", "_")
        enumText += f"    FILE_{enumName} = {i}, // {fullpath}\n"
        entry = TableEntry(fullpath, type, size, lba)

        match directory:
            case "XA":
                entriesHill.append(entry)
            case _:
                entriesSilent.append(entry)
    executable.close()

    _extract(entriesSilent, args.outputFolder, args.silentFile, 2048, release.flags)

    if not release.flags & Flags.NO_XA_CONTAINER and args.hillFile:
        _extract(entriesHill, args.outputFolder, args.hillFile, 2336, release.flags)

    with open(os.path.join(args.outputFolder, "filetable.c.inc"), "a+") as f:
        f.truncate(0)
        f.write(headerText)
    with open(os.path.join(args.outputFolder, "fileenum.h.inc"), "a+") as f:
        f.truncate(0)
        f.write(enumText)

    audioDataText = _formatAudioData(entriesSilent, args.outputFolder, release)
    if audioDataText is not None:
        with open(os.path.join(args.outputFolder, "audiodata.c.inc"), "a+") as f:
            f.truncate(0)
            f.write(audioDataText)

    logging.info("All done!")


if __name__ == "__main__":
    main()
