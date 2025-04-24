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
// Add this prototype to make process_move_input available to other files
int process_move_input(char* input, char player);

#endif
