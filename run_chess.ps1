# PowerShell script to set up the terminal for Unicode chess pieces display
# and run the chess game

# Set the code page to UTF-8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

# Set the font to a Unicode-compatible font if possible (Consolas is usually good for Unicode)
# Note: This requires admin rights, so we'll just suggest it to the user

Write-Host "For best results, make sure your PowerShell terminal is using a font that supports Unicode chess pieces." -ForegroundColor Yellow
Write-Host "Recommended fonts: Consolas, DejaVu Sans Mono, or Cascadia Code." -ForegroundColor Yellow
Write-Host ""

# Display sample chess pieces to verify they're working
Write-Host "Testing chess piece display..."
Write-Host "Sample white pieces: ♔ ♕ ♖ ♗ ♘ ♙"
Write-Host "Sample black pieces: ♚ ♛ ♜ ♝ ♞ ♟"
Write-Host ""

$response = Read-Host "Do the chess pieces above display correctly? (y/n)"

if ($response.ToLower() -eq "y") {
    Write-Host "Great! Starting the chess game..." -ForegroundColor Green
    # Run the chess game
    & ".\chess_english.exe"
} else {
    Write-Host "Let's use ASCII fallback symbols instead." -ForegroundColor Yellow
    
    # Create a temporary file with ASCII symbols
    $content = @"
#include "chess_constants.h"

/**
 * Chess board columns
 */
char COLUMNS[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

/**
 * Chess piece letter representations
 */
char PIECE_LETTERS[] = { 'k', 'q', 'r', 'b', 'h', 'p' };

/**
 * ASCII chess piece symbols (first 6 white, next 6 black)
 * Using visually enhanced ASCII representations
 */
char *PIECE_SYMBOLS[] = { 
    "[K]", "[Q]", "[R]", "[B]", "[N]", "[P]",  /* White: King, Queen, Rook, Bishop, Knight, Pawn */
    "(k)", "(q)", "(r)", "(b)", "(n)", "(p)"   /* Black: King, Queen, Rook, Bishop, Knight, Pawn */
};
"@
    
    # Save to a temporary chess_constants file
    $content | Out-File -FilePath ".\chess_constants.c" -Encoding utf8
    
    # Rebuild the game
    Write-Host "Rebuilding chess with ASCII symbols..."
    & gcc main_english.c globals.c chess_constants.c board_setup.c game.c piece_moves.c move_validator.c check_validator.c game_moves.c conversions.c save_load.c memory_utils.c exit.c error_message.c user_guide.c menu_new.c util.c position_exchange.c pawn_promotion.c king_moves.c -o chess_english.exe
    
    # Run the chess game
    & ".\chess_english.exe"
}
