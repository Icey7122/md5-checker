@echo off
REM Compile MD5 program
echo Compiling md5.c...

REM Try to use gcc (MinGW)
gcc -o md5.exe md5.c -Wall

if %ERRORLEVEL% EQU 0 (
    echo Compilation successful! md5.exe created.
    echo.
    echo Usage: md5.exe file1 [file2 ...]
    echo.
    echo Example: md5.exe test.txt
) else (
    echo Compilation failed. Please install MinGW or check your compiler.
    pause
)
