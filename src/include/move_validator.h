#ifndef MOVE_VALIDATOR_H_INCLUDED
#define MOVE_VALIDATOR_H_INCLUDED

#include "square.h"

int validate_move(Square* from, Square* to, char color);
void promote_pawn(Square* s);
int can_king_move(Square* s);
int exchange_positions(Square* from, Square* to, char color);

#endif // MOVE_VALIDATOR_H_INCLUDED
