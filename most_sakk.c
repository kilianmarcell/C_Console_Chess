#include <stdio.h>
#include <stdlib.h>
#include "mezo.h"
#include "lepes.h"
#include "debugmalloc.h"

void menu(int* navigal);
void jatek_betolt(int* navigal);
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

int oda_tud_e_lepni_seged(Mezo* m, char szin);
int kiraly_tud_e_lepni(Mezo* m);
int lepes_ellenorzes(Mezo* honnan, Mezo* hova, char szin);
void paraszt_cserelese(Mezo* m);
int volt_e_paraszt_csere();

void elozo_lepesek_kiir(Lepes* l, int szamol);
int lepesek_megszamolasa(Lepes* l, int ossz);
void tabla_betolt();
int egy_lepes(char *betolt_e, int betolt_vege);
void jatek_mentese();
void fajlbair(FILE* mentes, Lepes* lepes);

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
     if (jobbra_fel_ellenoriz(&tabla[feher->x - 1][feher->y + 1], 'w')) return 1;
     if (jobbra_fel_ellenoriz(&tabla[fekete->x - 1][fekete->y + 1], 'b')) return 2;

     if (jobbra_le_ellenoriz(&tabla[feher->x + 1][feher->y + 1], 'w')) return 1;
     if (jobbra_le_ellenoriz(&tabla[fekete->x + 1][fekete->y + 1], 'b')) return 2;

     if (balra_fel_ellenoriz(&tabla[feher->x - 1][feher->y - 1], 'w')) return 1;
     if (balra_fel_ellenoriz(&tabla[fekete->x - 1][fekete->y - 1], 'b')) return 2;

     if (balra_le_ellenoriz(&tabla[feher->x + 1][feher->y - 1], 'w')) return 1;
     if (balra_le_ellenoriz(&tabla[fekete->x + 1][fekete->y - 1], 'b')) return 2;

     //egyenes lépések
     if (egyenesen_fel_ellenoriz(&tabla[feher->x - 1][feher->y], 'w')) return 1;
     if (egyenesen_fel_ellenoriz(&tabla[fekete->x - 1][fekete->y], 'b')) return 2;

     if (egyenesen_le_ellenoriz(&tabla[feher->x + 1][feher->y], 'w')) return 1;
     if (egyenesen_le_ellenoriz(&tabla[fekete->x + 1][fekete->y], 'b')) return 2;

     if (egyenesen_jobbra_ellenoriz(&tabla[feher->x][feher->y + 1], 'w')) return 1;
     if (egyenesen_jobbra_ellenoriz(&tabla[fekete->x][fekete->y + 1], 'b')) return 2;

     if (egyenesen_balra_ellenoriz(&tabla[feher->x][feher->y - 1], 'w')) return 1;
     if (egyenesen_balra_ellenoriz(&tabla[fekete->x][fekete->y - 1], 'b')) return 2;

     //ló lépések
     if (lo_van_e(feher) == 1) return 1;
     if (lo_van_e(fekete) == 1) return 2;

     //paraszt lépések
     if (paraszt_van_e(feher) == 1) return 1;
     if (paraszt_van_e(fekete) == 1) return 2;

     return 0;
}

int oda_tud_e_lepni_seged(Mezo* m, char szin) {
     if (jobbra_fel_ellenoriz(&tabla[m->x - 1][m->y + 1], szin)) return 1;
     if (jobbra_le_ellenoriz(&tabla[m->x + 1][m->y + 1], szin)) return 1;
     if (balra_fel_ellenoriz(&tabla[m->x - 1][m->y - 1], szin)) return 1;
     if (balra_le_ellenoriz(&tabla[m->x + 1][m->y - 1], szin)) return 1;

     if (egyenesen_fel_ellenoriz(&tabla[m->x - 1][m->y], szin)) return 1;
     if (egyenesen_le_ellenoriz(&tabla[m->x + 1][m->y], szin)) return 1;
     if (egyenesen_jobbra_ellenoriz(&tabla[m->x][m->y + 1], szin)) return 1;
     if (egyenesen_balra_ellenoriz(&tabla[m->x][m->y - 1], szin)) return 1;

     if (lo_van_e(m) == 1) return 1;

     if (paraszt_van_e(m) == 1) return 1;

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
                    if (honnan->x == hova->x + 1 && hova->babu == '-') {
                         if (hova->x == 0) {
                              return 2; //ha a paraszt beért az ellenfél oldalára
                         }
                         return 1;
                    }
                    else if (honnan->x == 6 && honnan->x == hova->x + 2 && tabla[hova->x][hova->y].babu == '-') return 1;
                    else return 0;
               } else if (honnan->x == hova->x + 1 && (honnan->y == hova->y + 1 || honnan->y == hova->y - 1)) {
                    if (hova->szin == ellenkezoszin) return 1;
                    if (hova->x == 0) {
                         return 2;
                    }
                    if (lepes->honnan_x == 1 && lepes->hova_x == 3 && lepes->hova_y == hova->y &&
                    tabla[lepes->hova_x][lepes->hova_y].babu == 'p') {
                         if (honnan->x == 3 && tabla[3][hova->y].babu == 'p' &&
                         tabla[3][hova->y].szin == ellenkezoszin) {
                              tabla[3][hova->y].szin = '-';
                              tabla[3][hova->y].babu = '-';
                              return 4; //en passant
                         }
                    }
               }
          } else if (honnan->szin == 'b') {
               if (honnan->y == hova->y) {
                    if (honnan->x == hova->x - 1 && hova->babu == '-') {
                         if (hova->x == 7) {
                              return 2; //ha a paraszt beért az ellenfél oldalára
                         }
                         return 1;
                    }
                    else if (honnan->x == 1 && honnan->x == hova->x - 2 && tabla[hova->x][hova->y].babu == '-') return 1;
                    else return 0;
               } else if (honnan->x == hova->x - 1 && (honnan->y == hova->y + 1 || honnan->y == hova->y - 1)) {
                    if (hova->szin == ellenkezoszin) return 1;
                    if (hova->x == 7) {
                         return 2;
                    }
                    if (lepes->honnan_x == 6 && lepes->hova_x == 4 && lepes->hova_y == hova->y &&
                    tabla[lepes->hova_x][lepes->hova_y].babu == 'p') {
                         if (honnan->x == 4 && tabla[4][hova->y].babu == 'p' &&
                         tabla[4][hova->y].szin == ellenkezoszin) {
                              tabla[4][hova->y].szin = '-';
                              tabla[4][hova->y].babu = '-';
                              return 4; //en passant
                         }
                    }
               }
          }
          return 0;
     }

     //bástya lépésének ellenőrzése
     if (honnan->babu == 'r') {
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
          if (honnan->y == hova->y - 2) {
               if (tabla[honnan->x][honnan->y + 1].babu == '-' && tabla[honnan->x][honnan->y + 2].babu == '-' &&
               tabla[honnan->x][honnan->y + 3].babu == 'r') {
                    Lepes* seged = lepes;
                    while (seged != NULL) {
                         if (seged->honnan_x == honnan->x && (seged->honnan_y == honnan->y + 3 || seged->honnan_y == honnan->y)) return 0;
                         seged = seged->elozo;
                    }
                    return 5; //sáncolás
               }
          } else if (honnan->y == hova->y + 2) {
               if (tabla[honnan->x][honnan->y - 1].babu == '-' && tabla[honnan->x][honnan->y - 2].babu == '-' &&
               tabla[honnan->x][honnan->y - 3].babu == '-' && tabla[honnan->x][honnan->y - 4].babu == 'r') {
                    Lepes* seged = lepes;
                    while (seged != NULL) {
                         if (seged->honnan_x == honnan->x && (seged->honnan_y == honnan->y - 4 || seged->honnan_y == honnan->y)) return 0;
                         seged = seged->elozo;
                    }
                    return 5; //sáncolás
               }
          }
          if (kiraly_lepes(honnan, hova)) {
               if (honnan->szin == 'w') feher_kiraly = honnan;
               else fekete_kiraly = honnan;
               return 1;
          }

          return 0;
     }

     return 0;
}

//a paraszt bábu cserélését valósítja meg
void paraszt_cserelese(Mezo* m) {
     char melyik = 'a';
     printf("\nMilyen bábura váltasz? (q = királynő, r = bástya, b = futó, h = ló) ");
     scanf("%c", &melyik);
     scanf("%c", &melyik);
     switch (melyik) {
     case 'q':
          m->babu = 'q';
          break;
     case 'r':
          m->babu = 'r';
          break;
     case 'b':
          m->babu = 'b';
          break;
     case 'h':
          m->babu = 'h';
          break;
     }
}

int kiraly_tud_e_lepni(Mezo* m) {
     if (tablan_belul_van_e(m->x - 1, m->y)) {
          if (tabla[m->x - 1][m->y].szin != m->szin &&
          oda_tud_e_lepni_seged(&tabla[m->x - 1][m->y], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }
     if (tablan_belul_van_e(m->x - 1, m->y + 1)) {
          if (tabla[m->x - 1][m->y + 1].szin != m->szin &&
          oda_tud_e_lepni_seged(&tabla[m->x - 1][m->y + 1], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }
     if (tablan_belul_van_e(m->x, m->y + 1)) {
          if (tabla[m->x][m->y + 1].szin != m->szin &&
          oda_tud_e_lepni_seged(&tabla[m->x][m->y + 1], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }
     if (tablan_belul_van_e(m->x + 1, m->y + 1)) {
          if (tabla[m->x + 1][m->y + 1].szin != m->szin &&
          oda_tud_e_lepni_seged(&tabla[m->x + 1][m->y + 1], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }
     if (tablan_belul_van_e(m->x + 1, m->y)) {
          if (tabla[m->x + 1][m->y].szin != m->szin &&
          oda_tud_e_lepni_seged(&tabla[m->x + 1][m->y], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }
     if (tablan_belul_van_e(m->x + 1, m->y - 1)) {
          if (tabla[m->x + 1][m->y - 1].szin != m->szin &&
          oda_tud_e_lepni_seged(&tabla[m->x + 1][m->y - 1], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }
     if (tablan_belul_van_e(m->x, m->y - 1)) {
          if (tabla[m->x][m->y - 1].szin != m->szin &&
          oda_tud_e_lepni_seged(&tabla[m->x][m->y - 1], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }
     if (tablan_belul_van_e(m->x - 1, m->y - 1)) {
          if (tabla[m->x - 1][m->y - 1].szin != m->szin &&
          oda_tud_e_lepni_seged(&tabla[m->x - 1][m->y - 1], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }

     return 0;
}

//kettő mezőt megcserél
int pozicio_cserel(Mezo* honnan, Mezo* hova, char szin) {
     int ervenytelenlepes = 0, lepesellenorzo = lepes_ellenorzes(honnan, hova, szin);
     char ideiglenes_honnan_babu = honnan->babu, ideiglenes_honnan_szin = honnan->szin;
     char ideiglenes_hova_babu = hova->babu, ideiglenes_hova_szin = hova->szin;
     
     if (honnan->babu == '-' || honnan->szin != szin) return 0; //ha nem a soron lévő játkos lép akkor 0-t ad vissza
     if (hova->szin == szin || lepesellenorzo == 0) return 2; //ha nem szabályosan lép a játékos 2-t ad vissza
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

     //sakk ellenőrzése
     int sakke = sakk_ellenoriz(feher_kiraly, fekete_kiraly);
     if (sakke == 1) {
          int matt_e = 0;

          if (kiraly_tud_e_lepni(feher_kiraly) == 0) {
               //átlós lépések
               if (jobbra_fel_ellenoriz(&tabla[feher_kiraly->x - 1][feher_kiraly->y + 1], 'w')) {
                    Mezo* seged = &tabla[feher_kiraly->x - 1][feher_kiraly->y + 1];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'b')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->x - 1 >= 0 && seged->y + 1 <= 7) seged = &tabla[seged->x - 1][seged->y + 1];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }
               
               if (jobbra_le_ellenoriz(&tabla[feher_kiraly->x + 1][feher_kiraly->y + 1], 'w')) {
                    Mezo* seged = &tabla[feher_kiraly->x + 1][feher_kiraly->y + 1];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'b')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->x + 1 <= 7 && seged->y + 1 <= 7) seged = &tabla[seged->x + 1][seged->y + 1];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }

               if (balra_fel_ellenoriz(&tabla[feher_kiraly->x - 1][feher_kiraly->y - 1], 'w')) {
                    Mezo* seged = &tabla[feher_kiraly->x - 1][feher_kiraly->y - 1];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'b')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->x - 1 >= 0 && seged->y - 1 >= 0) seged = &tabla[seged->x - 1][seged->y - 1];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }

               if (balra_le_ellenoriz(&tabla[feher_kiraly->x + 1][feher_kiraly->y - 1], 'w')) {
                    Mezo* seged = &tabla[feher_kiraly->x + 1][feher_kiraly->y - 1];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'b')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->x + 1 <= 7 && seged->y - 1 >= 0) seged = &tabla[seged->x + 1][seged->y - 1];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }

               //egyenes lépések
               if (egyenesen_fel_ellenoriz(&tabla[feher_kiraly->x - 1][feher_kiraly->y], 'w')) {
                    Mezo* seged = &tabla[feher_kiraly->x - 1][feher_kiraly->y];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'b')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->x - 1 >= 0) seged = &tabla[seged->x - 1][seged->y];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }

               if (egyenesen_le_ellenoriz(&tabla[feher_kiraly->x + 1][feher_kiraly->y], 'w')) {
                    Mezo* seged = &tabla[feher_kiraly->x + 1][feher_kiraly->y];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'b')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->x + 1 <= 7) seged = &tabla[seged->x + 1][seged->y];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }

               if (egyenesen_jobbra_ellenoriz(&tabla[feher_kiraly->x][feher_kiraly->y + 1], 'w')) {
                    Mezo* seged = &tabla[feher_kiraly->x][feher_kiraly->y + 1];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'b')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->y + 1 <= 7) seged = &tabla[seged->x][seged->y + 1];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }

               if (egyenesen_balra_ellenoriz(&tabla[feher_kiraly->x][feher_kiraly->y - 1], 'w')) {
                    Mezo* seged = &tabla[feher_kiraly->x][feher_kiraly->y - 1];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'b')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->y - 1 >= 0) seged = &tabla[seged->x][seged->y - 1];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }

               //ló lépések
               if (lo_van_e(feher_kiraly) == 1) {
                    if (tablan_belul_van_e(feher_kiraly->x - 1, feher_kiraly->y + 2)) {
                         if (tabla[feher_kiraly->x - 1][feher_kiraly->y + 2].babu == 'h' &&
                              tabla[feher_kiraly->x - 1][feher_kiraly->y + 2].szin != feher_kiraly->szin &&
                              oda_tud_e_lepni_seged(&tabla[feher_kiraly->x - 1][feher_kiraly->y + 2], 'b') == 0) matt_e = 1;
                    }
                    if (tablan_belul_van_e(feher_kiraly->x - 1, feher_kiraly->y - 2)) {
                         if (tabla[feher_kiraly->x - 1][feher_kiraly->y - 2].babu == 'h' &&
                              tabla[feher_kiraly->x - 1][feher_kiraly->y - 2].szin != feher_kiraly->szin &&
                              oda_tud_e_lepni_seged(&tabla[feher_kiraly->x - 1][feher_kiraly->y - 2], 'b') == 0) matt_e = 1;
                    }
                    if (tablan_belul_van_e(feher_kiraly->x - 2, feher_kiraly->y + 1)) {
                         if (tabla[feher_kiraly->x - 2][feher_kiraly->y + 1].babu == 'h' &&
                              tabla[feher_kiraly->x - 2][feher_kiraly->y + 1].szin != feher_kiraly->szin &&
                              oda_tud_e_lepni_seged(&tabla[feher_kiraly->x - 2][feher_kiraly->y + 1], 'b') == 0) matt_e = 1;
                    }
                    if (tablan_belul_van_e(feher_kiraly->x - 2, feher_kiraly->y - 1)) {
                         if (tabla[feher_kiraly->x - 2][feher_kiraly->y - 1].babu == 'h' &&
                              tabla[feher_kiraly->x - 2][feher_kiraly->y - 1].szin != feher_kiraly->szin &&
                              oda_tud_e_lepni_seged(&tabla[feher_kiraly->x - 2][feher_kiraly->y - 1], 'b') == 0) matt_e = 1;
                    }
                    if (tablan_belul_van_e(feher_kiraly->x + 1, feher_kiraly->y + 2)) {
                         if (tabla[feher_kiraly->x + 1][feher_kiraly->y + 2].babu == 'h' &&
                              tabla[feher_kiraly->x + 1][feher_kiraly->y + 2].szin != feher_kiraly->szin &&
                              oda_tud_e_lepni_seged(&tabla[feher_kiraly->x + 1][feher_kiraly->y + 2], 'b') == 0) matt_e = 1;
                    }
                    if (tablan_belul_van_e(feher_kiraly->x + 1, feher_kiraly->y - 2)) {
                         if (tabla[feher_kiraly->x + 1][feher_kiraly->y - 2].babu == 'h' &&
                              tabla[feher_kiraly->x + 1][feher_kiraly->y - 2].szin != feher_kiraly->szin &&
                              oda_tud_e_lepni_seged(&tabla[feher_kiraly->x + 1][feher_kiraly->y - 2], 'b') == 0) matt_e = 1;
                    }
                    if (tablan_belul_van_e(feher_kiraly->x + 2, feher_kiraly->y + 1)) {
                         if (tabla[feher_kiraly->x + 2][feher_kiraly->y + 1].babu == 'h' &&
                              tabla[feher_kiraly->x + 2][feher_kiraly->y + 1].szin != feher_kiraly->szin &&
                              oda_tud_e_lepni_seged(&tabla[feher_kiraly->x + 2][feher_kiraly->y + 1], 'b') == 0) matt_e = 1;
                    }
                    if (tablan_belul_van_e(feher_kiraly->x + 2, feher_kiraly->y - 1)) {
                         if (tabla[feher_kiraly->x + 2][feher_kiraly->y - 1].babu == 'h' &&
                              tabla[feher_kiraly->x + 2][feher_kiraly->y - 1].szin != feher_kiraly->szin &&
                              oda_tud_e_lepni_seged(&tabla[feher_kiraly->x + 2][feher_kiraly->y - 1], 'b') == 0) matt_e = 1;
                    }
               }

               if (paraszt_van_e(feher_kiraly) == 1) {
                    if (tabla[feher_kiraly->x - 1][feher_kiraly->y + 1].babu == 'p' &&
                         tabla[feher_kiraly->x - 1][feher_kiraly->y + 1].szin == 'b'&&
                         oda_tud_e_lepni_seged(&tabla[feher_kiraly->x - 1][feher_kiraly->y + 1], 'b') == 0) matt_e = 1;
                    if (tabla[feher_kiraly->x - 1][feher_kiraly->y - 1].babu == 'p' &&
                         tabla[feher_kiraly->x - 1][feher_kiraly->y - 1].szin == 'b' &&
                         oda_tud_e_lepni_seged(&tabla[feher_kiraly->x - 1][feher_kiraly->y - 1], 'b') == 0) matt_e = 1;
               }
          }
          
          if (matt_e == 1) return 4;
     } else if (sakke == 2) {
          int matt_e = 0;

          if (kiraly_tud_e_lepni(feher_kiraly) == 0) {
               //átlós lépések
               if (jobbra_fel_ellenoriz(&tabla[fekete_kiraly->x - 1][fekete_kiraly->y + 1], 'b')) {
                    Mezo* seged = &tabla[fekete_kiraly->x - 1][fekete_kiraly->y + 1];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'w')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->x - 1 >= 0 && seged->y + 1 <= 7) seged = &tabla[seged->x - 1][seged->y + 1];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }
               
               if (jobbra_le_ellenoriz(&tabla[fekete_kiraly->x + 1][fekete_kiraly->y + 1], 'b')) {
                    Mezo* seged = &tabla[fekete_kiraly->x + 1][fekete_kiraly->y + 1];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'w')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->x + 1 <= 7 && seged->y + 1 <= 7) seged = &tabla[seged->x + 1][seged->y + 1];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }

               if (balra_fel_ellenoriz(&tabla[fekete_kiraly->x - 1][fekete_kiraly->y - 1], 'b')) {
                    Mezo* seged = &tabla[fekete_kiraly->x - 1][fekete_kiraly->y - 1];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'w')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->x - 1 >= 0 && seged->y - 1 >= 0) seged = &tabla[seged->x - 1][seged->y - 1];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }

               if (balra_le_ellenoriz(&tabla[fekete_kiraly->x + 1][fekete_kiraly->y - 1], 'b')) {
                    Mezo* seged = &tabla[fekete_kiraly->x + 1][fekete_kiraly->y - 1];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'w')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->x + 1 <= 7 && seged->y - 1 >= 0) seged = &tabla[seged->x + 1][seged->y - 1];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }

               //egyenes lépések
               if (egyenesen_fel_ellenoriz(&tabla[feher_kiraly->x - 1][feher_kiraly->y], 'w')) {
                    Mezo* seged = &tabla[feher_kiraly->x - 1][feher_kiraly->y];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'b')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->x - 1 >= 0) seged = &tabla[seged->x - 1][seged->y];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }
               
               if (egyenesen_le_ellenoriz(&tabla[feher_kiraly->x + 1][feher_kiraly->y], 'w')) {
                    Mezo* seged = &tabla[feher_kiraly->x + 1][feher_kiraly->y];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'b')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->x + 1 <= 7) seged = &tabla[seged->x + 1][seged->y];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }

               if (egyenesen_jobbra_ellenoriz(&tabla[feher_kiraly->x][feher_kiraly->y + 1], 'w')) {
                    Mezo* seged = &tabla[feher_kiraly->x][feher_kiraly->y + 1];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'b')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->y + 1 <= 7) seged = &tabla[seged->x][seged->y + 1];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }

               if (egyenesen_balra_ellenoriz(&tabla[feher_kiraly->x][feher_kiraly->y - 1], 'w')) {
                    Mezo* seged = &tabla[feher_kiraly->x][feher_kiraly->y - 1];
                    int vege = 0, kell_e_tovabb_ellenorizni = 1;
                    while (vege != 1 && kell_e_tovabb_ellenorizni != 0) {
                         if (oda_tud_e_lepni_seged(&tabla[seged->x][seged->y], 'b')) kell_e_tovabb_ellenorizni = 0;
                         else if (seged->babu == '-' && seged->y - 1 >= 0) seged = &tabla[seged->x][seged->y - 1];
                         else vege = 1;
                    }
                    if (kell_e_tovabb_ellenorizni == 1) matt_e = 1;
               }
          }

          if (matt_e == 1) return 4;
     }
     if (sakke == 1 && szin == 'w') ervenytelenlepes = 1;
     else if (sakke == 2 && szin == 'b') ervenytelenlepes = 1;

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

     if (lepesellenorzo == 2) paraszt_cserelese(hova);
     if (lepesellenorzo == 5) {
          if (hova->y == honnan->y + 2) { //jobbra sáncolás
               tabla[hova->x][7].babu = '-';
               tabla[hova->x][7].szin = '-';
               tabla[hova->x][hova->y - 1].babu = 'r';
               tabla[hova->x][hova->y - 1].szin = hova->szin;
          } else if (hova->y == honnan->y - 2) { //balra sáncolás
               tabla[hova->x][0].babu = '-';
               tabla[hova->x][0].szin = '-';
               tabla[hova->x][hova->y + 1].babu = 'r';
               tabla[hova->x][hova->y + 1].szin = hova->szin;
          }
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
          if (lepesellenorzo == 4)  {
               l->leutott_babu = 'p';
               l->leutott_szin = (hova->szin == 'w') ? 'b' : 'w';
          }
     }
     l->elozo = lepes;
     
     lepes = l;

     if (sakke == 1 && szin != 'w') return 3;
     else if (sakke == 2 && szin != 'b') return 3;

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
     // system("cls");
     if (lepesek_megszamolasa(lepes, 0) > 0) {
          printf("Utolsó 5 lépés:   ");
          elozo_lepesek_kiir(lepes, 0);
          printf("\n\n");
     }
     printf("    ");
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

//ez a metódus segí megtalálni, hogy paraszt cserélés volt-e a játszma során
int volt_e_paraszt_csere() {
     Lepes* l_jelenlegi = lepes;
     Lepes* l_elozo = lepes->elozo;
     int sor = 0;
     while (l_elozo != NULL) {
          if (l_jelenlegi->honnan_x == l_elozo->hova_x && l_jelenlegi->honnan_y == l_elozo->hova_y) {
               l_jelenlegi = l_elozo;
               l_elozo = l_elozo->elozo;
               sor = l_jelenlegi->honnan_x;
          }
          l_elozo = l_elozo->elozo;
     }
     
     return sor;
}

//visszaállítja az előző lépésre a sakktáblát
void visszalepes() {
     if (tabla[lepes->hova_x][lepes->hova_y].babu == 'k') {
          if (tabla[lepes->hova_x][lepes->hova_y].szin == 'w') feher_kiraly = &tabla[lepes->honnan_x][lepes->honnan_y];
          if (tabla[lepes->hova_x][lepes->hova_y].szin == 'b') fekete_kiraly = &tabla[lepes->honnan_x][lepes->honnan_y];

          if (lepes->honnan_y == lepes->hova_y - 2) { //ha jobbra sáncolás volt
               tabla[lepes->honnan_x][5].babu = '-';
               tabla[lepes->honnan_x][5].szin = '-';
               tabla[lepes->honnan_x][7].babu = 'r';
               tabla[lepes->honnan_x][7].szin = tabla[lepes->hova_x][lepes->hova_y].szin;
          } else if (lepes->honnan_y == lepes->hova_y + 2) { //ha balra sáncolás volt
               tabla[lepes->honnan_x][3].babu = '-';
               tabla[lepes->honnan_x][3].szin = '-';
               tabla[lepes->honnan_x][0].babu = 'r';
               tabla[lepes->honnan_x][0].szin = tabla[lepes->hova_x][lepes->hova_y].szin;
          }
     }

     if (lepes->honnan_x == 1 && lepes->hova_x == 0) {
          if (volt_e_paraszt_csere() == 6) tabla[lepes->hova_x][lepes->hova_y].babu = 'p';
     }

     if (lepes->honnan_x == 6 && lepes->hova_x == 7) {
          if (volt_e_paraszt_csere() == 1) tabla[lepes->hova_x][lepes->hova_y].babu = 'p';
     }

     //ha fehér paraszt csinált en passant-ot
     if (lepes->leutott_babu == 'p' && lepes->leutott_szin == 'b' && lepes->honnan_x == 3 && lepes->elozo->honnan_x == 1 && lepes->elozo->hova_x == 3) {
          tabla[lepes->elozo->hova_x][lepes->elozo->hova_y].babu = 'p';
          tabla[lepes->elozo->hova_x][lepes->elozo->hova_y].szin = 'b';
          lepes->leutott_babu = '-';
          lepes->leutott_szin = '-';
     }

     //ha fekete paraszt csinált en passant-ot
     if (lepes->leutott_babu == 'p' && lepes->leutott_szin == 'w' && lepes->honnan_x == 4 && lepes->elozo->honnan_x == 6 && lepes->elozo->hova_x == 4) {
          tabla[lepes->hova_x - 1][lepes->hova_y].babu = 'p';
          tabla[lepes->hova_x - 1][lepes->hova_y].szin = 'w';
          lepes->leutott_babu = '-';
          lepes->leutott_szin = '-';
     }

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
void uj_jatek(int* navigal) {
     tabla_betolt();
     if (egy_lepes("-", 0) == 1) {
          menu(navigal);
     }
}

//megszámolja és visszaadja az eddigi lépések számát
int lepesek_megszamolasa(Lepes* l, int ossz) {
     if (l != NULL) {
          ++ossz;
          return lepesek_megszamolasa(l->elozo, ossz);
     }
     return ossz;
}

//egy lépést valósít meg
int egy_lepes(char* betolt_e, int betolt_vege) {
     int muvelet = 0, x, y, ellenoriz, sakk_e = 0;
     char sor, oszlop, jatekos = 'w';
     char bemenet[5];
     if (strcmp(betolt_e, "-") == 0) aktualis_megjelenit(&tabla[0][0]);

     if (betolt_vege == 1) {
          if (lepesek_megszamolasa(lepes, 0) % 2 == 1) jatekos = 'b';
          if (sakk_ellenoriz(feher_kiraly, fekete_kiraly) != 0) sakk_e = 1;
     }

     if (strcmp(betolt_e, "-") == 1) {
          strcpy(bemenet, betolt_e);
          if (lepesek_megszamolasa(lepes, 0) % 2 == 1) jatekos = 'b';
     }

     while(muvelet != 9) {
          if (sakk_e == 1) {
               if (strcmp(betolt_e, "-") == 0) aktualis_megjelenit(&tabla[0][0]);
               printf("Sakk!\n");
               sakk_e = 0;
          }
          if (strcmp(betolt_e, "-") == 0) {
               if (jatekos == 'w') printf("Feher");
               else printf("Fekete");
               printf(" jatekos: ");
               scanf(" %[^\n]s", bemenet);
          }
          if (sscanf(bemenet, "%c%d %c%d", &sor, &x, &oszlop, &y) == 4) {
               if (helyesxy(&x, &y) && helyes_sor_oszlop(&sor, &oszlop)) {
                    ellenoriz = pozicio_cserel(&tabla[7 - (x - 1)][betubol_szamra_konvertal(&sor)],
                         &tabla[7 - (y - 1)][betubol_szamra_konvertal(&oszlop)], jatekos);
                    if (ellenoriz == 0) {
                         if (strcmp(betolt_e, "-") == 1) return 1;
                         if (jatekos == 'w') {
                              printf("A feher jatekos kovetkezik!\n");
                         } else if (jatekos == 'b') {
                              printf("A fekete jatekos kovetkezik!\n");
                         }
                    } else if (ellenoriz == 2) {
                         if (strcmp(betolt_e, "-") == 1) return 0;
                         hibauzenet("lepest");
                    } else if (ellenoriz == 1) {
                         if (jatekos == 'w') jatekos = 'b';
                         else jatekos = 'w';
                         if (strcmp(betolt_e, "-") == 0) aktualis_megjelenit(&tabla[0][0]);
                    } else if (ellenoriz == 3) {
                         if (jatekos == 'w') jatekos = 'b';
                         else jatekos = 'w';
                         sakk_e = 1;
                    } else if (ellenoriz == 4) {
                         printf("\nSakk matt!\n");
                         (jatekos == 'w') ? printf("Fehér játékos nyert!") : printf("Fekete játékos nyert");
                         muvelet = 9;
                    }
               } else {
                    if (strcmp(betolt_e, "-") == 1) return 0;
                    hibauzenet("bemeneti erteket");
               }
          } else if (sscanf(bemenet, "%d", &muvelet) == 1) {
               if (strcmp(betolt_e, "-") == 1) return 0;
               if (muvelet == 2) {
                    if (lepes != NULL) {
                         visszalepes();

                         if (jatekos == 'w') jatekos = 'b';
                         else jatekos = 'w';
                         
                         if (sakk_ellenoriz(feher_kiraly, fekete_kiraly) != 0) {
                              sakk_e = 1;
                              printf("Sakk e=%d\n", sakk_ellenoriz(feher_kiraly, fekete_kiraly));
                         } else {
                              sakk_e = 0;
                         }
                    } else {
                         aktualis_megjelenit(&tabla[0][0]);
                         printf("Nem lehet visszalépni!\n\n");
                    }
               } else if (muvelet == 1) {
                    jatek_mentese();
               }
          } else if (muvelet != 2 && muvelet != 9 && sscanf(bemenet, "%c%d %c%d", &sor, &x, &oszlop, &y) != -1) {
               if (strcmp(betolt_e, "-") == 1) return 0;
               hibauzenet("bemeneti erteket");
          }
     }
     
     printf("Elmenti a jatekot?: ");
     char valasz;
     scanf("%c", &valasz);
     if (valasz == 'i') jatek_mentese();
     
     while (lepes != NULL) {
          Lepes *seged = lepes->elozo;
          free(lepes);
          lepes = seged;
     }

     return 1;
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
     printf("Hova szeretné menteni a játszmát? ");
     char jatek[50];
     scanf(" %[^\n]s", jatek);

     FILE *mentes = fopen(jatek, "w");
     if (mentes == NULL) {
          printf("Sikertelen mentés!");
     }
     
     fajlbair(mentes, lepes);

     printf("\nSikeres mentés!\n");
     fclose(mentes);
}

//helyes sorrendben menti el a lépéseket
void fajlbair(FILE* mentes, Lepes* lepes) {
     if (lepes->elozo != NULL) fajlbair(mentes, lepes->elozo);

     fputc(lepes->honnan_x + '0', mentes);
     fputc(lepes->honnan_y + '0', mentes);
     fputc(lepes->hova_x + '0', mentes);
     fputc(lepes->hova_y + '0', mentes);
     fputc('\n', mentes);
}

//betölt egy elmentett sakkjátszmát
void jatek_betolt(int* navigal) {
     FILE *jatszma;
     char jatek[50];

     printf("Melyik játékot szeretné megnyitni?: ");
     scanf("%s", jatek);

     jatszma = fopen(jatek, "r");
     if (jatszma == NULL) {
          printf("Nincs ilyen fájl");
          menu(navigal);
     }

     tabla_betolt();

     fseek(jatszma, 0, SEEK_END);
     int length = ftell(jatszma);
     fseek(jatszma, 0, SEEK_SET); //a fájl elejére visszük vissza a pointert

     char *beolvasott = malloc(sizeof(char) * (length + 1));

     char c;
     int szamol = 0;

     while ((c = fgetc(jatszma)) != EOF) {
          beolvasott[szamol] = c;
          szamol++;
     }

     beolvasott[szamol] = '\0';
     char bemenet[5];

     for(int i = 4; i <= szamol; i += 5) {
          bemenet[0] = oszlopok[karakterbol_szamra_konvertal(beolvasott[i - 3])];
          bemenet[1] = (8 - karakterbol_szamra_konvertal(beolvasott[i - 4])) + '0';
          bemenet[2] = oszlopok[karakterbol_szamra_konvertal(beolvasott[i - 1])];
          bemenet[3] = (8 - karakterbol_szamra_konvertal(beolvasott[i - 2])) + '0';
          bemenet[4] = '\0';

          if (egy_lepes(bemenet, 0) == 0) {
               while (lepes != NULL) {
                    Lepes *seged = lepes->elozo;
                    free(lepes);
                    lepes = seged;
               }
               free(beolvasott);
               fclose(jatszma);
               system("cls");
               printf("Hibás lépés van ebben a játszmában!\n");
               menu(navigal);
          }
     }
     free(beolvasott);
     fclose(jatszma);
     
     egy_lepes("-", 1);
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
               uj_jatek(navigal);
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