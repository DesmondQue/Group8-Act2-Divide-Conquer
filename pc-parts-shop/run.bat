@echo off
cd /d "%~dp0"

g++ src/main.cpp src/utils/file_handler.cpp -o bin/main.exe

if %errorlevel% equ 0 (
    echo Compilation successful!
    .\bin\main.exe
) else (
    echo Compilation failed!
    pause
)