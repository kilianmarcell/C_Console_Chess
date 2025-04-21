#include <stdio.h>
#include <stdlib.h>
#include "square.h"
#include "move.h"
#include "conversions.h"
#include "piece_moves.h"
#include "check_validator.h"
#include "move_validator.h"
#include "menu.h"
#include "chess_constants.h"
#include "memory_utils.h"
#include "debugmalloc.h"

void menu(int* navigate);
void load_game(int* navigate);
void display_error(char *message);
int letter_to_number(char c);

/**
 * Global variables
 */
Square board[8][8];     // The chess board
Square* white_king;     // Pointer to the white king
Square* black_king;     // Pointer to the black king

Move *current_move = NULL;

int main(void) {
    int navigate = 0;
    menu(&navigate);
    return 0;
}
