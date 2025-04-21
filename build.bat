@echo off
echo Console Chess - Build Script

REM Check for GCC in common locations
SET GCC_CMD=gcc
SET GCC_FOUND=0
WHERE %GCC_CMD% >nul 2>nul
IF %ERRORLEVEL% EQU 0 (
    SET GCC_FOUND=1
) ELSE (
    REM Try common MinGW locations
    IF EXIST "C:\MinGW\bin\gcc.exe" (
        SET GCC_CMD=C:\MinGW\bin\gcc.exe
        SET GCC_FOUND=1
    )
    IF EXIST "C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe" (
        SET GCC_CMD=C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe
        SET GCC_FOUND=1
    )
    IF EXIST "C:\Program Files\mingw-w64\x86_64-12.2.0-release-posix-seh-ucrt-rt_v10\mingw64\bin\gcc.exe" (
        SET GCC_CMD=C:\Program Files\mingw-w64\x86_64-12.2.0-release-posix-seh-ucrt-rt_v10\mingw64\bin\gcc.exe
        SET GCC_FOUND=1
    )
    IF EXIST "C:\msys64\mingw64\bin\gcc.exe" (
        SET GCC_CMD=C:\msys64\mingw64\bin\gcc.exe
        SET GCC_FOUND=1
    )
)

IF %GCC_FOUND% EQU 0 (
    echo ERROR: GCC compiler not found. Please install MinGW or add it to your PATH.
    echo You can download MinGW from: https://www.mingw-w64.org/downloads/
    goto end
)

echo Using compiler: %GCC_CMD%
echo.
echo Select which version to build:
echo 1. English version
echo 2. Hungarian version
echo 3. Build both versions

set /p choice="Enter your choice (1-3): "

if "%choice%"=="1" goto build_english
if "%choice%"=="2" goto build_hungarian
if "%choice%"=="3" goto build_both

echo Invalid choice!
goto end

:build_english
echo Building English version...
echo Executing: %GCC_CMD% -Isrc\include src\ui\main_english.c src\utils\globals.c src\core\chess_constants.c src\core\board_setup.c src\game\game.c src\game\piece_moves.c src\validation\move_validator.c src\validation\check_validator.c src\game\game_moves.c src\validation\conversions.c src\utils\save_load.c src\utils\memory_utils.c src\ui\exit.c src\ui\error_message.c src\ui\user_guide.c src\ui\menu_new.c src\utils\util.c src\core\position_exchange.c src\game\pawn_promotion.c src\game\king_moves.c -o chess_english.exe
%GCC_CMD% -Isrc\include src\ui\main_english.c src\utils\globals.c src\core\chess_constants.c src\core\board_setup.c src\game\game.c src\game\piece_moves.c src\validation\move_validator.c src\validation\check_validator.c src\game\game_moves.c src\validation\conversions.c src\utils\save_load.c src\utils\memory_utils.c src\ui\exit.c src\ui\error_message.c src\ui\user_guide.c src\ui\menu_new.c src\utils\util.c src\core\position_exchange.c src\game\pawn_promotion.c src\game\king_moves.c -o chess_english.exe
IF %ERRORLEVEL% NEQ 0 (
    echo Compilation failed! See errors above.
) ELSE (
    echo English version built successfully: chess_english.exe
)
goto end

:build_hungarian
echo Building Hungarian version...
echo Executing: %GCC_CMD% -Isrc\include src\ui\main.c src\core\chess_constants.c src\game\jatszma.c src\game\babu_lepesek.c src\validation\lepes_ellenorzo.c src\validation\sakk_ellenorzo.c src\game\jatszma_lepesek.c src\validation\konvertalasok.c src\utils\mentes_beolvas.c src\ui\kilepes.c src\ui\hibauzenet.c src\ui\hasznalati_utmutato.c src\ui\menu.c src\utils\util.c -o chess_hungarian.exe
%GCC_CMD% -Isrc\include src\ui\main.c src\core\chess_constants.c src\game\jatszma.c src\game\babu_lepesek.c src\validation\lepes_ellenorzo.c src\validation\sakk_ellenorzo.c src\game\jatszma_lepesek.c src\validation\konvertalasok.c src\utils\mentes_beolvas.c src\ui\kilepes.c src\ui\hibauzenet.c src\ui\hasznalati_utmutato.c src\ui\menu.c src\utils\util.c -o chess_hungarian.exe
IF %ERRORLEVEL% NEQ 0 (
    echo Compilation failed! See errors above.
) ELSE (
    echo Hungarian version built successfully: chess_hungarian.exe
)
goto end

:build_both
echo Building both versions...
echo Building English version...
%GCC_CMD% -Isrc\include src\ui\main_english.c src\utils\globals.c src\core\chess_constants.c src\core\board_setup.c src\game\game.c src\game\piece_moves.c src\validation\move_validator.c src\validation\check_validator.c src\game\game_moves.c src\validation\conversions.c src\utils\save_load.c src\utils\memory_utils.c src\ui\exit.c src\ui\error_message.c src\ui\user_guide.c src\ui\menu_new.c src\utils\util.c src\core\position_exchange.c src\game\pawn_promotion.c src\game\king_moves.c -o chess_english.exe
IF %ERRORLEVEL% NEQ 0 (
    echo English version compilation failed! See errors above.
) ELSE (
    echo English version built successfully: chess_english.exe
)

echo Building Hungarian version...
%GCC_CMD% -Isrc\include src\ui\main.c src\core\chess_constants.c src\game\jatszma.c src\game\babu_lepesek.c src\validation\lepes_ellenorzo.c src\validation\sakk_ellenorzo.c src\game\jatszma_lepesek.c src\validation\konvertalasok.c src\utils\mentes_beolvas.c src\ui\kilepes.c src\ui\hibauzenet.c src\ui\hasznalati_utmutato.c src\ui\menu.c src\utils\util.c -o chess_hungarian.exe
IF %ERRORLEVEL% NEQ 0 (
    echo Hungarian version compilation failed! See errors above.
) ELSE (
    echo Hungarian version built successfully: chess_hungarian.exe
)
goto end

:end
echo.
pause
