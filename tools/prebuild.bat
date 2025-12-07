@echo off
setlocal enabledelayedexpansion

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