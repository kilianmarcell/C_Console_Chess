#include "square.h"
#include "chess_constants.h"

/**
 * Initializes the chess board with starting positions
 * Sets up all pieces in their standard starting positions
 */
void load_board() {
     // Initialize the board with empty squares
     for(int i = 0; i < 8; i++) {
          for(int j = 0; j < 8; j++) {
               board[i][j].x = i;
               board[i][j].y = j;
               board[i][j].piece = '-';
               board[i][j].color = '-';
               
               // Set black pawns on row 1
               if (i == 1) {
                    board[i][j].piece = PIECE_LETTERS[PAWN];
                    board[i][j].color = BLACK;
               }
               
               // Set white pawns on row 6
               if (i == 6) {
                    board[i][j].piece = PIECE_LETTERS[PAWN];
                    board[i][j].color = WHITE;
               }
          }
     }
     
     // Set up black pieces (non-pawns) in back row
     board[0][0].piece = PIECE_LETTERS[ROOK];
     board[0][1].piece = PIECE_LETTERS[KNIGHT];
     board[0][2].piece = PIECE_LETTERS[BISHOP];
     board[0][3].piece = PIECE_LETTERS[QUEEN];
     board[0][4].piece = PIECE_LETTERS[KING];
     board[0][5].piece = PIECE_LETTERS[BISHOP];
     board[0][6].piece = PIECE_LETTERS[KNIGHT];
     board[0][7].piece = PIECE_LETTERS[ROOK];
     
     // Set up white pieces (non-pawns) in back row
     board[7][0].piece = PIECE_LETTERS[ROOK];
     board[7][1].piece = PIECE_LETTERS[KNIGHT];
     board[7][2].piece = PIECE_LETTERS[BISHOP];
     board[7][3].piece = PIECE_LETTERS[QUEEN];
     board[7][4].piece = PIECE_LETTERS[KING];
     board[7][5].piece = PIECE_LETTERS[BISHOP];
     board[7][6].piece = PIECE_LETTERS[KNIGHT];
     board[7][7].piece = PIECE_LETTERS[ROOK];
     
     // Set piece colors for the back rows
     for(int i = 0; i < 8; i++) {
          board[0][i].color = BLACK;
          board[7][i].color = WHITE;
     }

     white_king = &board[7][4];
     black_king = &board[0][4];
}
