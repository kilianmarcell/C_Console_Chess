#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save_load.h"
#include "move.h"
#include "game.h"
#include "chess_constants.h"
#include "square.h"
#include "menu.h"
#include "error_message.h"

extern Square board[8][8];
extern Move *current_move;
extern char COLUMNS[];

/**
 * Saves the current game state to a file
 */
void save_game() {
    char filename[100];
    printf("Enter filename to save: ");
    scanf("%s", filename);
    
    FILE* save_file = fopen(filename, "w");
    if (save_file == NULL) {
        display_error("Could not create save file");
        return;
    }
    
    write_to_file(save_file, current_move);
    fclose(save_file);
    
    printf("Game saved successfully!\n");
}

/**
 * Helper function to write move data to the save file
 * 
 * @param save_file File pointer to write to
 * @param move Current move to write
 */
void write_to_file(FILE* save_file, Move* move) {
    if (move == NULL) {
        return;
    }
    
    write_to_file(save_file, move->previous);
    fprintf(save_file, "%c%d %c%d\n", 
            COLUMNS[move->from_y], 8 - move->from_x,
            COLUMNS[move->to_y], 8 - move->to_x);
}

/**
 * Loads a previously saved game from a file
 * 
 * @param navigate Pointer to navigation variable for menu handling
 */
void load_game(int* navigate) {
    char filename[100];
    printf("Enter filename to load: ");
    scanf("%s", filename);
    
    FILE* load_file = fopen(filename, "r");
    if (load_file == NULL) {
        display_error("Could not open save file");
        menu(navigate);
        return;
    }
    
    load_board();  // Reset the board to starting position
    
    char move_notation[6];
    while (fgets(move_notation, sizeof(move_notation), load_file)) {
        // Remove newline if present
        move_notation[strcspn(move_notation, "\n")] = 0;
        
        if (make_move(move_notation, 0) == 0) {
            display_error("Invalid move in save file");
            fclose(load_file);
            menu(navigate);
            return;
        }
    }
    
    fclose(load_file);
    make_move("-", 1);  // Continue the game
    menu(navigate);
}
