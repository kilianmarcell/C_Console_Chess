#include <stdio.h>
#include "error_message.h"
#include "menu.h"

/**
 * Displays an error message to the user
 * 
 * @param message The error message to display
 */
void display_error(char *message) {
     printf("Invalid move! Please enter a valid %s.\n\n", message);
}
