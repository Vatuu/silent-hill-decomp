import sys
import os

# Patch garbage bytes in .bss segment

if __name__ == "__main__":
    match sys.argv[1]:
        case "screens/stream" | "build/USA/out/VIN/STREAM.BIN":
            overlayFile = open("build/USA/out/VIN/STREAM.BIN", "r+b")
            overlayFile.seek(0x12AE4)
            overlayFile.write(b'\xE4\x73\x40\xAC')
            overlayFile.close()
        case "bodyprog" | "build/USA/out/1ST/BODYPROG.BIN" | "build/JAP0/out/1ST/BODYPROG.BIN":
            usaPath = "build/USA/out/1ST/BODYPROG.BIN"
            jap0Path = "build/JAP0/out/1ST/BODYPROG.BIN"
            if os.path.isfile(usaPath):
                overlayFile = open(usaPath, "r+b")
                overlayFile.seek(0xA23DC)
                overlayFile.write(b'\x0A\x09\x2E\x62')
                overlayFile.seek(0xA24CC)
                overlayFile.write(b'\x38\x0D\x0A\x09')
                overlayFile.seek(0xA2B8C)
                overlayFile.write(b'\x0D\x0A\x09\x2E')
                overlayFile.seek(0xA3F9C)
                overlayFile.write(b'\x09\x30\x78\x61')
                overlayFile.seek(0x9827C)
                overlayFile.write(b'\x22\x00\xA2\x97')
                overlayFile.seek(0x98284)
                overlayFile.write(b'\x21\x10\x46\x00')
                overlayFile.seek(0x9B08C)
                overlayFile.write(b'\x02\x00\x01\x00')
                overlayFile.seek(0x9CA4C)
                overlayFile.write(b'\x04\xCF\x41\x76')
                overlayFile.seek(0x9CA54)
                overlayFile.write(b'\x00\x18\xE3\xB8')
                overlayFile.seek(0x9F75C)
                overlayFile.write(b'\x10\x00\xB0\x8F')
                overlayFile.seek(0x9FD88)
                overlayFile.write(b'\x00\x00\x42\x30')
                overlayFile.seek(0x9FD8C)
                overlayFile.write(b'\x07\x00\x40\x14')
                overlayFile.seek(0x9FD94)
                overlayFile.write(b'\x0F\x80\x02\x3C')
                overlayFile.seek(0x9F774)
                overlayFile.write(b'\x21\x80\x80\x00')
                overlayFile.seek(0x9F8F4)
                overlayFile.write(b'\x00\x00\x02\x00')
                overlayFile.seek(0x9F96C)
                overlayFile.write(b'\x10\x00\xB0\x8F')
                overlayFile.seek(0x9FABC)
                overlayFile.write(b'\x30\x00\xA4\x27')
                overlayFile.seek(0x9FACC)
                overlayFile.write(b'\x61\x26\x01\x0C')
                overlayFile.seek(0x910CC)
                overlayFile.write(b'\x3C\x38\x92\xD8')
                overlayFile.seek(0x910D0)
                overlayFile.write(b'\x00\x00\x00\x00')
                overlayFile.seek(0x981B4)
                overlayFile.write(b'\x80\x18\x13\x00')
                overlayFile.seek(0x981B8)
                overlayFile.write(b'\x00\x00\x00\x00')
                overlayFile.seek(0x981E0)
                overlayFile.write(b'\x00\x70\xE5\x8D')
                overlayFile.seek(0x981E4)
                overlayFile.write(b'\x05\x00\x02\x24')
                overlayFile.seek(0x981EC)
                overlayFile.write(b'\x28\x00\x02\x24')
                overlayFile.seek(0x981F0)
                overlayFile.write(b'\x00\x00\x00\x00')
                overlayFile.seek(0x9821C)
                overlayFile.write(b'\x21\x10\x49\x00')
                overlayFile.seek(0x98220)
                overlayFile.write(b'\x00\x00\x00\x00')
                overlayFile.close()
            if os.path.isfile(jap0Path):
                overlayFile = open(jap0Path, "r+b")
                overlayFile.seek(0xA22B8)
                overlayFile.write(b'\x00\x4E\x0A\x09\x09\x09\x82\xB7')
                overlayFile.seek(0xA22C4)
                overlayFile.write(b'\x8C\x8C\x82\xC6')
                overlayFile.seek(0xA490C)
                overlayFile.write(b'\x3A\x20\x25\x64')
                overlayFile.seek(0xA49FC)
                overlayFile.write(b'\x54\x81\x09\x80')
                overlayFile.seek(0xA50BC)
                overlayFile.write(b'\x73\x5F\x6F\x72')
                overlayFile.seek(0xA64CC)
                overlayFile.write(b'\x6F\x72\x67\x65')
                overlayFile.close()
        case "screens/b_konami" | "build/USA/out/1ST/B_KONAMI.BIN":
            # Random pad bytes between b_konami.c .data and lzss.c .data.
            overlayFile = open("build/USA/out/1ST/B_KONAMI.BIN", "r+b")
            overlayFile.seek(0xF79)
            overlayFile.write(b'\x1F\xCE\xF3')
        case "maps/map3_s06" | "build/USA/out/VIN/MAP3_S06.BIN":
            # Random bytes at end of rodata section, linker artifact?
            overlayFile = open("build/USA/out/VIN/MAP3_S06.BIN", "r+b")
            overlayFile.seek(0x1D65)
            overlayFile.write(b'\x65\x74\x5F')
            overlayFile.close()
        case "maps/map4_s05" | "build/USA/out/VIN/MAP4_S05.BIN":
            # Random bytes at end of rodata section, linker artifact?
            overlayFile = open("build/USA/out/VIN/MAP4_S05.BIN", "r+b")
            overlayFile.seek(0x1729)
            overlayFile.write(b'\x65\x5F\x77')
            overlayFile.close()
        case "maps/map5_s01" | "build/USA/out/VIN/MAP5_S01.BIN":
            # Random bytes at end of rodata section, linker artifact?
            overlayFile = open("build/USA/out/VIN/MAP5_S01.BIN", "r+b")
            overlayFile.seek(0x3515)
            overlayFile.write(b'\x9C\x03\x08')
            overlayFile.close()
        case "maps/map6_s01" | "build/USA/out/VIN/MAP6_S01.BIN":
            # Random bytes at end of rodata section, linker artifact?
            overlayFile = open("build/USA/out/VIN/MAP6_S01.BIN", "r+b")
            overlayFile.seek(0x25e6)
            overlayFile.write(b'\x40\x14')
            overlayFile.close()
