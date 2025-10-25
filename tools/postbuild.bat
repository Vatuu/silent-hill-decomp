@echo off
setlocal EnableDelayedExpansion

::if %1 == build/out/1ST/BODYPROG.BIN (
::	set file=build\\out\\1ST\\BODYPROG.BIN
::	certutil -encodehex !file! !file!.temp0 0x4 > NUL
::	set i = 0
::	for /f "delims=" %%b in (!file!.temp0) do (
::		set /A i+=1
::		if i == 41534:
::			'\x0A\x09\x2E\x62'
::		if i == 41549:
::			'\x38\x0D\x0A\x09'
::		if i == 41657:
::		    '\x0D\x0A\x09\x2E'
::		if i == 41978:
::		    '\x09\x30\x78\x61'
::		
::	)
::	goto eof
::)

if %1 == build/out/1ST/BODYPROG.BIN (
	set file=build\\out\\1ST\\BODYPROG.BIN
	set file_temp0=!file!.temp0
	set file_temp1=!file!.temp1
	certutil -encodehex !file! !file_temp0! 0x4 > NUL
	echo. 2>!file_temp1! > NUL
	set i = 0
	for /f "delims=" %%b in (!file_temp0!) do (
		set /A i+=1
		set s=%%b
		if !i! == 41534 (
			set s=!s:00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00=00 00 00 00 00 00 00 00  00 00 00 00 0A 09 2E 62!
		)
		if !i! == 41549 (
			set s=!s:00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00=00 00 00 00 00 00 00 00  00 00 00 00 38 0D 0A 09!
		)
		if !i! == 41657 (
			set s=!s:00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00=00 00 00 00 00 00 00 00  00 00 00 00 0D 0A 09 2E!
		)
		if !i! == 41978 (
			set s=!s:00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00=00 00 00 00 00 00 00 00  00 00 00 00 09 30 78 61!
		)
		>>!file_temp1! echo !s!
	)
	del !file!
	del !file_temp0!
	certutil -decodehex !file_temp1! !file! 0x4 > NUL
	del !file_temp1!
	goto eof
)

if %1 == build/out/VIN/STREAM.BIN (
	set file=build\\out\\VIN\\STREAM.BIN
	set file_temp0=!file!.temp0
	set file_temp1=!file!.temp1
	certutil -encodehex !file! !file_temp0! 0x4 > NUL
	echo. 2>!file_temp1! > NUL
	set i = 0
	for /f "delims=" %%b in (!file_temp0!) do (
		set /A i+=1
		set s=%%b
		if !i! == 4783 (
			set s=!s:00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00=00 00 00 00 E4 73 40 AC  00 00 00 00 00 00 00 00!
		)
		>>!file_temp1! echo !s!
	)
	del !file!
	del !file_temp0!
	certutil -decodehex !file_temp1! !file! 0x4 > NUL
	del !file_temp1!
	goto eof
)

:eof