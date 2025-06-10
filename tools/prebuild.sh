#!/bin/bash

# Splat `lib` segments only support loading .o from inside .a file
# Loading .a has issues with dependency checks though
# For now, rewrite the linker scripts from splat to load loose .o instead
sed -i 's/\.a:/\//g' linkers/main.ld
sed -i 's/\.a:/\//g' linkers/bodyprog.ld
sed -i 's/\.a:/\//g' linkers/screens/stream.ld

# .bss section includes 16 random padding bytes, which prevent us from marking them as .bss
# We'll replace those bytes with 00 so that build can link properly, postbuild.sh will then patch them back in
sed -i 's/0x090A0D38/0x00000000/g' asm/bodyprog/data/bodyprog_A24CC.bss.s
sed -i 's/0x622E090A/0x00000000/g' asm/bodyprog/data/bodyprog_A23DC.bss.s
sed -i 's/0x2E090A0D/0x00000000/g' asm/bodyprog/data/bodyprog_A28B0.bss.s
sed -i 's/0x61783009/0x00000000/g' asm/bodyprog/data/bodyprog_A28B0.bss.s

sed -i 's/0xAC4073E4/0x00000000/g' asm/screens/stream/data/stream_unk.bss.s
