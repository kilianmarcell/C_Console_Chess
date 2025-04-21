#ifndef CHECK_VALIDATOR_H_INCLUDED
#define CHECK_VALIDATOR_H_INCLUDED

#include "square.h"

int validate_check(Square* white, Square* black);
int can_move_to_helper(Square* s, char color);

/**
 * Checks if the player of the specified color has any valid moves.
 * 
 * @param color The color of the player to check.
 * @return 1 if the player has at least one valid move, 0 otherwise.
 */
int can_opponent_move(char color);

#endif // CHECK_VALIDATOR_H
