#include <stdlib.h>
#include "memory_utils.h"
#include "move.h"
#include "debugmalloc.h"

/**
 * Allocates memory for a new move and initializes it with the provided data
 */
Move* create_move(int from_x, int from_y, int to_x, int to_y, 
                  char captured_color, char captured_piece, Move* previous) {
    Move* new_move = (Move*)malloc(sizeof(Move));
    
    if (new_move == NULL) {
        return NULL;  // Memory allocation failed
    }
    
    new_move->from_x = from_x;
    new_move->from_y = from_y;
    new_move->to_x = to_x;
    new_move->to_y = to_y;
    new_move->captured_color = captured_color;
    new_move->captured_piece = captured_piece;
    new_move->previous = previous;
    
    return new_move;
}

/**
 * Frees all moves in the linked list starting from the given move
 */
void free_all_moves(Move* m) {
    Move* current = m;
    Move* next;
    
    while (current != NULL) {
        next = current->previous;
        free(current);
        current = next;
    }
}

/**
 * Frees a single move from memory
 */
void free_move(Move* m) {
    if (m != NULL) {
        free(m);
    }
}
