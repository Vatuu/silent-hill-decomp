@echo off
setlocal EnableDelayedExpansion

::if %1 == build/out/1ST/BODYPROG.BIN (
::	set file=build\\out\\1ST\\BODYPROG.BIN
::	certutil -encodehex !file! !file!.temp0 0x4 > NUL
::	set i = 0
::	echo lol
::	for /f "delims=" %%b in (!file!.temp0) do (
::		set /A i+=1
::		echo !i!
::	)
::	goto eof
::)
::if %1 == build/out/VIN/STREAM.BIN (
::	goto eof
::)


:eof