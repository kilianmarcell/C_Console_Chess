#include <stdio.h>
#include <stdlib.h>
#include "square.h"
#include "move.h"
#include "conversions.h"
#include "game.h"
#include "chess_constants.h"

extern Square board[8][8];
extern Move *current_move;
extern Square* white_king;
extern Square* black_king;

// Helper function declarations
static void print_board_header(void);
static void print_board_row(int row);
static void print_board_separator(void);
static void print_board_bottom(void);
static void print_piece(Square* square);
static int get_piece_index(char piece, char color);
void show_board(void);

/**
 * Recursively prints the last few moves in the game history
 */
void print_previous_moves(Move* m, int count) {
    if (m == NULL) return;
    
    if (count < 5) {
        print_previous_moves(m->previous, count + 1);
        printf("%c%d->%c%d   ", 
               COLUMNS[m->from_y], 8 - m->from_x, 
               COLUMNS[m->to_y], 8 - m->to_x);
    }
}

/**
 * Displays the current board state and move history
 */
void display_current_board(Square* s) {
    if (count_moves(current_move, 0) > 0) {
        printf("Last 5 moves:   ");
        print_previous_moves(current_move, 0);
        printf("\n\n");
    }
    
    show_board();
}

/**
 * Displays the chess board with all pieces
 */
void show_board() {
    print_board_header();
    print_board_separator();
    
    for (int i = 0; i < 8; i++) {
        print_board_row(i);
        if (i < 7) print_board_separator();
    }
    
    print_board_bottom();
}

/**
 * Prints the column headers (A-H)
 */
static void print_board_header(void) {
    printf("    ");
    for (int i = 0; i < 8; i++) {
        printf("%c   ", COLUMNS[i]);
    }
    printf("\n");
}

/**
 * Prints a single row of the chess board
 */
static void print_board_row(int row) {
    printf("%d |", 8 - row);
    
    for (int j = 0; j < 8; j++) {
        print_piece(&board[row][j]);
    }
    
    printf("\n");
}

/**
 * Prints a single chess piece
 */
static void print_piece(Square* square) {
    if (square->piece == '-') {
        printf("   |");
        return;
    }
    
    int piece_index = get_piece_index(square->piece, square->color);
    printf(" %s |", PIECE_SYMBOLS[piece_index]);
}

/**
 * Gets the index for a chess piece in the symbols array
 */
static int get_piece_index(char piece, char color) {
    for (int k = 0; k < 6; k++) {
        if (piece == PIECE_LETTERS[k]) {
            return (color == WHITE) ? k : k + 6;
        }
    }
    return 0;
}

/**
 * Prints horizontal separator between board rows
 */
static void print_board_separator(void) {
    printf("  +---+---+---+---+---+---+---+---+\n");
}

/**
 * Prints the bottom border of the chess board
 */
static void print_board_bottom(void) {
    printf("  +---+---+---+---+---+---+---+---+\n\n");
}
