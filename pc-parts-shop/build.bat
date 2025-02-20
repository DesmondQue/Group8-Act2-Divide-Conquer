@echo off
REM Get the directory where the batch file is located
cd /d "%~dp0"

REM Create directories if they don't exist
if not exist "bin" mkdir bin
if not exist "data" mkdir data

REM Compile the program
g++ src/main.cpp src/utils/file_handler.cpp -o bin/main

if %errorlevel% equ 0 (
    REM Run from project root to maintain correct relative paths
    .\bin\main
) else (
    echo Compilation failed!
    pause
)
pause