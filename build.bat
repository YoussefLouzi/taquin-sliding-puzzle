@echo off
REM Taquin - Sliding Puzzle Game Build Script for Windows
REM This script builds the game without requiring Make

echo ========================================
echo Taquin - Sliding Puzzle Game Builder
echo ========================================
echo.

REM Create directories if they don't exist
if not exist "bin" mkdir bin
if not exist "obj" mkdir obj

echo Creating object files...

REM Compile source files
gcc -Wall -Wextra -std=c99 -O2 -c main.c -o obj/main.o -IC:/development/i686-w64-mingw32/include/SDL2 -IC:/development/SDL2/x86_64-w64-mingw32/include/SDL2
if errorlevel 1 (
    echo Error compiling main.c
    pause
    exit /b 1
)

gcc -Wall -Wextra -std=c99 -O2 -c game.c -o obj/game.o -IC:/development/i686-w64-mingw32/include/SDL2 -IC:/development/SDL2/x86_64-w64-mingw32/include/SDL2
if errorlevel 1 (
    echo Error compiling game.c
    pause
    exit /b 1
)

gcc -Wall -Wextra -std=c99 -O2 -c render.c -o obj/render.o -IC:/development/i686-w64-mingw32/include/SDL2 -IC:/development/SDL2/x86_64-w64-mingw32/include/SDL2
if errorlevel 1 (
    echo Error compiling render.c
    pause
    exit /b 1
)

echo Linking executable...

REM Link the executable
gcc obj/main.o obj/game.o obj/render.o -o bin/taquin.exe -LC:/development/i686-w64-mingw32/lib -LC:/development/SDL2/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2
if errorlevel 1 (
    echo Error linking executable
    pause
    exit /b 1
)

echo.
echo ========================================
echo Build completed successfully!
echo Executable: bin/taquin.exe
echo ========================================
echo.

REM Ask if user wants to run the game
set /p choice="Do you want to run the game now? (y/n): "
if /i "%choice%"=="y" (
    echo Starting game...
    bin\taquin.exe
)

pause
