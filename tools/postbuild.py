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
