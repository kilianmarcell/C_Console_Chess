#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "save_load.h"
#include "user_guide.h"
#include "exit.h"
#include "error_message.h"
#include "util.h"

/**
 * Main menu of the chess application
 * This is the first function that runs when the program starts.
 * It displays menu options and calls the appropriate function based on user selection.
 * 
 * @param navigate Pointer to navigation variable that stores the user's menu choice
 */
void menu(int* navigate) {
     printf("- Chess -\n\n1. New game\n2. Load game\n3. User guide\n\n9. Exit\n\n");
     printf("Choice: ");
     
     // Input validation
     if (scanf("%d", navigate) != 1) {
          // Clear input buffer if non-numeric input was provided
          while (getchar() != '\n');
          *navigate = 0;  // Set to invalid choice
     }
     
     switch (*navigate) {
          case 1:
               clear_screen();
               new_game(navigate);
               break;
          case 2:
               clear_screen();
               load_game(navigate);
               break;
          case 3:
               clear_screen();
               show_user_guide(navigate);
               break;
          case 9:
               exit_program();
               break;
          default:
               clear_screen();
               display_error("invalid menu choice");
               menu(navigate);
     }
}
