#ifndef SAVE_LOAD_H_INCLUDED
#define SAVE_LOAD_H_INCLUDED

#include "move.h"

extern char COLUMNS[];
extern Move *current_move;

void save_game();
void write_to_file(FILE* save_file, Move* move);
void load_game(int* navigate);

#endif
