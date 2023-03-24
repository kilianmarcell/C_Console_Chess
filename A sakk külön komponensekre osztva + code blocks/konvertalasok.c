#include <stdio.h>
#include <ctype.h>

extern char oszlopok[];
extern char babubetuk[];
extern char *babuk[];

//K�l�nb�z� konvert�l�sok
//ellen�rzi, hogy �rv�nyes sorokat adott-e meg a felhaszn�l� (sakk j�tszma k�zben)
int helyesxy(int* x, int* y) {
     return (*x >= 1 && *x <= 8 && *y >= 1 && *y <= 8);
}

//ellen�rzi, hogy �rv�nyes poz�ci�t adott-e meg a felhaszn�l� (sakk j�tszma k�zben)
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

//a j�t�kos �ltal megadott bet�t egy y koordin�t�v� v�ltoztatja
int betubol_szamra_konvertal(char* betu) {
     for(int i = 0; i < 8; i++) {
          if (oszlopok[i] == *betu) return (i);
     }

     return 0;
}

//egy b�bunak a bet�j�b�l �s a sz�n�b�l el��ll�tja a b�but
char *baburakonvertal(char betu, char szin) {
     int hanyadik;

     for(int i = 0; i < 8; i++) {
          if (babubetuk[i] == betu) hanyadik = i;
     }

     if (szin == 'w') return babuk[hanyadik];
     if (szin == 'b') return babuk[hanyadik + 6];
     return " ";
}

//ellen�rzi, hogy a koordin�t�k a t�bl�n bel�lre mutatnak-e
int tablan_belul_van_e(int x, int y) {
     return (x >= 0 && x <= 7 && y >= 0 && y <= 7);
}

//egy bej�v� sz�m karaktert (char-t) konvert�l sz�mra (int) t�pus�ra
int karakterbol_szamra_konvertal(char c) {
     int szam = 0;
     szam = c - '0';
     return szam;
}
