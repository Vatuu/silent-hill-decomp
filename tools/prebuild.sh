#!/bin/bash

# prebuild.sh [target_name]

# Splat `lib` segments only support loading .o from inside .a file
# Loading .a has issues with dependency checks though
# For now, rewrite the ld linker scripts from splat to load loose .o instead

if [ "$1" == "main" ]; then
    sed -i 's/\.a:/\//g' linkers/main.ld
elif [ "$1" == "bodyprog" ]; then
    sed -i 's/\.a:/\//g' linkers/bodyprog.ld
    # BODYPROG.BIN .bss section contains 16 random padding bytes, which prevents us marking them as .bss in linker script
    # We'll replace those bytes with 00 so that build can link properly
    # postbuild.sh will then patch them back in after linking
    sed -i 's/0x622E090A/0x00000000/g' asm/bodyprog/data/bodyprog_800C6F3C.bss.s
    sed -i 's/0x090A0D38/0x00000000/g' asm/bodyprog/data/bodyprog_800C702C.bss.s
    sed -i 's/0x2E090A0D/0x00000000/g' asm/bodyprog/data/bodyprog_800C7410.bss.s
    sed -i 's/0x61783009/0x00000000/g' asm/bodyprog/data/bodyprog_800C7410.bss.s
	
	# It is very possible that part of what is considered part of the data segment
	# is actually part of the bss segment.
    #sed -i 's/0x42/0x00/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x30/0x00/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x07/0x00/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x40/0x00/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x14/0x00/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x0F/0x00/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x80/0x00/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x02/0x00/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x3C/0x00/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x0C012661/0x00000000/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x27A40030/0x00000000/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x0010/0x0000/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x8FB0/0x0000/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x00000010/0x00000000/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x0021/0x0000/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x0080/0x0000/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
    #sed -i 's/0x00020000/0x00000000/g' asm/bodyprog/data/bodyprog_800C15D8.bss.s
elif [ "$1" == "screens/stream" ] || [ "$1" == "stream" ]; then
    sed -i 's/\.a:/\//g' linkers/screens/stream.ld

    # STREAM.BIN also includes 4 random bytes in .bss
    sed -i 's/0xAC4073E4/0x00000000/g' asm/screens/stream/data/stream_801F50E4.bss.s
fi
