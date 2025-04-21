#ifndef CONVERSIONS_H_INCLUDED
#define CONVERSIONS_H_INCLUDED

/**
 * Converts a column letter to its numerical array index
 * For example: 'a' -> 0, 'b' -> 1, etc.
 * 
 * @param c Pointer to the column letter character
 * @return Numerical index, or -1 if invalid
 */
int letter_to_number(char* c);

/**
 * Validates if the row and column numbers are within the chess board range
 * 
 * @param x Pointer to the row number (1-8)
 * @param y Pointer to the column number (converted from a-h)
 * @return 1 if valid, 0 if invalid
 */
int is_valid_xy(int* x, int* y);

/**
 * Validates if the column and row characters are valid chess notation
 * 
 * @param column Pointer to the column character (a-h)
 * @param row Pointer to the row character (1-8)
 * @return 1 if valid, 0 if invalid
 */
int is_valid_column_row(char* column, char* row);

#endif
