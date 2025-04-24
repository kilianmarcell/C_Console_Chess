#include <stdio.h>
#include <stdlib.h>
#include "square.h"
#include "move.h"
#include "piece_moves.h"
#include "conversions.h"
#include "check_validator.h"
#include "chess_constants.h"
#include "memory_utils.h"

extern Square board[8][8];
extern Move *current_move;
extern Square* white_king;
extern Square* black_king;

/**
 * Validates if a move is legal for the given piece
 * 
 * @param from Source square (from position)
 * @param to Destination square (to position)
 * @param color Color of the moving piece ('w' for white, 'b' for black)
 * @return 1 if move is valid, 0 if invalid, 2 for special cases like pawn promotion
 */
int validate_move(Square* from, Square* to, char color) {
     // Determine opponent's color
     char opponent_color = (color == WHITE) ? BLACK : WHITE;
     
     // Knight move validation
     if (from->piece == PIECE_LETTERS[KNIGHT]) {
          return knight_move(from, to) ? 1 : 0;
     }

     // Bishop move validation
     if (from->piece == PIECE_LETTERS[BISHOP]) {
          return is_diagonal_valid(from, to) ? 1 : 0;
     }     // Pawn move validation
     if (from->piece == PIECE_LETTERS[PAWN]) {
          if (from->color == WHITE) {
               if (from->y == to->y) {
                    // Single step forward
                    if (from->x - 1 == to->x && to->piece == '-') {
                         if (to->x == 0) {
                              return 2; // Pawn reached the opponent's back rank (promotion)
                         }
                         return 1; // Valid forward move
                    }
                    // Double move from starting position
                    if (from->x == 6 && to->x == 4 && to->piece == '-' && 
                        board[5][from->y].piece == '-') {
                         return 1;
                    }
               } 
               // Regular capture move
               else if ((from->y == to->y - 1 || from->y == to->y + 1) && 
                      from->x - 1 == to->x && to->color == BLACK) {
                    if (to->x == 0) {
                         return 2; // Pawn reached the opponent's back rank (promotion)
                    }
                    return 1;
               }
               // En passant capture (for White)
               else if (from->x == 3 && to->x == 2 && 
                       (from->y == to->y - 1 || from->y == to->y + 1) &&
                       to->piece == '-' && 
                       current_move != NULL && 
                       current_move->to_x == 3 && 
                       current_move->from_x == 1 &&
                       current_move->to_y == to->y &&
                       board[3][to->y].piece == PIECE_LETTERS[PAWN] &&
                       board[3][to->y].color == BLACK) {
                    printf("Debug: En passant capture by white detected!\n");
                    // Remove the captured pawn
                    board[3][to->y].piece = '-';
                    board[3][to->y].color = '-';
                    return 1;
               }
          }
          // Black pawn moves
          else {
               if (from->y == to->y) {
                    if (from->x + 1 == to->x && to->piece == '-') {
                         if (to->x == 7) {
                              return 2; // Pawn reached the opponent's back rank (promotion)
                         }
                         return 1;
                    }
                      // Double move from starting position
                    if (from->x == 1 && to->x == 3 && to->piece == '-' && 
                        board[2][from->y].piece == '-') {
                         return 1;
                    }
               } 
               // Regular capture move
               else if ((from->y == to->y - 1 || from->y == to->y + 1) && 
                      from->x + 1 == to->x && to->color == WHITE) {
                    if (to->x == 7) {
                         return 2; // Pawn reached the opponent's back rank (promotion)
                    }
                    return 1;
               }
               // En passant capture (for Black)
               else if (from->x == 4 && to->x == 5 && 
                       (from->y == to->y - 1 || from->y == to->y + 1) &&
                       to->piece == '-' &&
                       current_move != NULL && 
                       current_move->to_x == 4 && 
                       current_move->from_x == 6 &&
                       current_move->to_y == to->y &&
                       board[4][to->y].piece == PIECE_LETTERS[PAWN] &&
                       board[4][to->y].color == WHITE) {
                    printf("Debug: En passant capture by black detected!\n");
                    // Remove the captured pawn
                    board[4][to->y].piece = '-';
                    board[4][to->y].color = '-';
                    return 1;
               }
          }
          return 0;
     }

     // Rook move validation
     if (from->piece == PIECE_LETTERS[ROOK]) {
          return is_straight_valid(from, to) ? 1 : 0;
     }

     // Queen move validation (can move diagonally or straight)
     if (from->piece == PIECE_LETTERS[QUEEN]) {
          if (is_diagonal_valid(from, to) || is_straight_valid(from, to)) {
               return 1;
          }
          return 0;
     }

     // King move validation
     if (from->piece == PIECE_LETTERS[KING]) {
          return king_move(from, to) ? 1 : 0;
     }

     return 0;
}
