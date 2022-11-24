#include <stdio.h>
#include <stdlib.h>
#include "mezo.h"
#include "lepes.h"
#include "debugmalloc.h"

void menu(int* navigal);
void *jatek_betolt(int* navigal);
void hibauzenet(char *uzenet);
int karakterbol_szamra_konvertal(char c);

//lépéseket ellenőrző metódusok
int lo_lepes(Mezo* jelenlegi, Mezo* hova);

int jobbra_fel_lepes(Mezo* jelenlegi, Mezo* hova);
int jobbra_le_lepes(Mezo* jelenlegi, Mezo* hova);
int balra_fel_lepes(Mezo* jelenlegi, Mezo* hova);
int balra_le_lepes(Mezo* jelenlegi, Mezo* hova);

int egyenes_fel_lepes(Mezo *jelenlegi, Mezo *hova);
int egyenes_le_lepes(Mezo *jelenlegi, Mezo *hova);
int egyenes_jobbra_lepes(Mezo *jelenlegi, Mezo *hova);
int egyenes_balra_lepes(Mezo *jelenlegi, Mezo *hova);

//sakkot ellenőrző metódusok
int jobbra_fel_ellenoriz(Mezo* jelenlegi, char szin);
int jobbra_le_ellenoriz(Mezo* jelenlegi, char szin);
int balra_fel_ellenoriz(Mezo* jelenlegi, char szin);
int balra_le_ellenoriz(Mezo* jelenlegi, char szin);

int egyenesen_fel_ellenoriz(Mezo* jelenlegi, char szin);
int egyenesen_le_ellenoriz(Mezo* jelenlegi, char szin);
int egyenesen_jobbra_ellenoriz(Mezo* jelenlegi, char szin);
int egyenesen_balra_ellenoriz(Mezo* jelenlegi, char szin);

int lo_van_e(Mezo* kiraly);

void elozo_lepesek_kiir(Lepes* l, int szamol);
void tabla_betolt();
void egy_lepes(int* muvelet, int* x, int* y, int* ellenoriz, int* hanyadik_lepes, char* sor, char* oszlop, char* valasz, char* jatekos);
void jatek_mentese();

//-------------------------------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------------------------------

//Különböző konvertálások
//ellenőrzi, hogy érvényes sorokat adott-e meg a felhasználó (sakk játszma közben)
int helyesxy(int* x, int* y) {
     return (*x >= 1 && *x <= 8 && *y >= 1 && *y <= 8);
}

//ellenőrzi, hogy érvényes pozíciót adott-e meg a felhasználó (sakk játszma közben)
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

//a játékos által megadott betűt egy y koordinátává változtatja
int betubol_szamra_konvertal(char* betu) {
     for(int i = 0; i < 8; i++) {
          if (oszlopok[i] == *betu) return (i);
     }

     return 0;
}

//egy bábunak a betűjéből és a színéből előállítja a bábut
char *baburakonvertal(char betu, char szin) {
     int hanyadik;
     
     for(int i = 0; i < 8; i++) {
          if (babubetuk[i] == betu) hanyadik = i;
     }

     if (szin == 'w') return babuk[hanyadik];
     if (szin == 'b') return babuk[hanyadik + 6];
     return " ";
}

//ellenőrzi, hogy a koordináták a táblán belülre mutatnak-e
int tablan_belul_van_e(int x, int y) {
     return (x >= 0 && x <= 7 && y >= 0 && y <= 7);
}

//egy bejövő szám karaktert (char-t) konvertál számra (int) típusúra
int karakterbol_szamra_konvertal(char c) {
     int szam = 0;
     szam = c - '0';
     return szam;
}

//-------------------------------------------------------------------------------------------------------

//ló lépései
int lo_lepes(Mezo* jelenlegi, Mezo* hova) {
     if (tablan_belul_van_e(jelenlegi->x - 1, jelenlegi->y + 2)) {
          if (&tabla[jelenlegi->x - 1][jelenlegi->y + 2] == hova) return 1;
     }
     if (tablan_belul_van_e(jelenlegi->x - 1, jelenlegi->y - 2)) {
          if (&tabla[jelenlegi->x - 1][jelenlegi->y - 2] == hova) return 1;
     }
     if (tablan_belul_van_e(jelenlegi->x - 2, jelenlegi->y + 1)) {
          if (&tabla[jelenlegi->x - 2][jelenlegi->y + 1] == hova) return 1;
     }
     if (tablan_belul_van_e(jelenlegi->x - 2, jelenlegi->y - 1)) {
          if (&tabla[jelenlegi->x - 2][jelenlegi->y - 1] == hova) return 1;
     }
     if (tablan_belul_van_e(jelenlegi->x + 1, jelenlegi->y + 2)) {
          if (&tabla[jelenlegi->x + 1][jelenlegi->y + 2] == hova) return 1;
     }
     if (tablan_belul_van_e(jelenlegi->x + 1, jelenlegi->y - 2)) {
          if (&tabla[jelenlegi->x + 1][jelenlegi->y - 2] == hova) return 1;
     }
     if (tablan_belul_van_e(jelenlegi->x + 2, jelenlegi->y + 1)) {
          if (&tabla[jelenlegi->x + 2][jelenlegi->y + 1] == hova) return 1;
     }
     if (tablan_belul_van_e(jelenlegi->x + 2, jelenlegi->y - 1)) {
          if (&tabla[jelenlegi->x + 2][jelenlegi->y - 1] == hova) return 1;
     }

     return 0;
}

//király lépései
int kiraly_lepes(Mezo* jelenlegi, Mezo* hova) {
     if (tablan_belul_van_e(jelenlegi->x - 1, jelenlegi->y)) {
          if (&tabla[jelenlegi->x - 1][jelenlegi->y] == hova) return 1;
     }
     if (tablan_belul_van_e(jelenlegi->x - 1, jelenlegi->y + 1)) {
          if (&tabla[jelenlegi->x - 1][jelenlegi->y + 1] == hova) return 1;
     }
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y + 1)) {
          if (&tabla[jelenlegi->x][jelenlegi->y + 1] == hova) return 1;
     }
     if (tablan_belul_van_e(jelenlegi->x + 1, jelenlegi->y + 1)) {
          if (&tabla[jelenlegi->x + 1][jelenlegi->y + 1] == hova) return 1;
     }
     if (tablan_belul_van_e(jelenlegi->x + 1, jelenlegi->y)) {
          if (&tabla[jelenlegi->x + 1][jelenlegi->y] == hova) return 1;
     }
     if (tablan_belul_van_e(jelenlegi->x + 1, jelenlegi->y - 1)) {
          if (&tabla[jelenlegi->x + 1][jelenlegi->y - 1] == hova) return 1;
     }
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y - 1)) {
          if (&tabla[jelenlegi->x][jelenlegi->y - 1] == hova) return 1;
     }
     if (tablan_belul_van_e(jelenlegi->x - 1, jelenlegi->y - 1)) {
          if (&tabla[jelenlegi->x - 1][jelenlegi->y - 1] == hova) return 1;
     }

     return 0;
}

//átlós lépések
//egy bábunak a jobbra felfele átlós lépését ellenőrzi
int jobbra_fel_lepes(Mezo* jelenlegi, Mezo* hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->x - 1 >= 0 && jelenlegi->y + 1 <= 7) {
               return jobbra_fel_lepes(&tabla[jelenlegi->x - 1][jelenlegi->y + 1], hova);
          }
     }

     return 0;
}

//egy bábunak a jobbra lefele átlós lépését ellenőrzi
int jobbra_le_lepes(Mezo* jelenlegi, Mezo* hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->x + 1 >= 0 && jelenlegi->y + 1 <= 7) {
               return jobbra_le_lepes(&tabla[jelenlegi->x + 1][jelenlegi->y + 1], hova);
          }
     }

     return 0;
}

//egy bábunak a balra felfele átlós lépését ellenőrzi
int balra_fel_lepes(Mezo* jelenlegi, Mezo* hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->x - 1 >= 0 && jelenlegi->y - 1 <= 7) {
               return balra_fel_lepes(&tabla[jelenlegi->x - 1][jelenlegi->y - 1], hova);
          }
     }

     return 0;
}

//egy bábunak a balra lefele átlós lépését ellenőrzi
int balra_le_lepes(Mezo* jelenlegi, Mezo* hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->x + 1 >= 0 && jelenlegi->y - 1 <= 7) {
               return balra_le_lepes(&tabla[jelenlegi->x + 1][jelenlegi->y - 1], hova);
          }
     }

     return 0;
}

//átlós lépések ellenőrzése
int atlosan_jo_e(Mezo* honnan, Mezo* hova) {
     if (jobbra_fel_lepes(&tabla[honnan->x - 1][honnan->y + 1], hova)) return 1;
     if (jobbra_le_lepes(&tabla[honnan->x + 1][honnan->y + 1], hova)) return 1;
     if (balra_fel_lepes(&tabla[honnan->x - 1][honnan->y - 1], hova)) return 1;
     if (balra_le_lepes(&tabla[honnan->x + 1][honnan->y - 1], hova)) return 1;
     
     return 0;
}

//egyenes lépések
//az egyenesen felfele lépés helyességét ellenőrzi a metódus
int egyenes_fel_lepes(Mezo *jelenlegi, Mezo *hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->x - 1 >= 0) {
               return egyenes_fel_lepes(&tabla[jelenlegi->x - 1][jelenlegi->y], hova);
          }
     }

     return 0;
}

//az egyenesen lefele lépés helyességét ellenőrzi a metódus
int egyenes_le_lepes(Mezo *jelenlegi, Mezo *hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->x + 1 <= 7) {
               return egyenes_le_lepes(&tabla[jelenlegi->x + 1][jelenlegi->y], hova);
          }
     }

     return 0;
}

//az egyenesen jobbra lépés helyességét ellenőrzi a metódus
int egyenes_jobbra_lepes(Mezo *jelenlegi, Mezo *hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->y + 1 <= 7) {
               return egyenes_jobbra_lepes(&tabla[jelenlegi->x][jelenlegi->y + 1], hova);
          }
     }

     return 0;
}

//az egyenesen balra lépés helyességét ellenőrzi a metódus
int egyenes_balra_lepes(Mezo *jelenlegi, Mezo *hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->y - 1 >= 0) {
               return egyenes_balra_lepes(&tabla[jelenlegi->x][jelenlegi->y - 1], hova);
          }
     }

     return 0;
}

//egyenes lépések ellenőrzése
int egyenesen_jo_e(Mezo* honnan, Mezo* hova) {
     if (egyenes_fel_lepes(&tabla[honnan->x - 1][honnan->y], hova)) return 1;
     if (egyenes_le_lepes(&tabla[honnan->x + 1][honnan->y], hova)) return 1;
     if (egyenes_jobbra_lepes(&tabla[honnan->x][honnan->y + 1], hova)) return 1;
     if (egyenes_balra_lepes(&tabla[honnan->x][honnan->y - 1], hova)) return 1;
     
     return 0;
}

//-------------------------------------------------------------------------------------------------------

//elenőrzés, hogy átlós irányba van-e sakk
//jobbra felfele
int jobbra_fel_ellenoriz(Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'b') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->x - 1 >= 0 && jelenlegi->y + 1 <= 7) {
               return jobbra_fel_ellenoriz(&tabla[jelenlegi->x - 1][jelenlegi->y + 1], szin);
          }
     }

     return 0;
}

//jobbra lefele
int jobbra_le_ellenoriz(Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'b') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->x + 1 <= 7 && jelenlegi->y + 1 <= 7) {
               return jobbra_le_ellenoriz(&tabla[jelenlegi->x + 1][jelenlegi->y + 1], szin);
          }
     }

     return 0;
}

//balra felfele
int balra_fel_ellenoriz(Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'b') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->x - 1 >= 0 && jelenlegi->y - 1 >= 0) {
               return balra_fel_ellenoriz(&tabla[jelenlegi->x - 1][jelenlegi->y - 1], szin);
          }
     }

     return 0;
}

//balra lefele
int balra_le_ellenoriz(Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'b') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->x + 1 <= 7 && jelenlegi->y - 1 >= 0) {
               return balra_le_ellenoriz(&tabla[jelenlegi->x + 1][jelenlegi->y - 1], szin);
          }
     }

     return 0;
}

//elenőrzés, hogy egyenes irányba van-e sakk
//felfele
int egyenesen_fel_ellenoriz(Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'r') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->x - 1 >= 0) {
               return egyenesen_fel_ellenoriz(&tabla[jelenlegi->x - 1][jelenlegi->y], szin);
          }
     }

     return 0;
}

//lefele
int egyenesen_le_ellenoriz(Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'r') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->x + 1 <= 7) {
               return egyenesen_le_ellenoriz(&tabla[jelenlegi->x + 1][jelenlegi->y], szin);
          }
     }

     return 0;
}

//jobbra
int egyenesen_jobbra_ellenoriz(Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'r') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->y + 1 >= 0) {
               return egyenesen_jobbra_ellenoriz(&tabla[jelenlegi->x][jelenlegi->y + 1], szin);
          }
     }

     return 0;
}

//balra
int egyenesen_balra_ellenoriz(Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'r') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->y - 1 >= 0) {
               return egyenesen_balra_ellenoriz(&tabla[jelenlegi->x][jelenlegi->y - 1], szin);
          }
     }

     return 0;
}

//ellenőzi, hogy ló lépésben van-e sakk
int lo_van_e(Mezo* kiraly) {
     if (tablan_belul_van_e(kiraly->x - 1, kiraly->y + 2)) {
          if (tabla[kiraly->x - 1][kiraly->y + 2].babu == 'h' &&
               tabla[kiraly->x - 1][kiraly->y + 2].szin != kiraly->szin) return 1;
     }
     if (tablan_belul_van_e(kiraly->x - 1, kiraly->y - 2)) {
          if (tabla[kiraly->x - 1][kiraly->y - 2].babu == 'h' &&
               tabla[kiraly->x - 1][kiraly->y - 2].szin != kiraly->szin) return 1;
     }
     if (tablan_belul_van_e(kiraly->x - 2, kiraly->y + 1)) {
          if (tabla[kiraly->x - 2][kiraly->y + 1].babu == 'h' &&
               tabla[kiraly->x - 2][kiraly->y + 1].szin != kiraly->szin) return 1;
     }
     if (tablan_belul_van_e(kiraly->x - 2, kiraly->y - 1)) {
          if (tabla[kiraly->x - 2][kiraly->y - 1].babu == 'h' &&
               tabla[kiraly->x - 2][kiraly->y - 1].szin != kiraly->szin) return 1;
     }
     if (tablan_belul_van_e(kiraly->x + 1, kiraly->y + 2)) {
          if (tabla[kiraly->x + 1][kiraly->y + 2].babu == 'h' &&
               tabla[kiraly->x + 1][kiraly->y + 2].szin != kiraly->szin) return 1;
     }
     if (tablan_belul_van_e(kiraly->x + 1, kiraly->y - 2)) {
          if (tabla[kiraly->x + 1][kiraly->y - 2].babu == 'h' &&
               tabla[kiraly->x + 1][kiraly->y - 2].szin != kiraly->szin) return 1;
     }
     if (tablan_belul_van_e(kiraly->x + 2, kiraly->y + 1)) {
          if (tabla[kiraly->x + 2][kiraly->y + 1].babu == 'h' &&
               tabla[kiraly->x + 2][kiraly->y + 1].szin != kiraly->szin) return 1;
     }
     if (tablan_belul_van_e(kiraly->x + 2, kiraly->y - 1)) {
          if (tabla[kiraly->x + 2][kiraly->y - 1].babu == 'h' &&
               tabla[kiraly->x + 2][kiraly->y - 1].szin != kiraly->szin) return 1;
     }

     return 0;
}

//ellenőzi, hogy paraszt lépésben van-e sakk
int paraszt_van_e(Mezo* kiraly) {
     if (kiraly->szin == 'w') {
          if (tablan_belul_van_e(kiraly->x - 1, kiraly->y + 1)) {
               if (tabla[kiraly->x - 1][kiraly->y + 1].babu == 'p' &&
                    tabla[kiraly->x - 1][kiraly->y + 1].szin == 'b') return 1;
          }
          if (tablan_belul_van_e(kiraly->x - 1, kiraly->y - 1)) {
               if (tabla[kiraly->x - 1][kiraly->y - 1].babu == 'p' &&
                    tabla[kiraly->x - 1][kiraly->y - 1].szin == 'b') return 1;
          }
     } else {
          if (tablan_belul_van_e(kiraly->x + 1, kiraly->y + 1)) {
               if (tabla[kiraly->x + 1][kiraly->y - 1].babu == 'p' &&
                    tabla[kiraly->x + 1][kiraly->y - 1].szin == 'w') return 1;
          }
          if (tablan_belul_van_e(kiraly->x + 1, kiraly->y - 1)) {
               if (tabla[kiraly->x + 1][kiraly->y + 1].babu == 'p' &&
                    tabla[kiraly->x + 1][kiraly->y + 1].szin == 'w') return 1;
          }
     }

     return 0;
}

//ellenőrzi, hogy sakk van-e
int sakk_ellenoriz(Mezo* feher, Mezo* fekete) {
     //átlós lépések
     if (jobbra_fel_ellenoriz(&tabla[feher->x - 1][feher->y + 1], 'w')) return 1; //printf("sakk van1");
     if (jobbra_fel_ellenoriz(&tabla[fekete->x - 1][fekete->y + 1], 'b')) return 2; //printf("sakk van2");

     if (jobbra_le_ellenoriz(&tabla[feher->x + 1][feher->y + 1], 'w')) return 1; //printf("sakk van3");
     if (jobbra_le_ellenoriz(&tabla[fekete->x + 1][fekete->y + 1], 'b')) return 2; //printf("sakk van4");

     if (balra_fel_ellenoriz(&tabla[feher->x - 1][feher->y - 1], 'w')) return 1; //printf("sakk van5");
     if (balra_fel_ellenoriz(&tabla[fekete->x - 1][fekete->y - 1], 'b')) return 2; //printf("sakk van6");

     if (balra_le_ellenoriz(&tabla[feher->x + 1][feher->y - 1], 'w')) return 1; //printf("sakk van7");
     if (balra_le_ellenoriz(&tabla[fekete->x + 1][fekete->y - 1], 'b')) return 2; //printf("sakk van8");

     //egyenes lépések
     if (egyenesen_fel_ellenoriz(&tabla[feher->x - 1][feher->y], 'w')) return 1; //printf("1sakk van");
     if (egyenesen_fel_ellenoriz(&tabla[fekete->x - 1][fekete->y], 'b')) return 2; //printf("2sakk van");

     if (egyenesen_le_ellenoriz(&tabla[feher->x + 1][feher->y], 'w')) return 1; //printf("3sakk van");
     if (egyenesen_le_ellenoriz(&tabla[fekete->x + 1][fekete->y], 'b')) return 2; //printf("4sakk van");

     if (egyenesen_jobbra_ellenoriz(&tabla[feher->x][feher->y + 1], 'w')) return 1; //printf("5sakk van");
     if (egyenesen_jobbra_ellenoriz(&tabla[fekete->x][fekete->y + 1], 'b')) return 2; //printf("6sakk van");

     if (egyenesen_balra_ellenoriz(&tabla[feher->x][feher->y - 1], 'w')) return 1; //printf("7sakk van");
     if (egyenesen_balra_ellenoriz(&tabla[fekete->x][fekete->y - 1], 'b')) return 2; //printf("8sakk van");

     //ló lépések
     if (lo_van_e(feher) == 1) return 1; //printf("11sakk van");
     if (lo_van_e(fekete) == 1) return 2; //printf("12sakk van");

     if (paraszt_van_e(feher) == 1) return 1; //printf("12sakk van");
     if (paraszt_van_e(fekete) == 1) return 2; //printf("12sakk van");

     return 0;
}

//ellenőrzi a bábuk lépésének helyességét
int lepes_ellenorzes(Mezo* honnan, Mezo* hova, char szin) {
     char ellenkezoszin; 
     if (szin == 'w') ellenkezoszin = 'b';
     if (szin == 'b') ellenkezoszin = 'w';

     //lo lépésének ellenőrzése
     if (honnan->babu == 'h') {
          if (lo_lepes(honnan, hova)) return 1;
          else return 0;
     }
     
     //futó lépésének ellenőrzése
     if (honnan->babu == 'b') {
          if (atlosan_jo_e(honnan, hova)) return 1;
          else return 0;
     }

     //paraszt lépésének ellenőrzése
     if (honnan->babu == 'p') {
          if (honnan->szin == 'w') {
               if (honnan->y == hova->y) {
                    if (honnan->x == hova->x + 1 && hova->babu == '-') return 1;
                    else if (honnan->x == 6 && honnan->x == hova->x + 2) return 1;
                    else return 0;
               } else {
                    if (honnan->x == hova->x + 1 && (honnan->y == hova->y - 1 || honnan->y == hova->y + 1 ) &&
                    hova->szin == ellenkezoszin) return 1;
                    else return 0;
               }
               //TODO: csere, en passant
          } else if (honnan->szin == 'b') {
               if (honnan->y == hova->y) {
                    if (honnan->x == hova->x - 1 && hova->babu == '-') return 1;
                    else if (honnan->x == 1 && honnan->x == hova->x - 2) return 1;
                    else return 0;
               } else {
                    if (honnan->x == hova->x - 1 && (honnan->y == hova->y + 1 || honnan->y == hova->y - 1 ) &&
                    hova->szin == ellenkezoszin) return 1;
                    else return 0;
               }
               //TODO: csere, en passant
          }

          return 0;
     }

     //bástya lépésének ellenőrzése
     if (honnan->babu == 'r') {
          //TODO: sáncolás
          if (egyenesen_jo_e(honnan, hova)) return 1;
          else return 0;
     }
     
     //királynő lépésének ellenőrzése
     if (honnan->babu == 'q') {
          if (atlosan_jo_e(honnan, hova) || egyenesen_jo_e(honnan, hova)) return 1;
          else return 0;
     }

     //király lépésének ellenőrzése
     if (honnan->babu == 'k') {
          if (kiraly_lepes(honnan, hova)) {
               if (honnan->szin == 'w') feher_kiraly = honnan;
               else fekete_kiraly = honnan;
               return 1;
          }

          return 0;
     }

     return 0;
}

//kettő mezőt megcserél
int pozicio_cserel(Mezo* honnan, Mezo* hova, char szin) {
     int ervenytelenlepes = 0;
     char ideiglenes_honnan_babu = honnan->babu, ideiglenes_honnan_szin = honnan->szin;
     char ideiglenes_hova_babu = hova->babu, ideiglenes_hova_szin = hova->szin;
     
     if (honnan->babu == '-' || honnan->szin != szin) return 0; //ha nem a soron lévő játkos lép akkor 0-t ad vissza
     if (hova->szin == szin || lepes_ellenorzes(honnan, hova, szin) == 0) return 2; //ha nem szabályosan lép a játékos 2-t ad vissza
     if (honnan->babu == 'k') {
          if (honnan->szin == 'w') feher_kiraly = hova;
          else fekete_kiraly = hova;
     }
     if (hova->szin != szin && hova->szin != '-') { //ha ütés történik
          hova->babu = '-';
          hova->szin = '-';
     }

     //mezők cserélése
     honnan->babu = hova->babu;
     honnan->szin = hova->szin;
     hova->babu = ideiglenes_honnan_babu;
     hova->szin = ideiglenes_honnan_szin;

     int sakke = sakk_ellenoriz(feher_kiraly, fekete_kiraly);
     if (sakke == 1) {
          if (szin == 'w') ervenytelenlepes = 1;
          else printf("\nSakk!\n");
     } else if (sakke == 2) {
          if (szin == 'b') ervenytelenlepes = 1;
          else printf("\nSakk!\n");
     }

     if (ervenytelenlepes) {
          hova->babu = ideiglenes_hova_babu;
          hova->szin = ideiglenes_hova_szin;
          honnan->babu = ideiglenes_honnan_babu;
          honnan->szin = ideiglenes_honnan_szin;
          
          if (honnan->babu == 'k') {
               if (honnan->szin == 'w') feher_kiraly = honnan;
               else fekete_kiraly = honnan;
          }

          return 2;
     }
     
     Lepes *l;
     l = (Lepes*) malloc(sizeof(Lepes));
     l->honnan_x = honnan->x;
     l->honnan_y = honnan->y;
     l->hova_x = hova->x;
     l->hova_y = hova->y;
     if (ideiglenes_hova_szin != szin && ideiglenes_hova_szin != '-') {
          l->leutott_babu = ideiglenes_hova_babu;
          l->leutott_szin = ideiglenes_hova_szin;
     } else {
          l->leutott_babu = '-';
          l->leutott_szin = '-';
     }
     l->elozo = lepes;
     
     lepes = l;

     return 1;
}

void elozo_lepesek_kiir(Lepes* l, int szamol) {
     if (szamol < 5 && l != NULL) {
          elozo_lepesek_kiir(l->elozo, szamol + 1);
          printf("%c%d->%c%d   ", oszlopok[l->honnan_y], 8 - l->honnan_x, oszlopok[l->hova_y], 8 - l->hova_x);
     }
}

//megjeleníti az aktuális táblát és a navigációkat
void aktualis_megjelenit(Mezo* m) {
     system("cls");
     printf("Utolsó 5 lépés:   ");
     elozo_lepesek_kiir(lepes, 0);
     printf("\n\n    ");
     for (int i = 0; i < 8; i++) {
          printf("%c   ", oszlopok[i]);
     }
     printf("\n");
     
     int szamol = 0;
     for(int i = 0; i < 17; i++) {
          if (i % 2 == 0) {
               printf("  ");
               for (int i = 0; i < 8; i++) {
                    printf("+---");
               }
               printf("+");
          } else {
               printf("%d |", 8 - szamol);
               for(int j = 0; j < 8; j++) {
                    printf(" %s |", baburakonvertal(m->babu, m->szin));
                    m++;
               }
               szamol++;
          }
          printf("\n");
     }
     printf("\n1. Jatek mentese\n2. Visszalepes\n\n9. Kilepes\n\n");
}

//visszaállítja az előző lépésre a sakktáblát
void visszalepes() {
     char ideiglenes_babu = tabla[lepes->honnan_x][lepes->honnan_y].babu;
     char ideiglenes_szin = tabla[lepes->honnan_x][lepes->honnan_y].babu;

     tabla[lepes->honnan_x][lepes->honnan_y].babu = tabla[lepes->hova_x][lepes->hova_y].babu;
     tabla[lepes->honnan_x][lepes->honnan_y].szin = tabla[lepes->hova_x][lepes->hova_y].szin;

     if (lepes->leutott_babu != '-') {
          tabla[lepes->hova_x][lepes->hova_y].babu = lepes->leutott_babu;
          tabla[lepes->hova_x][lepes->hova_y].szin = lepes->leutott_szin;
     } else {
          tabla[lepes->hova_x][lepes->hova_y].babu = ideiglenes_babu;
          tabla[lepes->hova_x][lepes->hova_y].szin = ideiglenes_szin;
     }

     Lepes* seged = lepes->elozo;
     free(lepes);
     lepes = seged;
     aktualis_megjelenit(&tabla[0][0]);
}

//betölt egy sakktáblát, innen kezdődik a játék
void uj_jatek(int betolte) {
     tabla_betolt();

     int muvelet, x, y, ellenoriz, hanyadik_lepes = 1;
     char sor, oszlop, valasz, jatekos = 'w';
     while(muvelet != 9) {
          egy_lepes(muvelet, x, y, ellenoriz, hanyadik_lepes, betolte, sor, oszlop, valasz, jatekos);
     }
     printf("Elmenti a jatekot?: ");
     valasz = getchar();
     if (valasz == 'i') jatek_mentese;
     while (lepes != NULL) {
          Lepes *seged = lepes->elozo;
          free(lepes);
          lepes = seged;
     }
}

//egy lépést valósít meg
void egy_lepes(int muvelet, int x, int y, int ellenoriz, int hanyadik_lepes, int betolte, char sor, char oszlop, char valasz, char jatekos) {
     char bemenet[5];
     if (jatekos == 'w') printf("Feher");
          else printf("Fekete");
          printf(" jatekos: ");
          if (betolte == 0) {
               gets(bemenet);
          } else if (betolte == 1) {

          }
          if (sscanf(bemenet, "%c%d %c%d", &sor, &x, &oszlop, &y) == 4) {
               if (helyesxy(&x, &y) && helyes_sor_oszlop(&sor, &oszlop)) {
                    ellenoriz = pozicio_cserel(&tabla[7 - (x - 1)][betubol_szamra_konvertal(&sor)],
                         &tabla[7 - (y - 1)][betubol_szamra_konvertal(&oszlop)], jatekos);
                    if (ellenoriz == 0) {
                              if (jatekos == 'w') {
                                   printf("A feher jatekos kovetkezik!\n");
                              } else if (jatekos == 'b') {
                                   printf("A fekete jatekos kovetkezik!\n");
                              }
                    } else if (ellenoriz == 2) {
                         hibauzenet("lepest");
                    } else if (ellenoriz == 1) {
                         if (jatekos == 'w') jatekos = 'b';
                         else jatekos = 'w';
                         aktualis_megjelenit(&tabla[0][0]);
                    }
               } else {
                    hibauzenet("bemeneti erteket");
               }
               ++hanyadik_lepes;
          } else if (sscanf(bemenet, "%d", &muvelet) == 1) {
               if (muvelet == 2) {
                    if (hanyadik_lepes != 1) {
                         visszalepes();
                         if (jatekos == 'w') jatekos = 'b';
                         else jatekos = 'w';
                         --hanyadik_lepes;
                    } else {
                         aktualis_megjelenit(&tabla[0][0]);
                         printf("Nem lehet visszalépni!\n\n");
                    }
               } else if (muvelet == 1) {
                    jatek_mentese();
               }
          } else if (muvelet != 2 && muvelet != 9) {
               aktualis_megjelenit(&tabla[0][0]);
               hibauzenet("bemeneti erteket");
          }
}

//betölt egy üres táblát
void tabla_betolt() {
     //tábla feltöltése
     for(int i = 0; i < 8; i++) {
          for(int j = 0; j < 8; j++) {
               tabla[i][j].x = i;
               tabla[i][j].y = j;
               //a paraszt bábuk beállítása
               tabla[i][j].babu = '-';
               tabla[i][j].szin = '-';

               if (i == 1) {
                    tabla[i][j].babu = 'p';
                    tabla[i][j].szin = 'b';
               }

               if (i == 6) {
                    tabla[i][j].babu = 'p';
                    tabla[i][j].szin = 'w';
               }
          }
     }

     //fekete bábuk beállítása, a parasztokon kívül
     tabla[0][0].babu = 'r';
     tabla[0][1].babu = 'h';
     tabla[0][2].babu = 'b';
     tabla[0][3].babu = 'q';
     tabla[0][4].babu = 'k';
     tabla[0][5].babu = 'b';
     tabla[0][6].babu = 'h';
     tabla[0][7].babu = 'r';

     //fehér bábuk beállítása, a parasztokon kívül
     tabla[7][0].babu = 'r';
     tabla[7][1].babu = 'h';
     tabla[7][2].babu = 'b';
     tabla[7][3].babu = 'q';
     tabla[7][4].babu = 'k';
     tabla[7][5].babu = 'b';
     tabla[7][6].babu = 'h';
     tabla[7][7].babu = 'r';

     for(int i = 0; i < 8; i++) {
          tabla[0][i].szin = 'b';
          tabla[7][i].szin = 'w';
     }

     feher_kiraly = &tabla[7][4];
     fekete_kiraly = &tabla[0][4];
}

//menti az aktuális játékot
void jatek_mentese() {
     FILE* mentes;
}

//betölt egy elmentett sakkjátszmát
void *jatek_betolt(int* navigal) {
     FILE *jatszma;
     char jatek[50];

     printf("Melyik játékot szeretné megnyitni?: ");
     scanf("%s", jatek);

     jatszma = fopen(jatek, "r");
     if (jatszma == NULL) {
          printf("Nincs ilyen fájl");
          menu(navigal);
     }

     fseek(jatszma, 0, SEEK_END);
     int length = ftell(jatszma);
     fseek(jatszma, 0, SEEK_SET); //a fájl elejére visszük vissza a pointert

     char *string = malloc(sizeof(char) * (length + 1));

     char c;
     int szamol = 0;

     while ((c = fgetc(jatszma)) != EOF) {
          string[szamol] = c;
          szamol++;
     }

     string[szamol] = '\0';
     printf("\n%s\n\n",string);

     for(int i = 4; i <= szamol; i += 5) {
               Lepes *l;
               l = (Lepes*) malloc(sizeof(Lepes));
               l->honnan_x = karakterbol_szamra_konvertal(string[i - 4]);
               l->honnan_y = karakterbol_szamra_konvertal(string[i - 3]);
               l->hova_x = karakterbol_szamra_konvertal(string[i - 2]);
               l->hova_y = karakterbol_szamra_konvertal(string[i - 1]);

               l->elozo = lepes;
               
               lepes = l;
     }
     
     elozo_lepesek_kiir(lepes, 0);
     printf("\n%d", lepes->honnan_x);

     while (lepes != NULL) {
          Lepes *seged = lepes->elozo;
          free(lepes);
          lepes = seged;
     }

     free(string);
     fclose(jatszma);
}

//megjeleníti a használati útmutatót, megjeleníti a programmal kapcsolatos tudnivalókat
void hasznalati_utmutato(int* navigal) {
     printf("- Sakk -\n\n- Leptetes\n");
     printf("Ket bemeneti erteket kell beirni (ketto darab koordinatat) a babuk leptetesehez egy jatszmaban. ");
     printf("Az elso az a pozicio amelyik helyrol szeretnenk leptetni a babunkat, ");
     printf("a masodik azt a koordinatat jelenti, ahova leptetni szeretnenk a kivalasztott babut.");
     printf("\nA koordinatak ketto karakterbol allnak, az elso a karakter egy betu (A-H), a masodik egy szam (1-8). ");
     printf("A betuknel kis es nagybetu is elfogadott.");
     printf("\nHa helytelen lepest adott meg, ellenőrizze, hogy mit rontott el es ujra adja meg a koordinatakat.");
     printf("\nHa rossz ertekeket irt be es javitani szeretne a lepeset, a visszalepes lehetoseget hasznalhatja, ");
     printf("\n a visszalepest meg kell erositeni.");
     printf("Hibas lepes eseten jelez a program.");
     printf("\n\n- Betoltes\n");
     printf("Ha be szeretne tolteni egy jatszmat, a jatszma nevet kell beirnia a kiterjesztesevel egyutt ");
     printf("(a kiterjesztes txt) peldaul: jatszma.txt");

     printf("\n\n9. Vissza a menube\n\nValasztas: ");
     scanf("%d", navigal);
     if (*navigal != 9) {
          hibauzenet("erteket");
          printf("9. Vissza a menube\n\nValasztas: ");
          scanf("%d", navigal);
          system("cls");
     }
     system("cls");
     menu(navigal);
}

//ez a metódus kilép a programból
void kilepes() {
     exit(0);
}

//hibaüzenetet ír a felhasználónak, visszajelzést ad, ha helytelen bemeneti értéket adott meg a felhasználó
void hibauzenet(char *uzenet) {
     printf("Kerem ervenyes %s adjon meg!\n\n", uzenet);
}

//amikor betölt a program ez a metódus fut le először, ez a metódus a menüt jelenti, itt dönti el a felhasználó,
//hogy mit szeretne a programon belül csinálni, ez a metódus a felhasználó által választott metódust hívja meg
void menu(int* navigal) {
     printf("- Sakk -\n\n1. Uj jatek\n2. Jatek betoltese\n3. Hasznalati utmutato\n\n9. Kilepes\n\n");
     printf("Valasztas: ");
     scanf("%d", navigal);
     printf("\n\n%d\n\n", *navigal);
     switch (*navigal) {
          case 1:
               system("cls");
               uj_jatek(0);
               break;
          case 2:
               system("cls");
               jatek_betolt(navigal);
               break;
          case 3:
               system("cls");
               hasznalati_utmutato(navigal);
               break;
          case 9:
               kilepes();
               break;
          default:
               system("cls");
               hibauzenet("erteket");
               menu(navigal);
     }
}

int main(void) {
     int navigal;
     menu(&navigal);
}