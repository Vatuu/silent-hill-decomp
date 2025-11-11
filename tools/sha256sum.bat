@echo off
setlocal EnableDelayedExpansion

set "hash_list_file=%1/checksum.sha"

if not exist "%hash_list_file%" (
    echo Error: File "%hash_list_file%" not found.
    goto :eof
)

for /f "delims=" %%L in (%hash_list_file%) do (
    set "hash_list_line=%%L"
	set "hash_filename=!hash_list_line:~66!"
	if exist "!hash_filename!" (
		set "hash_target=!hash_list_line:~0,64!"
		for /f "delims=" %%B in ('certutil -hashfile !hash_filename! sha256 ^| find /v ":"') do set "hash_result=%%B"
		if !hash_target! == !hash_result! (
			echo !hash_filename!: OK
		) else (
			echo !hash_filename!: FAILED
		)
	)
)

:eof