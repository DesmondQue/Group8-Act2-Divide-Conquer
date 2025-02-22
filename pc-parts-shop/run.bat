@echo off
cd /d "%~dp0"

g++ src/main.cpp src/utils/file_handler.cpp src/algorithms/merge_sort.cpp src/algorithms/quick_sort.cpp -o bin/main

if %errorlevel% equ 0 (
    .\bin\main
) else (
    echo Compilation failed!
    pause
)
pause