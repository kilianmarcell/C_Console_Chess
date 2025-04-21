#include <stdio.h>
#include <stdlib.h>
#include "square.h"
#include "move.h"
#include "move_validator.h"
#include "check_validator.h" // Ensure this is included for can_opponent_move
#include "pawn_promotion.h"
#include "memory_utils.h" // Ensure this is included for create_move
#include "chess_constants.h"
#include "game.h" // Include for access to board, kings, current_move

// Make board, kings, and current_move accessible
extern Square board[8][8];
extern Move *current_move;
extern Square* white_king;
extern Square* black_king;


/**
 * Exchanges the positions of two squares on the board - making a move
 * 
 * @param from Source square
 * @param to Destination square
 * @param color Color of the moving piece
 * @return 0 if successful, 3 if invalid move, 4 if checkmate
 */
int exchange_positions(Square* from, Square* to, char color) {
    // Debug information
    printf("Debug: Moving from (%d,%d) to (%d,%d) - piece: %c color: %c\n", 
           from->x, from->y, to->x, to->y, from->piece, from->color);
           
    // Validate that the piece belongs to the current player
    if (from->piece == '-' || from->color != color) {
        printf("Debug: Invalid piece or color\n");
        return 3; // Invalid: No piece or wrong color
    }

    // If destination contains a piece of the same color, invalid move
    if (to->color == color) {
        printf("Debug: Cannot capture own piece\n");
        return 3; // Invalid: Cannot capture own piece
    }
    
    // Validate the move according to piece movement rules
    int move_status = validate_move(from, to, color);
    printf("Debug: validate_move status: %d\n", move_status);

    if (move_status == 0) {
        printf("Debug: Basic move validation failed\n");
        return 3; // Invalid move based on piece rules
    }
    // Valid move continues - move_status is either 1 (normal move) or 2 (special case like promotion)

    // --- Simulate the move ---
    char captured_piece = to->piece;
    char captured_color = to->color;
    char original_from_piece = from->piece; // Store original piece for potential revert
    char original_from_color = from->color; // Store original color for potential revert

    // Update 'to' square
    to->piece = from->piece;
    to->color = from->color;

    // Clear 'from' square
    from->piece = '-';
    from->color = '-';

    // Update king pointers if a king moved
    Square* original_king_ptr = NULL;
    if (to->piece == PIECE_LETTERS[KING]) {
        if (to->color == WHITE) {
            original_king_ptr = white_king; // Store original pointer
            white_king = to;
        } else {
            original_king_ptr = black_king; // Store original pointer
            black_king = to;
        }
    }

    // --- Check for self-check ---
    int check_result = validate_check(white_king, black_king);
    int self_check = (color == WHITE && check_result == 1) || (color == BLACK && check_result == 2);

    if (self_check) {
        // printf("Debug: Self-check detected, reverting move\n"); // Debug
        // Revert the move
        from->piece = original_from_piece; // Use stored original piece
        from->color = original_from_color; // Use stored original color
        to->piece = captured_piece;
        to->color = captured_color;

        // Revert king pointer if it was updated
        if (to->piece == PIECE_LETTERS[KING]) {
             if (to->color == WHITE) {
                 white_king = original_king_ptr;
             } else {
                 black_king = original_king_ptr;
             }
        }
        return 3; // Invalid move because it results in check
    }

    // --- Move is valid, finalize it ---

    // Add move to history
    // Pass necessary arguments to create_move
    Move* new_move = create_move(from->x, from->y, to->x, to->y, captured_piece, captured_color, current_move);
    if (!new_move) {
        // Handle allocation failure - potentially revert move and return error
        // Revert the move (simplified - consider a dedicated revert function)
        from->piece = original_from_piece;
        from->color = original_from_color;
        to->piece = captured_piece;
        to->color = captured_color;
        if (to->piece == PIECE_LETTERS[KING]) { // Revert king pointer
             if (to->color == WHITE) white_king = original_king_ptr;
             else black_king = original_king_ptr;
        }
        printf("Error: Failed to allocate memory for move history!\n");
        return 3; // Indicate failure
    }

    new_move->from_x = from->x;
    new_move->from_y = from->y;
    new_move->to_x = to->x;
    new_move->to_y = to->y;
    new_move->captured_piece = captured_piece;
    new_move->captured_color = captured_color;
    new_move->previous = current_move; // Link to previous move
    current_move = new_move;          // Update current move pointer

    // Handle pawn promotion
    if (move_status == 2) {
        promote_pawn(to); // Call promotion function from pawn_promotion.c
        // Update move history if promotion changed the piece? (Optional)
        // current_move->promoted_to = to->piece; // Example if Move struct supports it
    }

    // --- Check for checkmate on opponent ---
    // Check if the opponent is now in check
    check_result = validate_check(white_king, black_king);
    char opponent_color = (color == WHITE) ? BLACK : WHITE;
    int opponent_in_check = (opponent_color == WHITE && check_result == 1) || (opponent_color == BLACK && check_result == 2);

    if (opponent_in_check) {
        // Check if the opponent has any valid moves to escape check (checkmate)
        // Assuming can_opponent_move is declared in check_validator.h
        if (!can_opponent_move(opponent_color)) {
             // printf("Debug: Checkmate detected!\n"); // Corrected string literal
             return 4; // Checkmate
        }
        // Opponent is in check, but not checkmate (handled in game loop)
    }


    // printf("Debug: Move successful\n"); // Debug
    return 0; // Move successful
}
