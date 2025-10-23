@echo off
setlocal enabledelayedexpansion
echo %1

:: Pls don't make me get the BAD+ ending because of this horrid of code ;-; -Will

if %1 == main (
	echo MAIN
	goto replace_o
)
if %1 == screens\stream (
	echo STREAM
	goto replace_bss
	:return_stream
	goto replace_o
)
if %1 == bodyprog (
	echo BODYFROG
	goto replace_bss
	:return_bodyfrog
	goto replace_o
)

goto eof
:replace_bss
if %1 == screens\stream (
	set mainbss=asm\\screens\\stream\\data\\stream_801F50E4.bss.s
	set tempbss=!mainbss!.temp
	
	for /f "delims=" %%b in (!mainbss!) do (		
		set s=%%b
		set s=!s:.word 0xAC4073E4=.word 0x00000000!
		>>!tempbss! echo !s!
	)

	del !mainbss!
	
	copy !tempbss! !mainbss! > NUL
	
	del !tempbss!

	goto return_stream
) else %1 == bodyprog (
	set mainbss=asm/bodyprog/data/bodyprog_800C6F3C.bss.s asm/bodyprog/data/bodyprog_800C702C.bss.s asm/bodyprog/data/bodyprog_800C7410.bss.s
	
	for /f "delims=" %%c in (!mainbss!) do (
		echo !c!
	)

	
	goto return_bodyfrog
)
goto eof
:replace_o
set "mainlinker=linkers\%1.ld"
set "templinker=linkers\%1.ld.temp"

for /f "delims=" %%a in (!mainlinker!) do (
	set s=%%a
	set s=!s:.a:=/!
	>>!templinker! echo !s!
)

del !mainlinker!

copy !templinker! !mainlinker! > NUL

del !templinker!

:eof


::#!/bin/bash
::
::# prebuild.sh [target_name]
::
::# Splat `lib` segments only support loading .o from inside .a file
::# Loading .a has issues with dependency checks though
::# For now, rewrite the ld linker scripts from splat to load loose .o instead
::
::if [ "$1" == "main" ]; then
::    sed -i 's/\.a:/\//g' linkers/main.ld
::elif [ "$1" == "bodyprog" ]; then
::    sed -i 's/\.a:/\//g' linkers/bodyprog.ld
::    # BODYPROG.BIN .bss section contains 16 random padding bytes, which prevents us marking them as .bss in linker script
::    # We'll replace those bytes with 00 so that build can link properly
::    # postbuild.sh will then patch them back in after linking
::    sed -i 's/0x622E090A/0x00000000/g' asm/bodyprog/data/bodyprog_800C6F3C.bss.s
::    sed -i 's/0x090A0D38/0x00000000/g' asm/bodyprog/data/bodyprog_800C702C.bss.s
::    sed -i 's/0x2E090A0D/0x00000000/g' asm/bodyprog/data/bodyprog_800C7410.bss.s
::    sed -i 's/0x61783009/0x00000000/g' asm/bodyprog/data/bodyprog_800C7410.bss.s
::elif [ "$1" == "screens/stream" ]; then
::    sed -i 's/\.a:/\//g' linkers/screens/stream.ld
::
::    # STREAM.BIN also includes 4 random bytes in .bss
::    sed -i 's/0xAC4073E4/0x00000000/g' asm/screens/stream/data/stream_801F50E4.bss.s
::fi