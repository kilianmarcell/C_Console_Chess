#include <stdio.h>
#include <ctype.h>

extern char oszlopok[];
extern char babubetuk[];
extern char *babuk[];

//Különbözõ konvertálások
//ellenõrzi, hogy érvényes sorokat adott-e meg a felhasználó (sakk játszma közben)
int helyesxy(int* x, int* y) {
     return (*x >= 1 && *x <= 8 && *y >= 1 && *y <= 8);
}

//ellenõrzi, hogy érvényes pozíciót adott-e meg a felhasználó (sakk játszma közben)
int helyes_sor_oszlop(char* honnanoszlop, char* hovaoszlop) {
     *honnanoszlop = tolower(*honnanoszlop);
     *hovaoszlop = tolower(*hovaoszlop);
     int szamol = 0;
     for(int i = 0; i < 8; i++) {
          if (oszlopok[i] == *hovaoszlop) ++szamol;
          if (oszlopok[i] == *honnanoszlop) ++szamol;
     }

     return (szamol == 2);
}

//a játékos által megadott betût egy y koordinátává változtatja
int betubol_szamra_konvertal(char* betu) {
     for(int i = 0; i < 8; i++) {
          if (oszlopok[i] == *betu) return (i);
     }

     return 0;
}

//egy bábunak a betûjébõl és a színébõl elõállítja a bábut
char *baburakonvertal(char betu, char szin) {
     int hanyadik;

     for(int i = 0; i < 8; i++) {
          if (babubetuk[i] == betu) hanyadik = i;
     }

     if (szin == 'w') return babuk[hanyadik];
     if (szin == 'b') return babuk[hanyadik + 6];
     return " ";
}

//ellenõrzi, hogy a koordináták a táblán belülre mutatnak-e
int tablan_belul_van_e(int x, int y) {
     return (x >= 0 && x <= 7 && y >= 0 && y <= 7);
}

//egy bejövõ szám karaktert (char-t) konvertál számra (int) típusúra
int karakterbol_szamra_konvertal(char c) {
     int szam = 0;
     szam = c - '0';
     return szam;
}
