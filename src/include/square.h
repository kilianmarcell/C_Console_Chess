#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED

typedef struct {
     int x;
     int y;
     char piece;  // was 'babu'
     char color;  // was 'szin'
} Square;         // was 'Mezo'

extern Square board[8][8];        // was 'tabla'
extern Square* white_king;        // was 'feher_kiraly'
extern Square* black_king;        // was 'fekete_kiraly'

#endif
