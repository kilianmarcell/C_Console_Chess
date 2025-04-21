#ifndef PAWN_PROMOTION_H
#define PAWN_PROMOTION_H

#include "square.h" // Include necessary dependencies, like square.h

/**
 * Handles pawn promotion when a pawn reaches the opposite end of the board
 * 
 * @param s Pointer to the square containing the pawn to be promoted
 */
void promote_pawn(Square* s);

#endif // PAWN_PROMOTION_H
