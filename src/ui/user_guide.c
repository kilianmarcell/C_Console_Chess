#include <stdio.h>
#include "user_guide.h"
#include "menu.h"
#include "util.h"

/**
 * Displays usage instructions for the chess program
 * 
 * @param navigate Pointer to navigation variable for menu handling
 */
void show_user_guide(int* navigate) {
    printf("CHESS - USER GUIDE\n\n");
    printf("How to play:\n");
    printf("1. Enter moves in algebraic notation, e.g., 'e2 e4' to move from e2 to e4\n");
    printf("2. White moves first, then players alternate turns\n");
    printf("3. Capture pieces by moving your piece to an opponent's square\n");
    printf("4. When a pawn reaches the opposite end of the board, it can be promoted\n");
    printf("5. The game ends when a king is in checkmate (cannot escape check)\n\n");
    
    printf("Special commands during game:\n");
    printf("- Type '1' to save the current game\n");
    printf("- Type '2' to take back your last move\n");
    printf("- Type '9' to exit to main menu\n\n");
    
    printf("Press Enter to return to the main menu...");
    getchar();
    getchar();  // Wait for Enter key
    
    clear_screen();
    menu(navigate);
}
