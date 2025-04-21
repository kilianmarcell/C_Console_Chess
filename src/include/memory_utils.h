#ifndef MEMORY_UTILS_H_INCLUDED
#define MEMORY_UTILS_H_INCLUDED

#include "move.h"

/**
 * Allocates memory for a new move and initializes it with the provided data
 * 
 * @param from_x Source X coordinate
 * @param from_y Source Y coordinate
 * @param to_x Destination X coordinate
 * @param to_y Destination Y coordinate
 * @param captured_color Color of captured piece (if any)
 * @param captured_piece Type of captured piece (if any)
 * @param previous Pointer to the previous move in the linked list
 * @return Pointer to the newly created move, or NULL if allocation failed
 */
Move* create_move(int from_x, int from_y, int to_x, int to_y, 
                  char captured_color, char captured_piece, Move* previous);

/**
 * Frees all moves in the linked list starting from the given move
 * 
 * @param m Pointer to the first move to free
 */
void free_all_moves(Move* m);

/**
 * Frees a single move from memory
 * 
 * @param m Pointer to the move to free
 */
void free_move(Move* m);

#endif // MEMORY_UTILS_H_INCLUDED
