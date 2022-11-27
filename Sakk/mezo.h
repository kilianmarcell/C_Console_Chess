#ifndef MEZO_H_INCLUDED
#define MEZO_H_INCLUDED

typedef struct {
     int x;
     int y;
     char babu;
     char szin;
} Mezo;

extern Mezo tabla[8][8];
extern Mezo* feher_kiraly;
extern Mezo* fekete_kiraly;

#endif