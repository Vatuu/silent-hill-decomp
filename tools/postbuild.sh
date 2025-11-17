#!/bin/bash

# postbuild.sh [target_name]

# Patch random/uninitialized bytes in .bss section back into BODYPROG.BIN / STREAM.BIN

if [ "$1" == "bodyprog" ] || [ "$1" == "build/out/1ST/BODYPROG.BIN" ]; then
    printf '\x0A\x09\x2E\x62' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0xA23DC)) conv=notrunc status=none
    printf '\x38\x0D\x0A\x09' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0xA24CC)) conv=notrunc status=none
    printf '\x0D\x0A\x09\x2E' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0xA2B8C)) conv=notrunc status=none
    printf '\x09\x30\x78\x61' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0xA3F9C)) conv=notrunc status=none
    #printf '\x10\x00\xB0\x8F' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0x9F75C)) conv=notrunc status=none
	#printf '\x21\x80\x80\x00' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0x9F774)) conv=notrunc status=none
    #printf '\x00\x00\x02\x00' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0x9F8F4)) conv=notrunc status=none
    #printf '\x10\x00\xB0\x8F' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0x9F96C)) conv=notrunc status=none
    #printf '\x30\x00\xA4\x27' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0x9FABC)) conv=notrunc status=none
    #printf '\x61\x26\x01\x0C' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0x9FACC)) conv=notrunc status=none
    #printf '\x00\x00\x42\x30\x07\x00\x40\x14\x00\x00\x00\x00\x0F\x80\x02\x3C' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0x9FD88)) conv=notrunc status=none
elif [ "$1" == "screens/stream" ] || [ "$1" == "build/out/VIN/STREAM.BIN" ]; then
    printf '\xE4\x73\x40\xAC' | dd of=build/out/VIN/STREAM.BIN bs=1 seek=$((0x12AE4)) conv=notrunc status=none
fi
