#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "square.h"
#include "move.h"
#include "game.h"
#include "conversions.h"
#include "move_validator.h"
#include "game_moves.h"
#include "check_validator.h"
#include "menu.h"
#include "error_message.h"
#include "save_load.h"
#include "chess_constants.h"
#include "util.h"
#include "memory_utils.h"

// Function declarations for helper functions
static void switch_player(char* player);
static void handle_check_state(char* load_move, int* is_check);
static void display_player_prompt(char player);
static int get_player_input(char* input);
static void cleanup_moves(void);
void take_back_move(void);

/**
 * Starts a new chess game
 */
void new_game(int* navigate) {
    load_board();
    // Play the game until user exits
    make_move("-", 0);
    // Return to menu after game is finished
    menu(navigate);
}

/**
 * Counts and returns the number of moves made so far
 */
int count_moves(Move* m, int total) {
    if (m == NULL) return total;
    return count_moves(m->previous, total + 1);
}

/**
 * Executes one move in the chess game
 */
int make_move(char* load_move, int load_complete) {
    int action = 0, is_check = 0;
    char player = WHITE;  // Default to white player first
    char input[10] = {0};  // Increased buffer size to accommodate longer inputs
    int move_result;  // Declare move_result

    // Display the board if not loading saved moves
    if (strcmp(load_move, "-") == 0) 
        display_current_board(&board[0][0]);

    // Setup for loaded or ongoing game
    if (load_complete == 1) {
        if (count_moves(current_move, 0) % 2 == 1) 
            player = BLACK;
        
        if (validate_check(white_king, black_king) != 0) 
            is_check = 1;
    }
    
    if (strcmp(load_move, "-") != 0) {
        strcpy(input, load_move);
        if (count_moves(current_move, 0) % 2 == 1) 
            player = BLACK;
    }
    
    while(action != 9) {
        // Handle check state
        handle_check_state(load_move, &is_check);
        
        // Get player input
        if (strcmp(load_move, "-") == 0) {
            display_player_prompt(player);
            if (!get_player_input(input))
                continue;
        }
        
        // Reset action to 0 to ensure we don't accidentally exit the loop
        action = 0;
          // Process command or move
        int result = sscanf(input, "%d", &action);
        
        if (result == 1) {
            // Handle numeric commands
            if (action == 1) {
                save_game();
            } else if (action == 2) {
                // Take back move
                if (current_move != NULL) {
                    take_back_move();
                    switch_player(&player);
                    is_check = (validate_check(white_king, black_king) != 0);
                } else {
                    display_current_board(&board[0][0]);
                    printf("No moves to take back!\n\n");
                }
            }
        } else {            // Process chess move
            move_result = process_move_input(input, player);
            
            // Handle move result
            if (move_result == 1) {
                // For loaded moves, return immediately
                if (strcmp(load_move, "-") != 0) return 1;
                
                // For normal game play, update the board and switch players
                display_current_board(&board[0][0]); // Update the board after successful move
                switch_player(&player);
                
                // Clear input buffer for next move
                input[0] = '\0';
            } else if (move_result == 2) {
                // Game over (checkmate)
                return (strcmp(load_move, "-") != 0) ? 0 : 1;
            } else if (move_result == 3) {
                // Invalid move
                if (strcmp(load_move, "-") != 0) return 0;
                display_error("move");
                display_current_board(&board[0][0]); // Redraw board to avoid duplicate prompt
            }
        }
        
        // Exit condition for loaded moves
        if (strcmp(load_move, "-") != 0) return 0;
    }

    // Prompt to save before exit
    printf("Save game before exit? (y/n): ");
    char answer;
    scanf(" %c", &answer);
    if (answer == 'y' || answer == 'Y') save_game();

    // Cleanup
    cleanup_moves();
    
    return 1;
}

/**
 * Processes a move input and makes the move if valid
 */
int process_move_input(char* input, char player) {
    char from_col, to_col;
    int from_row, to_row, validate;
    // Make input lowercase to handle both uppercase and lowercase letters
    for (int i = 0; input[i]; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            input[i] = input[i] - 'A' + 'a';
        }
    }
    
    // More flexible input parsing - try different formats
    int result;
    
    // Try standard format with space "a2 a4"
    result = sscanf(input, "%c%d %c%d", &from_col, &from_row, &to_col, &to_row);
    
    // If that fails, try format without space "a2a4"
    if (result != 4) {
        result = sscanf(input, "%c%d%c%d", &from_col, &from_row, &to_col, &to_row);
    }
    
    if (result != 4) {
        printf("Debug: Invalid input format: %s\n", input);
        printf("Please use format 'a2 a4' or 'a2a4'\n");
        return 3; // Invalid input format
    }
    
    // Validate row numbers (1-8)
    if (from_row < 1 || from_row > 8 || to_row < 1 || to_row > 8) {
        printf("Debug: Invalid row coordinates\n");
        return 3; // Invalid coordinates
    }
      // Directly validate column letters using COLUMNS array
    int from_col_valid = 0, to_col_valid = 0;
    
    // Check if columns are valid chess notation (a-h)
    for (int i = 0; i < 8; i++) {
        if (from_col == COLUMNS[i]) from_col_valid = 1;
        if (to_col == COLUMNS[i]) to_col_valid = 1;
    }
    
    if (!from_col_valid || !to_col_valid) {
        printf("Debug: Invalid column coordinates\n");
        return 3; // Invalid coordinates
    }
      // Convert chess notation to array indices
    int from_col_idx = letter_to_number(&from_col);
    int to_col_idx = letter_to_number(&to_col);
    int from_row_idx = 8 - from_row;
    int to_row_idx = 8 - to_row;
    
    printf("Debug: From [%d,%d] to [%d,%d]\n", from_row_idx, from_col_idx, to_row_idx, to_col_idx);
    
    // Check array bounds for safety
    if (from_row_idx < 0 || from_row_idx > 7 || from_col_idx < 0 || from_col_idx > 7 ||
        to_row_idx < 0 || to_row_idx > 7 || to_col_idx < 0 || to_col_idx > 7) {
        printf("Debug: Array index out of bounds\n");
        return 3; // Invalid coordinates
    }
    
    printf("Debug: Source piece: %c, color: %c\n", board[from_row_idx][from_col_idx].piece, board[from_row_idx][from_col_idx].color);
    printf("Debug: Target piece: %c, color: %c\n", board[to_row_idx][to_col_idx].piece, board[to_row_idx][to_col_idx].color);
    
    // Execute the move
    validate = exchange_positions(
        &board[from_row_idx][from_col_idx],
        &board[to_row_idx][to_col_idx],
        player
    );
    
    if (validate == 0) {
        return 1; // Success - normal
    } else if (validate == 4) {
        printf("\nCheckmate!\n");
        printf("%s player wins!\n", (player == WHITE) ? "White" : "Black");
        return 2; // Success - game over
    }
    
    return 3; // Invalid move
}

/**
 * Switches the current player
 */
static void switch_player(char* player) {
    *player = (*player == WHITE) ? BLACK : WHITE;
}

/**
 * Handles check state display
 */
static void handle_check_state(char* load_move, int* is_check) {
    if (*is_check == 1) {
        if (strcmp(load_move, "-") == 0) 
            display_current_board(&board[0][0]);
        printf("Check!\n");
        *is_check = 0;
    }
}

/**
 * Displays the current player prompt
 */
static void display_player_prompt(char player) {
    printf("%s player: ", (player == WHITE) ? "White" : "Black");
}

/**
 * Gets input from the player
 */
static int get_player_input(char* input) {
    // Clear input buffer first
    fflush(stdin);
    
    // Get the input - use larger buffer size (10) to accommodate moves with spaces
    if (fgets(input, 10, stdin) == NULL) {
        return 0; // Error or EOF
    }
    
    // Remove newline if present
    input[strcspn(input, "\n")] = 0;
    
    // Check if input is empty
    if (input[0] == '\0') {
        return 0;
    }
    
    return 1;
}

/**
 * Takes back the last move
 */
void take_back_move() {
    if (current_move == NULL) return;
    
    // Restore the piece to its original position
    board[current_move->from_x][current_move->from_y].piece = 
        board[current_move->to_x][current_move->to_y].piece;
    board[current_move->from_x][current_move->from_y].color = 
        board[current_move->to_x][current_move->to_y].color;
    
    // Restore captured piece if any
    board[current_move->to_x][current_move->to_y].piece = current_move->captured_piece;
    board[current_move->to_x][current_move->to_y].color = current_move->captured_color;
    
    // Update king pointers if needed
    if (board[current_move->from_x][current_move->from_y].piece == PIECE_LETTERS[KING]) {
        if (board[current_move->from_x][current_move->from_y].color == WHITE) {
            white_king = &board[current_move->from_x][current_move->from_y];
        } else {
            black_king = &board[current_move->from_x][current_move->from_y];
        }
    }
    
    // Remove the move from history
    Move* prev = current_move->previous;
    free_move(current_move);
    current_move = prev;
    
    display_current_board(&board[0][0]);
}

/**
 * Cleans up all move history
 */
static void cleanup_moves(void) {
    free_all_moves(current_move);
    current_move = NULL;
}
