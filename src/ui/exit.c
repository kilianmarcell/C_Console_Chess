#include <stdlib.h>
#include "move.h"
#include "memory_utils.h"

extern Move *current_move;

/**
 * Properly exits the program after cleaning up allocated resources
 */
void exit_program() {
     // Free all allocated moves
     free_all_moves(current_move);
     
     // Exit the program
     exit(0);
}
