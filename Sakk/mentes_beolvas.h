#ifndef MENTES_BEOLVAS_H_INCLUDED
#define MENTES_BEOLVAS_H_INCLUDED

#include "lepes.h"

extern char oszlopok[];
extern Lepes *lepes;

void jatek_mentese();
void fajlbair(FILE* mentes, Lepes* lepes);
void jatek_betolt(int* navigal);

#endif // MENTES_BEOLVAS_H_INCLUDED
