// filepath: d:\Prog\C_Console_Chess\globals.c
#include <stddef.h>  // For NULL
#include "square.h"
#include "move.h"

// Define the global chess board
Square board[8][8];

// Define king pointers
Square* white_king;
Square* black_king;

// Define the current move
Move* current_move = NULL;
