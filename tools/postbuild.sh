#!/bin/bash

# Patch random bytes in .bss section back into BODYPROG / STREAM.BIN

printf '\x0A\x09\x2E\x62' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0xA23DC)) conv=notrunc status=none
printf '\x38\x0D\x0A\x09' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0xA24CC)) conv=notrunc status=none
printf '\x0D\x0A\x09\x2E' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0xA2B8C)) conv=notrunc status=none
printf '\x09\x30\x78\x61' | dd of=build/out/1ST/BODYPROG.BIN bs=1 seek=$((0xA3F9C)) conv=notrunc status=none

printf '\xE4\x73\x40\xAC' | dd of=build/out/VIN/STREAM.BIN bs=1 seek=$((0x12AE4)) conv=notrunc status=none
