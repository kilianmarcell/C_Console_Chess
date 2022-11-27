#include <stdio.h>
#include <stdlib.h>
#include "mezo.h"
#include "lepes.h"
#include "konvertalasok.h"
#include "babu_lepesek.h"
#include "sakk_ellenorzo.h"
#include "lepes_ellenorzo.h"
#include "menu.h"
#include "debugmalloc.h"

void menu(int* navigal);
void jatek_betolt(int* navigal);
void hibauzenet(char *uzenet);
int karakterbol_szamra_konvertal(char c);

//Konstansok
Mezo tabla[8][8];
Mezo* feher_kiraly;
Mezo* fekete_kiraly;

Lepes *lepes = NULL;

//a sakktábla oszlopait tárolja a karaktertömb
char oszlopok[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

//a sakkbábuk betűit tárolja a karaktertömb
char babubetuk[] = { 'k', 'q', 'r', 'b', 'h', 'p' };

//a sakkbábukat tárolja el a "karaktertömb"
char *babuk[] = { "♔", "♕", "♖", "♗", "♘", "♙", "♚", "♛", "♜", "♝", "♞", "♟︎" };

int main(void) {
    int navigal;
     menu(&navigal);
}
