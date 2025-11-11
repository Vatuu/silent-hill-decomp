@echo off

tools\win-build\iconv\iconv.exe -f UTF-8 -t CP932 %1 > %2 2>nul
exit /b 0