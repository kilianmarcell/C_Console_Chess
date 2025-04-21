#include <stdio.h>
#include <ctype.h>
#include "square.h"
#include "chess_constants.h"

/**
 * Handles pawn promotion when a pawn reaches the opposite end of the board
 * 
 * @param s Pointer to the square containing the pawn to be promoted
 */
void promote_pawn(Square* s) {
    char choice;
    int valid_input = 0;
    
    printf("Promote pawn to (Q)ueen, (R)ook, (B)ishop, or k(N)ight: ");
    
    while (!valid_input) {
        scanf(" %c", &choice);
        choice = tolower(choice);
        
        // Convert the input to the appropriate piece type
        switch(choice) {
            case 'q': 
                s->piece = PIECE_LETTERS[QUEEN];
                valid_input = 1;
                break;
            case 'r': 
                s->piece = PIECE_LETTERS[ROOK];
                valid_input = 1;
                break;
            case 'b': 
                s->piece = PIECE_LETTERS[BISHOP];
                valid_input = 1;
                break;
            case 'n': 
                s->piece = PIECE_LETTERS[KNIGHT];
                valid_input = 1;
                break;
            default:
                printf("Invalid choice. Please select Q, R, B, or N: ");
        }
    }
}
