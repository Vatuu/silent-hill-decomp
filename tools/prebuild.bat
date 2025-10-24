@echo off
setlocal enabledelayedexpansion

:: Pls don't make me get the BAD+ ending because of this horrid of code ;-; -Will

if %1 == main (
	goto replace_o
)
if %1 == stream (
	goto replace_bss
	:return_stream
	goto replace_o
)
if %1 == bodyprog (
	goto replace_bss
	:return_bodyfrog
	goto replace_o
)

goto eof
:replace_bss
if %1 == stream (
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
)
if %1 == bodyprog (
	set mainbss=asm\\bodyprog\\data\\bodyprog_800C6F3C.bss.s
	set tempbss=!mainbss!.temp
	
	for /f "delims=" %%b in (!mainbss!) do (
		set s=%%b
		set s=!s:.word 0x622E090A=.word 0x00000000!
		>>!tempbss! echo !s!
	)

	del !mainbss!
	
	copy !tempbss! !mainbss! > NUL
	
	del !tempbss!

	
	set mainbss=asm\\bodyprog\\data\\bodyprog_800C702C.bss.s
	set tempbss=!mainbss!.temp
	
	for /f "delims=" %%b in (!mainbss!) do (
		set s=%%b
		set s=!s:.word 0x090A0D38=.word 0x00000000!
		>>!tempbss! echo !s!
	)

	del !mainbss!
	
	copy !tempbss! !mainbss! > NUL
	
	del !tempbss!

	set mainbss=asm\\bodyprog\\data\\bodyprog_800C7410.bss.s
	set tempbss=!mainbss!.temp
	
	for /f "delims=" %%b in (!mainbss!) do (
		set s=%%b
		set s=!s:.word 0x2E090A0D=.word 0x00000000!
		set s=!s:.word 0x61783009=.word 0x00000000!
		>>!tempbss! echo !s!
	)

	del !mainbss!
	
	copy !tempbss! !mainbss! > NUL
	
	del !tempbss!
	
	goto return_bodyfrog
)
goto eof
:replace_o
if %1 == stream (
	set "mainlinker=linkers\screens\%1.ld"
	set "templinker=linkers\screens\%1.ld.temp"
) else (
	set "mainlinker=linkers\%1.ld"
	set "templinker=linkers\%1.ld.temp"
)

for /f "delims=" %%a in (!mainlinker!) do (
	set s=%%a
	set s=!s:.a:=/!
	>>!templinker! echo !s!
)

del !mainlinker!

copy !templinker! !mainlinker! > NUL

del !templinker!

:eof