import sys

if __name__ == "__main__":
    if sys.argv[1] == "build/out/VIN/STREAM.BIN":
        overlayFile = open(sys.argv[1], "r+b")
        overlayFile.seek(0x12AE4)
        overlayFile.write(b'\xE4\x73\x40\xAC')
        overlayFile.close()
    elif sys.argv[1] == "build/out/1ST/BODYPROG.BIN":
        overlayFile = open(sys.argv[1], "r+b")
        overlayFile.seek(0xA23DC)
        overlayFile.write(b'\x0A\x09\x2E\x62')
        overlayFile.seek(0xA24CC)
        overlayFile.write(b'\x38\x0D\x0A\x09')
        overlayFile.seek(0xA2B8C)
        overlayFile.write(b'\x0D\x0A\x09\x2E')
        overlayFile.seek(0xA3F9C)
        overlayFile.write(b'\x09\x30\x78\x61')
        overlayFile.close()