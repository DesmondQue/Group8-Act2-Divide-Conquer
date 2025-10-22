@echo off
cd /d "%~dp0"

g++ src/main.cpp src/utils/file_handler.cpp -o bin/main

if %errorlevel% equ 0 (
    .\bin\main
) else (
    echo Compilation failed!
    pause
)
pause