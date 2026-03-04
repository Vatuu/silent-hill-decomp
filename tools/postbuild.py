import sys
import os

# Patch garbage bytes in .bss segment

USA_STREAM = [
    [0x12AE4, b'\xE4\x73\x40\xAC']
]

USA_BODYPROG = [
    [0x9BF, b'\x4c\x00\x95\xab\x90'],
    [0xA23DC, b'\x0A\x09\x2E\x62'],
    [0xA24CC, b'\x38\x0D\x0A\x09'],
    [0xA2B8C, b'\x0D\x0A\x09\x2E'],
    [0xA3F9C, b'\x09\x30\x78\x61'],
    [0x9827C, b'\x22\x00\xA2\x97'],
    [0x98284, b'\x21\x10\x46'],
    [0x9B08C, b'\x02\x00\x01'],
    [0x9CA4C, b'\x04\xCF\x41\x76'],
    [0x9CA55, b'\x18\xE3\xB8'],
    [0x9F75C, b'\x10\x00\xB0\x8F'],
    [0x9FD8A, b'\x42\x30'],
    [0x9FD8C, b'\x07\x00\x40\x14'],
    [0x9FD94, b'\x0F\x80\x02\x3C'],
    [0x9F774, b'\x21\x80\x80'],
    [0x9F8F6, b'\x02'],
    [0x9F96C, b'\x10\x00\xB0\x8F'],
    [0x9FABC, b'\x30\x00\xA4\x27'],
    [0x9FACC, b'\x61\x26\x01\x0C'],
    [0x910CC, b'\x3C\x38\x92\xD8'],
    [0x981B4, b'\x80\x18\x13'],
    [0x981E1, b'\x70\xE5\x8D'],
    [0x981E4, b'\x05\x00\x02\x24'],
    [0x981EC, b'\x28\x00\x02\x24'],
    [0x9821C, b'\x21\x10\x49'],
]

JAP0_BODYPROG = [
    [0x12E, b'\xE8\xFF'],
    [0x871EE, b'\x24\x33'],
    [0x935FC, b'\xAF\x28\xFF\xAD'],
    [0x9A6E6, b'\x60'],
    [0x9A712, b'\x08\x00\x09\x00\x08\x00'],
    [0x9A71E, b'\x58'],
    [0x9A74C, b'\x04\x04\x04\x04'],
    [0x9D5BD, b'\xFE'],
    [0x9EF7C, b'\x10\x00\xB0\xAF'],
    [0x9EF87, b'\x16'],
    [0xA22B9, b'\x4E\x0A\x09\x09\x09\x82\xB7'],
    [0xA22C4, b'\x8C\x8C\x82\xC6'],
    [0xA490C, b'\x3A\x20\x25\x64'],
    [0xA49FC, b'\x54\x81\x09\x80'],
    [0xA50BC, b'\x73\x5F\x6F\x72'],
    [0xA64CC, b'\x6F\x72\x67\x65']
]

if __name__ == "__main__":
    match sys.argv[1]:
        case "screens/stream" | "build/USA/out/VIN/STREAM.BIN":
            file = open("build/USA/out/VIN/STREAM.BIN", "r+b")
            for data in USA_STREAM:
                file.seek(data[0])
                file.write(data[1])
            file.close()
        case "bodyprog" | "build/USA/out/1ST/BODYPROG.BIN" | "build/JAP0/out/1ST/BODYPROG.BIN":
            usaPath = "build/USA/out/1ST/BODYPROG.BIN"
            jap0Path = "build/JAP0/out/1ST/BODYPROG.BIN"
            if os.path.isfile(usaPath):
                file = open(usaPath, "r+b")
                for data in USA_BODYPROG:
                    file.seek(data[0])
                    file.write(data[1])
                file.close()
            if os.path.isfile(jap0Path):
                file = open(jap0Path, "r+b")
                for data in JAP0_BODYPROG:
                    file.seek(data[0])
                    file.write(data[1])
                file.close()
        case "screens/b_konami" | "build/USA/out/1ST/B_KONAMI.BIN":
            # Random pad bytes between b_konami.c .data and lzss.c .data.
            file = open("build/USA/out/1ST/B_KONAMI.BIN", "r+b")
            file.seek(0xF79)
            file.write(b'\x1F\xCE\xF3')
        case "maps/map3_s06" | "build/USA/out/VIN/MAP3_S06.BIN":
            # Random bytes at end of rodata section, linker artifact?
            file = open("build/USA/out/VIN/MAP3_S06.BIN", "r+b")
            file.seek(0x1D65)
            file.write(b'\x65\x74\x5F')
            file.close()
        case "maps/map4_s05" | "build/USA/out/VIN/MAP4_S05.BIN":
            # Random bytes at end of rodata section, linker artifact?
            file = open("build/USA/out/VIN/MAP4_S05.BIN", "r+b")
            file.seek(0x1729)
            file.write(b'\x65\x5F\x77')
            file.close()
        case "maps/map5_s01" | "build/USA/out/VIN/MAP5_S01.BIN":
            # Random bytes at end of rodata section, linker artifact?
            file = open("build/USA/out/VIN/MAP5_S01.BIN", "r+b")
            file.seek(0x3515)
            file.write(b'\x9C\x03\x08')
            file.close()
        case "maps/map6_s01" | "build/USA/out/VIN/MAP6_S01.BIN":
            # Random bytes at end of rodata section, linker artifact?
            file = open("build/USA/out/VIN/MAP6_S01.BIN", "r+b")
            file.seek(0x25e6)
            file.write(b'\x40\x14')
            file.close()
