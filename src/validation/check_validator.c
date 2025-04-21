#include <stdio.h>
#include <stdlib.h>
#include "square.h"
#include "piece_moves.h"
#include "chess_constants.h"
#include "check_validator.h"
#include "move_validator.h"

extern Square board[8][8];
extern Square* white_king;
extern Square* black_king;

/**
 * Validates if either king is in check
 * 
 * @param white Pointer to the white king square
 * @param black Pointer to the black king square
 * @return 0 if no check, 1 if white king in check, 2 if black king in check
 */
int validate_check(Square* white, Square* black) {
    // Check if white king is in check
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // If a black piece can move to white king's position
            if (board[i][j].color == BLACK && 
                validate_move(&board[i][j], white, BLACK)) {
                return 1; // White king is in check
            }
        }
    }
    
    // Check if black king is in check
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // If a white piece can move to black king's position
            if (board[i][j].color == WHITE && 
                validate_move(&board[i][j], black, WHITE)) {
                return 2; // Black king is in check
            }
        }
    }
    
    return 0; // No king in check
}

/**
 * Checks if the player of the specified color has any valid moves.
 * Iterates through all pieces of the given color and checks if any valid move exists
 * that does not result in the player's own king being in check.
 *
 * @param color The color of the player to check.
 * @return 1 if the player has at least one valid move, 0 otherwise.
 */
int can_opponent_move(char color) {
    Square* current_king = (color == WHITE) ? white_king : black_king;
    Square* opponent_king = (color == WHITE) ? black_king : white_king; // Needed for validate_check

    for (int r_from = 0; r_from < 8; r_from++) {
        for (int c_from = 0; c_from < 8; c_from++) {
            Square* from_square = &board[r_from][c_from];

            // Check only pieces of the specified color
            if (from_square->piece != '-' && from_square->color == color) {
                // Iterate through all possible destination squares
                for (int r_to = 0; r_to < 8; r_to++) {
                    for (int c_to = 0; c_to < 8; c_to++) {
                        Square* to_square = &board[r_to][c_to];

                        // Check if the basic move is valid (ignores self-check for now)
                        int move_status = validate_move(from_square, to_square, color);

                        if (move_status != 0) { // 0 means invalid basic move
                            // --- Simulate the move --- 
                            char original_to_piece = to_square->piece;
                            char original_to_color = to_square->color;
                            char original_from_piece = from_square->piece;
                            char original_from_color = from_square->color;
                            Square* original_king_ptr = NULL;

                            // Perform the move
                            to_square->piece = from_square->piece;
                            to_square->color = from_square->color;
                            from_square->piece = '-';
                            from_square->color = '-';

                            // Update king pointer if king moved
                            int king_moved = 0;
                            if (to_square->piece == PIECE_LETTERS[KING]) {
                                king_moved = 1;
                                if (color == WHITE) {
                                    original_king_ptr = white_king;
                                    white_king = to_square;
                                } else {
                                    original_king_ptr = black_king;
                                    black_king = to_square;
                                }
                                current_king = to_square; // Update local pointer too
                            }

                            // --- Check for self-check --- 
                            int check_result = validate_check(white_king, black_king);
                            int self_check = (color == WHITE && check_result == 1) || (color == BLACK && check_result == 2);

                            // --- Revert the move --- 
                            from_square->piece = original_from_piece;
                            from_square->color = original_from_color;
                            to_square->piece = original_to_piece;
                            to_square->color = original_to_color;

                            // Revert king pointer if it was updated
                            if (king_moved) {
                                if (color == WHITE) {
                                    white_king = original_king_ptr;
                                } else {
                                    black_king = original_king_ptr;
                                }
                                // No need to revert current_king local pointer, it's reset on next outer loop iteration
                            }

                            // If the move was valid and did NOT result in self-check, opponent can move
                            if (!self_check) {
                                return 1; // Found a valid move
                            }
                        }
                    }
                }
            }
        }
    }

    // If no valid moves were found after checking all pieces
    return 0; // Opponent cannot move (checkmate or stalemate)
}
