import sys

# Patch random/uninitialized bytes in .bss section back into BODYPROG.BIN / STREAM.BIN

if __name__ == "__main__":
    if sys.argv[1] == "screens/stream" or sys.argv[1] == "build/out/VIN/STREAM.BIN":
        overlayFile = open("build/out/VIN/STREAM.BIN", "r+b")
        overlayFile.seek(0x12AE4)
        overlayFile.write(b'\xE4\x73\x40\xAC')
        overlayFile.close()
    elif sys.argv[1] == "bodyprog" or sys.argv[1] == "build/out/1ST/BODYPROG.BIN":
        overlayFile = open("build/out/1ST/BODYPROG.BIN", "r+b")
        overlayFile.seek(0xA23DC)
        overlayFile.write(b'\x0A\x09\x2E\x62')
        overlayFile.seek(0xA24CC)
        overlayFile.write(b'\x38\x0D\x0A\x09')
        overlayFile.seek(0xA2B8C)
        overlayFile.write(b'\x0D\x0A\x09\x2E')
        overlayFile.seek(0xA3F9C)
        overlayFile.write(b'\x09\x30\x78\x61')
        overlayFile.close()
    elif sys.argv[1] == "maps/map3_s06" or sys.argv[1] == "build/out/VIN/MAP3_S06.BIN":
        # Random bytes at end of rodata section, linker artifact?
        overlayFile = open("build/out/VIN/MAP3_S06.BIN", "r+b")
        overlayFile.seek(0x1D65)
        overlayFile.write(b'\x65\x74\x5F')
        overlayFile.close()
    elif sys.argv[1] == "maps/map4_s05" or sys.argv[1] == "build/out/VIN/MAP4_S05.BIN":
        # Random bytes at end of rodata section, linker artifact?
        overlayFile = open("build/out/VIN/MAP4_S05.BIN", "r+b")
        overlayFile.seek(0x1729)
        overlayFile.write(b'\x65\x5F\x77')
        overlayFile.close()
    elif sys.argv[1] == "maps/map5_s01" or sys.argv[1] == "build/out/VIN/MAP5_S01.BIN":
        # Random bytes at end of rodata section, linker artifact?
        overlayFile = open("build/out/VIN/MAP5_S01.BIN", "r+b")
        overlayFile.seek(0x3515)
        overlayFile.write(b'\x9C\x03\x08')
        overlayFile.close()
