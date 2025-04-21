#include <stdio.h>
#include <stdlib.h>
#include "util.h"

/**
 * Clears the console screen in a cross-platform way
 */
void clear_screen(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
