#ifndef CHESS_CONSTANTS_H_INCLUDED
#define CHESS_CONSTANTS_H_INCLUDED

/**
 * Chess piece types
 */
typedef enum {
    KING = 0,
    QUEEN = 1,
    ROOK = 2,
    BISHOP = 3,
    KNIGHT = 4,
    PAWN = 5
} PieceType;

/**
 * Chess piece colors
 */
typedef enum {
    WHITE = 'w',
    BLACK = 'b'
} PieceColor;

/**
 * Chess board columns
 */
extern char COLUMNS[];

/**
 * Chess piece letter representations
 */
extern char PIECE_LETTERS[];

/**
 * Unicode chess piece symbols (first 6 white, next 6 black)
 */
extern char *PIECE_SYMBOLS[];

#endif // CHESS_CONSTANTS_H_INCLUDED
