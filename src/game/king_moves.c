#include <ctype.h>
#include "move_validator.h"
#include "square.h"

/**
 * Checks if the king can make any legal move
 * Used for determining checkmate
 * 
 * @param s Pointer to the king's square
 * @return 1 if king can move, 0 if king cannot move
 */
int can_king_move(Square* s) {
    // Check all 8 possible king moves
    int dx[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int dy[8] = {-1,  0,  1, -1, 1, -1, 0, 1};
    
    for (int i = 0; i < 8; i++) {
        int new_x = s->x + dx[i];
        int new_y = s->y + dy[i];
        
        // Check if the position is on the board
        if (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8) {
            // Check if the king can move to this position
            if (board[new_x][new_y].color != s->color) {
                // TODO: Need to verify move doesn't put king in check
                // For a complete implementation, this would call validate_check
                // to ensure the king isn't moving into check
                return 1;
            }
        }
    }
    
    return 0;
}
