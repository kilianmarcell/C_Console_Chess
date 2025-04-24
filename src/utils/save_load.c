#include "game_moves.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save_load.h"
#include "move.h"
#include "game.h" // for process_move_input declaration
#include "chess_constants.h"
#include "square.h"
#include "menu.h"
#include "error_message.h"
#include "move_validator.h"
#include "memory_utils.h"
#include "pawn_promotion.h"
#include "conversions.h"

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
void list_test_files() {
    printf("\nAvailable test files:\n");
    // Use OS command to list files in the tests directory
#if defined(_WIN32) || defined(_WIN64)
    system("dir tests\\*.txt /b > test_files_list.tmp");
#else
    system("ls -1 tests/*.txt > test_files_list.tmp");
#endif
    // Now open the file for reading only
    FILE* temp_file = fopen("test_files_list.tmp", "r");
    if (temp_file == NULL) {
        printf("Error listing test files.\n");
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line), temp_file)) {
        // Remove newline if present
        line[strcspn(line, "\n")] = 0;
        printf("- %s\n", line);
    }
    fclose(temp_file);
    remove("test_files_list.tmp");
    printf("\n");
}

void load_game(int* navigate) {
    char filename[100];
    char test_filename[120]; // Longer to accommodate full path
    
    // Show available test files
    list_test_files();
    
    printf("Enter filename to load: ");
    scanf("%s", filename);
    
    FILE* load_file = fopen(filename, "r");
    
    // If file not found in current directory, try in tests folder
    if (load_file == NULL) {
        sprintf(test_filename, "tests/%s", filename);
        load_file = fopen(test_filename, "r");
    }
    
    if (load_file == NULL) {
        display_error("Could not open save file");
        menu(navigate);
        return;
    }    load_board();  // Reset the board to starting position
    display_current_board(&board[0][0]);  // Show the initial board state
    printf("Initial board position\n\n");
    
    char move_notation[6];
    int move_count = 1;
    char player = WHITE;
    int is_test_file = strstr(filename, "test_") != NULL || strstr(test_filename, "test_") != NULL;
    
    while (fgets(move_notation, sizeof(move_notation), load_file)) {
        // Remove newline and carriage return if present
        move_notation[strcspn(move_notation, "\n")] = 0;
        move_notation[strcspn(move_notation, "\r")] = 0;
        // Skip empty lines
        if (strlen(move_notation) == 0) {
            continue;
        }
        // Debug output
        printf("Move %d: '%s'\n", move_count++, move_notation);
        int move_result = process_move_input(move_notation, player);
        if (move_result != 1) {
            display_error("Invalid move in save file");
            printf("Failed move: '%s'\n", move_notation);
            fclose(load_file);
            menu(navigate);
            return;
        }
        // Switch player after a successful move
        player = (player == WHITE) ? BLACK : WHITE;
        if (is_test_file) {
            display_current_board(&board[0][0]);
            printf("After move: %s\n\n", move_notation);
        }
    }
    
    fclose(load_file);
    display_current_board(&board[0][0]); // Show the board after loading all moves
    // Always continue gameplay after loading, regardless of file type
    make_move("-", 1);  // Continue the game
    // Do not call menu(navigate) here; let make_move handle returning to menu
    return;
}
