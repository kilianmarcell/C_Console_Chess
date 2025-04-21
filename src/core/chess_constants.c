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
 * Using visually appealing representations that work in all terminals
 */
char *PIECE_SYMBOLS[] = { 
    "♔", "♕", "♖", "♗", "♘", "♙",  /* White: King, Queen, Rook, Bishop, Knight, Pawn */
    "♚", "♛", "♜", "♝", "♞", "♟"   /* Black: King, Queen, Rook, Bishop, Knight, Pawn */
};
