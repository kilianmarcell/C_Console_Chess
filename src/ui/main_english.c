#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "menu.h"
#include "game.h"
#include "save_load.h"
#include "user_guide.h"
#include "exit.h"
#include "error_message.h"
#include "util.h"
#include <windows.h> // Include for SetConsoleOutputCP

/**
 * Main entry point for the English Chess program
 * Initializes and starts the menu system
 */
int main() {
    SetConsoleOutputCP(CP_UTF8); // Set console output to UTF-8

    // On Windows, set console mode to support Unicode
    #ifdef _WIN32
        system("chcp 65001 > nul");  // Change to UTF-8 and hide output
        printf("\033[2J\033[1;1H");  // Clear screen using ANSI escape sequence
    #endif
    
    printf("Loading chess pieces...\n\n");
    printf("Sample pieces: White ♔ ♕ ♖ ♗ ♘ ♙  Black ♚ ♛ ♜ ♝ ♞ ♟\n\n");
    printf("Press Enter to continue...");
    getchar();
    
    int navigate = 0;
    menu(&navigate);
    return 0;
}
