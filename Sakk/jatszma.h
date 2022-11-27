#ifndef JATSZMA_H_INCLUDED
#define JATSZMA_H_INCLUDED
#include "mezo.h"
#include "lepes.h"

extern Mezo tabla[8][8];
extern Lepes *lepes;

void uj_jatek(int* navigal);
int lepesek_megszamolasa(Lepes* l, int ossz);
int egy_lepes(char* betolt_e, int betolt_vege);
void tabla_betolt();

#endif // JATSZMA_H_INCLUDED
