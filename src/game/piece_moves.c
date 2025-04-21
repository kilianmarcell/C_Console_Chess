#include <stdlib.h>
#include "piece_moves.h"
#include "square.h"

extern Square board[8][8];

/**
 * Validates a knight move
 * 
 * @param current Source square
 * @param destination Destination square
 * @return 1 if valid knight move, 0 otherwise
 */
int knight_move(Square* current, Square* destination) {
    int dx = abs(current->x - destination->x);
    int dy = abs(current->y - destination->y);
    
    // Knight moves in an L-shape: 2 squares in one direction and 1 in the other
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

/**
 * Validates a king move
 * 
 * @param current Source square
 * @param destination Destination square
 * @return 1 if valid king move, 0 otherwise
 */
int king_move(Square* current, Square* destination) {
    int dx = abs(current->x - destination->x);
    int dy = abs(current->y - destination->y);
    
    // King can move one square in any direction
    return dx <= 1 && dy <= 1 && (dx > 0 || dy > 0);
}

/**
 * Checks if the path is clear for an up-right diagonal move
 * 
 * @param current Source square
 * @param destination Destination square
 * @return 1 if path is clear, 0 if blocked
 */
int up_right_move(Square* current, Square* destination) {
    int x = current->x - 1;
    int y = current->y + 1;
    
    while (x > destination->x && y < destination->y) {
        if (board[x][y].piece != '-') {
            return 0; // Path is blocked
        }
        x--;
        y++;
    }
    
    return 1; // Path is clear
}

/**
 * Checks if the path is clear for a down-right diagonal move
 * 
 * @param current Source square
 * @param destination Destination square
 * @return 1 if path is clear, 0 if blocked
 */
int down_right_move(Square* current, Square* destination) {
    int x = current->x + 1;
    int y = current->y + 1;
    
    while (x < destination->x && y < destination->y) {
        if (board[x][y].piece != '-') {
            return 0; // Path is blocked
        }
        x++;
        y++;
    }
    
    return 1; // Path is clear
}

/**
 * Checks if the path is clear for an up-left diagonal move
 * 
 * @param current Source square
 * @param destination Destination square
 * @return 1 if path is clear, 0 if blocked
 */
int up_left_move(Square* current, Square* destination) {
    int x = current->x - 1;
    int y = current->y - 1;
    
    while (x > destination->x && y > destination->y) {
        if (board[x][y].piece != '-') {
            return 0; // Path is blocked
        }
        x--;
        y--;
    }
    
    return 1; // Path is clear
}

/**
 * Checks if the path is clear for a down-left diagonal move
 * 
 * @param current Source square
 * @param destination Destination square
 * @return 1 if path is clear, 0 if blocked
 */
int down_left_move(Square* current, Square* destination) {
    int x = current->x + 1;
    int y = current->y - 1;
    
    while (x < destination->x && y > destination->y) {
        if (board[x][y].piece != '-') {
            return 0; // Path is blocked
        }
        x++;
        y--;
    }
    
    return 1; // Path is clear
}

/**
 * Validates if a diagonal move is valid
 * 
 * @param from Source square
 * @param to Destination square
 * @return 1 if valid diagonal move with clear path, 0 otherwise
 */
int is_diagonal_valid(Square* from, Square* to) {
    int dx = abs(from->x - to->x);
    int dy = abs(from->y - to->y);
    
    // Check if move is diagonal (same number of squares in x and y direction)
    if (dx != dy) {
        return 0;
    }
    
    // Determine which diagonal direction and check if path is clear
    if (from->x > to->x && from->y < to->y) {
        return up_right_move(from, to);
    } else if (from->x < to->x && from->y < to->y) {
        return down_right_move(from, to);
    } else if (from->x > to->x && from->y > to->y) {
        return up_left_move(from, to);
    } else if (from->x < to->x && from->y > to->y) {
        return down_left_move(from, to);
    }
    
    return 0;
}

/**
 * Checks if the path is clear for a straight up move
 * 
 * @param current Source square
 * @param destination Destination square
 * @return 1 if path is clear, 0 if blocked
 */
int straight_up_move(Square* current, Square* destination) {
    for (int x = current->x - 1; x > destination->x; x--) {
        if (board[x][current->y].piece != '-') {
            return 0; // Path is blocked
        }
    }
    return 1; // Path is clear
}

/**
 * Checks if the path is clear for a straight down move
 * 
 * @param current Source square
 * @param destination Destination square
 * @return 1 if path is clear, 0 if blocked
 */
int straight_down_move(Square* current, Square* destination) {
    for (int x = current->x + 1; x < destination->x; x++) {
        if (board[x][current->y].piece != '-') {
            return 0; // Path is blocked
        }
    }
    return 1; // Path is clear
}

/**
 * Checks if the path is clear for a straight left move
 * 
 * @param current Source square
 * @param destination Destination square
 * @return 1 if path is clear, 0 if blocked
 */
int straight_left_move(Square* current, Square* destination) {
    for (int y = current->y - 1; y > destination->y; y--) {
        if (board[current->x][y].piece != '-') {
            return 0; // Path is blocked
        }
    }
    return 1; // Path is clear
}

/**
 * Checks if the path is clear for a straight right move
 * 
 * @param current Source square
 * @param destination Destination square
 * @return 1 if path is clear, 0 if blocked
 */
int straight_right_move(Square* current, Square* destination) {
    for (int y = current->y + 1; y < destination->y; y++) {
        if (board[current->x][y].piece != '-') {
            return 0; // Path is blocked
        }
    }
    return 1; // Path is clear
}

/**
 * Validates if a straight move is valid
 * 
 * @param from Source square
 * @param to Destination square
 * @return 1 if valid straight move with clear path, 0 otherwise
 */
int is_straight_valid(Square* from, Square* to) {
    // Check if move is horizontal or vertical
    if (from->x != to->x && from->y != to->y) {
        return 0;
    }
    
    // Determine direction and check if path is clear
    if (from->x > to->x) {
        return straight_up_move(from, to);
    } else if (from->x < to->x) {
        return straight_down_move(from, to);
    } else if (from->y > to->y) {
        return straight_left_move(from, to);
    } else if (from->y < to->y) {
        return straight_right_move(from, to);
    }
    
    return 0;
}
