#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "square.h"
#include "move.h"

extern Square board[8][8];
extern Move *current_move;

void new_game(int* navigate);
int count_moves(Move* m, int total);
int make_move(char* load_move, int load_complete);
void load_board();

#endif
