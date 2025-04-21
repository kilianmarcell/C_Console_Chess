#ifndef PIECE_MOVES_H_INCLUDED
#define PIECE_MOVES_H_INCLUDED

#include "square.h"

int knight_move(Square* current, Square* destination);
int king_move(Square* current, Square* destination);
int up_right_move(Square* current, Square* destination);
int down_right_move(Square* current, Square* destination);
int up_left_move(Square* current, Square* destination);
int down_left_move(Square* current, Square* destination);
int is_diagonal_valid(Square* from, Square* to);
int straight_up_move(Square* current, Square* destination);
int straight_down_move(Square* current, Square* destination);
int straight_left_move(Square* current, Square* destination);
int straight_right_move(Square* current, Square* destination);
int is_straight_valid(Square* from, Square* to);

#endif
