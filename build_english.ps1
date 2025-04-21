# Build script for the English version of the chess program

# Define source directories
$CORE_DIR = "src\core"
$GAME_DIR = "src\game"
$UI_DIR = "src\ui"
$UTILS_DIR = "src\utils"
$VALIDATION_DIR = "src\validation"
$INCLUDE_DIR = "src\include"
$BUILD_DIR = "build\english"

# Ensure build directory exists
if (-not (Test-Path -Path $BUILD_DIR)) {
    New-Item -ItemType Directory -Path $BUILD_DIR -Force | Out-Null
}

# Define compilation command
$GCC_COMMAND = "gcc"

# Define include path
$INCLUDE_FLAG = "-I$INCLUDE_DIR"

# Define source files
$SOURCE_FILES = @(
    "$UI_DIR\main_english.c",
    "$CORE_DIR\chess_constants.c",
    "$CORE_DIR\board_setup.c",
    "$GAME_DIR\game.c",
    "$GAME_DIR\piece_moves.c",
    "$VALIDATION_DIR\move_validator.c",
    "$VALIDATION_DIR\check_validator.c",
    "$GAME_DIR\game_moves.c",
    "$VALIDATION_DIR\conversions.c",
    "$UTILS_DIR\save_load.c",
    "$UTILS_DIR\memory_utils.c",
    "$UI_DIR\exit.c",
    "$UI_DIR\error_message.c",
    "$UI_DIR\user_guide.c",
    "$UI_DIR\menu_new.c",
    "$UTILS_DIR\util.c",
    "$CORE_DIR\position_exchange.c",
    "$GAME_DIR\pawn_promotion.c",
    "$GAME_DIR\king_moves.c",
    "$UTILS_DIR\globals.c"
)

# Define output executable
$OUTPUT = "$BUILD_DIR\chess_english.exe"

# Build command
$BUILD_CMD = "$GCC_COMMAND $INCLUDE_FLAG $($SOURCE_FILES -join " ") -o $OUTPUT"

Write-Host "Building English chess program..."
Write-Host "Command: $BUILD_CMD"

# Execute the build command
Invoke-Expression $BUILD_CMD

# Check if build was successful
if ($LASTEXITCODE -eq 0) {
    Write-Host "Build successful! Executable created at: $OUTPUT"
} else {
    Write-Host "Build failed with error code: $LASTEXITCODE"
}
