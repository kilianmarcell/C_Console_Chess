#include <stdio.h>
#include "conversions.h"
#include "chess_constants.h"

/**
 * Converts a column letter to its numerical array index
 * For example: 'a' -> 0, 'b' -> 1, etc.
 * 
 * @param c Pointer to the column letter character
 * @return Numerical index, or -1 if invalid
 */
int letter_to_number(char* c) {
    char letter = *c;
    
    for (int i = 0; i < 8; i++) {
        if (letter == COLUMNS[i]) {
            return i;
        }
    }
    
    return -1;
}

/**
 * Validates if the row and column numbers are within the chess board range
 * 
 * @param x Pointer to the row number (1-8)
 * @param y Pointer to the column number (converted from a-h)
 * @return 1 if valid, 0 if invalid
 */
int is_valid_xy(int* x, int* y) {
    if (*x < 1 || *x > 8 || *y < 0 || *y > 7) {
        return 0;
    }
    return 1;
}

/**
 * Validates if the column and row characters are valid chess notation
 * 
 * @param column Pointer to the column character (a-h)
 * @param row Pointer to the row character (1-8)
 * @return 1 if valid, 0 if invalid
 */
int is_valid_column_row(char* column, char* row) {
    int column_valid = 0;
    int row_valid = 0;
    
    // Validate column (a-h)
    for (int i = 0; i < 8; i++) {
        if (*column == COLUMNS[i]) {
            column_valid = 1;
            break;
        }
    }
    
    // Validate row (1-8)
    if (*row >= '1' && *row <= '8') {
        row_valid = 1;
    }
    
    return column_valid && row_valid;
}
