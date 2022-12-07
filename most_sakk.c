#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "mezo.h"
#include "lepes.h"
#include "debugmalloc.h"

void menu();
void jatek_betolt();
void hibauzenet(char *uzenet);
int karakterbol_szamra_konvertal(char c);

//lépéseket ellenőrző metódusok
int lo_lepes(Mezo** tabla, Mezo* jelenlegi, Mezo* hova);

int jobbra_fel_lepes(Mezo** tabla, Mezo* jelenlegi, Mezo* hova);
int jobbra_le_lepes(Mezo** tabla, Mezo* jelenlegi, Mezo* hova);
int balra_fel_lepes(Mezo** tabla, Mezo* jelenlegi, Mezo* hova);
int balra_le_lepes(Mezo** tabla, Mezo* jelenlegi, Mezo* hova);

int egyenes_fel_lepes(Mezo** tabla, Mezo *jelenlegi, Mezo *hova);
int egyenes_le_lepes(Mezo** tabla, Mezo *jelenlegi, Mezo *hova);
int egyenes_jobbra_lepes(Mezo** tabla, Mezo *jelenlegi, Mezo *hova);
int egyenes_balra_lepes(Mezo** tabla, Mezo *jelenlegi, Mezo *hova);

//sakkot ellenőrző metódusok
int jobbra_fel_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin);
int jobbra_le_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin);
int balra_fel_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin);
int balra_le_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin);

int egyenesen_fel_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin);
int egyenesen_le_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin);
int egyenesen_jobbra_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin);
int egyenesen_balra_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin);

int lo_van_e(Mezo** tabla, Mezo* kiraly);

int oda_tud_e_lepni_seged(Mezo** tabla, Mezo* m, char szin);
int kiraly_tud_e_lepni(Mezo** tabla, Mezo* m);
int lepes_ellenorzes(Mezo** tabla, Lepes* lepes, Mezo* honnan, Mezo* hova, char szin);
void paraszt_cserelese(Mezo* m);
int volt_e_paraszt_csere(Lepes* lepes);

Mezo** tabla_betolt();
void aktualis_megjelenit(Mezo** tabla, Lepes* lepes);

Mezo* feher_kiraly_mezo(Mezo** tabla);
Mezo* fekete_kiraly_mezo(Mezo** tabla);

void visszalepes(Mezo** tabla, Lepes* lepes);
void elozo_lepesek_kiir(Lepes* l, int szamol);
int lepesek_megszamolasa(Lepes* l, int ossz);
int pozicio_cserel(Mezo** tabla, Lepes* lepes, Mezo* honnan, Mezo* hova, char szin);
int egy_lepes(Mezo** tabla, Lepes* lepes, char *betolt_e, int betolt_vege);
void jatek_mentese(Lepes* lepes);
void fajlbair(FILE* mentes, Lepes* lepes);

//-------------------------------------------------------------------------------------------------------

//Különböző konvertálások
//ellenőrzi, hogy érvényes sorokat adott-e meg a felhasználó (sakk játszma közben)
int helyesxy(int* x, int* y) {
     return (*x >= 1 && *x <= 8 && *y >= 1 && *y <= 8);
}

//ellenőrzi, hogy érvényes pozíciót adott-e meg a felhasználó (sakk játszma közben)
int helyes_sor_oszlop(char* honnanoszlop, char* hovaoszlop) {
     //a sakktábla oszlopait tárolja a karaktertömb
     char oszlopok[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
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
     //a sakktábla oszlopait tárolja a karaktertömb
     char oszlopok[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
     for(int i = 0; i < 8; i++) {
          if (oszlopok[i] == *betu) return i;
     }

     return 0;
}

//egy bábunak a betűjéből és a színéből előállítja a bábut
char *baburakonvertal(char betu, char szin) {
     //a sakkbábukat tárolja el a "karaktertömb"
     char *babuk[] = { "♔", "♕", "♖", "♗", "♘", "♙", "♚", "♛", "♜", "♝", "♞", "♟︎" };
     //a sakkbábuk betűit tárolja a karaktertömb
     char babubetuk[] = { 'k', 'q', 'r', 'b', 'h', 'p' };
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
int lo_lepes(Mezo** tabla, Mezo* jelenlegi, Mezo* hova) {
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
int kiraly_lepes(Mezo** tabla, Mezo* jelenlegi, Mezo* hova) {
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
int jobbra_fel_lepes(Mezo** tabla, Mezo* jelenlegi, Mezo* hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->x - 1 >= 0 && jelenlegi->y + 1 <= 7) {
               return jobbra_fel_lepes(tabla, &tabla[jelenlegi->x - 1][jelenlegi->y + 1], hova);
          }
     }

     return 0;
}

//egy bábunak a jobbra lefele átlós lépését ellenőrzi
int jobbra_le_lepes(Mezo** tabla, Mezo* jelenlegi, Mezo* hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->x + 1 >= 0 && jelenlegi->y + 1 <= 7) {
               return jobbra_le_lepes(tabla, &tabla[jelenlegi->x + 1][jelenlegi->y + 1], hova);
          }
     }

     return 0;
}

//egy bábunak a balra felfele átlós lépését ellenőrzi
int balra_fel_lepes(Mezo** tabla, Mezo* jelenlegi, Mezo* hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->x - 1 >= 0 && jelenlegi->y - 1 <= 7) {
               return balra_fel_lepes(tabla, &tabla[jelenlegi->x - 1][jelenlegi->y - 1], hova);
          }
     }

     return 0;
}

//egy bábunak a balra lefele átlós lépését ellenőrzi
int balra_le_lepes(Mezo** tabla, Mezo* jelenlegi, Mezo* hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->x + 1 >= 0 && jelenlegi->y - 1 <= 7) {
               return balra_le_lepes(tabla, &tabla[jelenlegi->x + 1][jelenlegi->y - 1], hova);
          }
     }

     return 0;
}

//átlós lépések ellenőrzése
int atlosan_jo_e(Mezo** tabla, Mezo* honnan, Mezo* hova) {
     if (honnan->x - 1 >= 0 && honnan->y + 1 <= 7) {
          if (jobbra_fel_lepes(tabla, &tabla[honnan->x - 1][honnan->y + 1], hova)) return 1;
     }
     if (honnan->x + 1 <= 7 && honnan->y + 1 <= 7) {
          if (jobbra_le_lepes(tabla, &tabla[honnan->x + 1][honnan->y + 1], hova)) return 1;
     }
     if (honnan->x - 1 >= 0 && honnan->y - 1 >= 0) {
          if (balra_fel_lepes(tabla, &tabla[honnan->x - 1][honnan->y - 1], hova)) return 1;
     }
     if (honnan->x + 1 <= 7 && honnan->y - 1 >= 0) {
          if (balra_le_lepes(tabla, &tabla[honnan->x + 1][honnan->y - 1], hova)) return 1;
     }
     
     return 0;
}

//egyenes lépések
//az egyenesen felfele lépés helyességét ellenőrzi a metódus
int egyenes_fel_lepes(Mezo** tabla, Mezo *jelenlegi, Mezo *hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->x - 1 >= 0) {
               return egyenes_fel_lepes(tabla, &tabla[jelenlegi->x - 1][jelenlegi->y], hova);
          }
     }

     return 0;
}

//az egyenesen lefele lépés helyességét ellenőrzi a metódus
int egyenes_le_lepes(Mezo** tabla, Mezo *jelenlegi, Mezo *hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->x + 1 <= 7) {
               return egyenes_le_lepes(tabla, &tabla[jelenlegi->x + 1][jelenlegi->y], hova);
          }
     }

     return 0;
}

//az egyenesen jobbra lépés helyességét ellenőrzi a metódus
int egyenes_jobbra_lepes(Mezo** tabla, Mezo *jelenlegi, Mezo *hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->y + 1 <= 7) {
               return egyenes_jobbra_lepes(tabla, &tabla[jelenlegi->x][jelenlegi->y + 1], hova);
          }
     }

     return 0;
}

//az egyenesen balra lépés helyességét ellenőrzi a metódus
int egyenes_balra_lepes(Mezo** tabla, Mezo *jelenlegi, Mezo *hova) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi != hova && jelenlegi->y - 1 >= 0) {
               return egyenes_balra_lepes(tabla, &tabla[jelenlegi->x][jelenlegi->y - 1], hova);
          }
     }

     return 0;
}

//egyenes lépések ellenőrzése
int egyenesen_jo_e(Mezo** tabla, Mezo* honnan, Mezo* hova) {
     if (honnan->x - 1 >= 0) {
          if (egyenes_fel_lepes(tabla, &tabla[honnan->x - 1][honnan->y], hova)) return 1;
     }
     if (honnan->x + 1 <= 7) {
          if (egyenes_le_lepes(tabla, &tabla[honnan->x + 1][honnan->y], hova)) return 1;
     }
     if (honnan->y + 1 <= 7) {
          if (egyenes_jobbra_lepes(tabla, &tabla[honnan->x][honnan->y + 1], hova)) return 1;
     }
     if (honnan->y - 1 <= 7) {
          if (egyenes_balra_lepes(tabla, &tabla[honnan->x][honnan->y - 1], hova)) return 1;
     }
     
     return 0;
}

//-------------------------------------------------------------------------------------------------------

//elenőrzés, hogy átlós irányba van-e sakk
//jobbra felfele
int jobbra_fel_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'b') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->x - 1 >= 0 && jelenlegi->y + 1 <= 7) {
               return jobbra_fel_ellenoriz(tabla, &tabla[jelenlegi->x - 1][jelenlegi->y + 1], szin);
          }
     }
     return 0;
}

//jobbra lefele
int jobbra_le_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'b') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->x + 1 <= 7 && jelenlegi->y + 1 <= 7) {
               return jobbra_le_ellenoriz(tabla, &tabla[jelenlegi->x + 1][jelenlegi->y + 1], szin);
          }
     }

     return 0;
}

//balra felfele
int balra_fel_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'b') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->x - 1 >= 0 && jelenlegi->y - 1 >= 0) {
               return balra_fel_ellenoriz(tabla, &tabla[jelenlegi->x - 1][jelenlegi->y - 1], szin);
          }
     }

     return 0;
}

//balra lefele
int balra_le_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'b') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->x + 1 <= 7 && jelenlegi->y - 1 >= 0) {
               return balra_le_ellenoriz(tabla, &tabla[jelenlegi->x + 1][jelenlegi->y - 1], szin);
          }
     }

     return 0;
}

//elenőrzés, hogy egyenes irányba van-e sakk
//felfele
int egyenesen_fel_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'r') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->x - 1 >= 0) {
               return egyenesen_fel_ellenoriz(tabla, &tabla[jelenlegi->x - 1][jelenlegi->y], szin);
          }
     }

     return 0;
}

//lefele
int egyenesen_le_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'r') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->x + 1 <= 7) {
               return egyenesen_le_ellenoriz(tabla, &tabla[jelenlegi->x + 1][jelenlegi->y], szin);
          }
     }

     return 0;
}

//jobbra
int egyenesen_jobbra_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'r') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->y + 1 >= 0) {
               return egyenesen_jobbra_ellenoriz(tabla, &tabla[jelenlegi->x][jelenlegi->y + 1], szin);
          }
     }

     return 0;
}

//balra
int egyenesen_balra_ellenoriz(Mezo** tabla, Mezo* jelenlegi, char szin) {
     if (tablan_belul_van_e(jelenlegi->x, jelenlegi->y)) {
          if (jelenlegi->szin == szin) return 0;
          if (jelenlegi->szin != szin && jelenlegi->szin != '-') {
               if (jelenlegi->babu == 'q' || jelenlegi->babu == 'r') return 1;
               else return 0;
          }
          if (jelenlegi->babu == '-' && jelenlegi->y - 1 >= 0) {
               return egyenesen_balra_ellenoriz(tabla, &tabla[jelenlegi->x][jelenlegi->y - 1], szin);
          }
     }

     return 0;
}

//ellenőzi, hogy ló lépésben van-e sakk
int lo_van_e(Mezo** tabla, Mezo* kiraly) {
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
int paraszt_van_e(Mezo** tabla, Mezo* kiraly) {
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
int sakk_ellenoriz(Mezo** tabla) {
     Mezo* feher = feher_kiraly_mezo(tabla);
     Mezo* fekete = fekete_kiraly_mezo(tabla);
     
     //átlós lépések
     if (feher->x - 1 >= 0 && feher->y + 1 <= 7) {
          if (jobbra_fel_ellenoriz(tabla, &tabla[feher->x - 1][feher->y + 1], 'w')) return 1;
     }
     if (fekete->x - 1 >= 0 && fekete->y + 1 <= 7) {
          if (jobbra_fel_ellenoriz(tabla, &tabla[fekete->x - 1][fekete->y + 1], 'b')) return 2;
     }

     if (feher->x + 1 <= 7 && feher->y + 1 <= 7) {
          if (jobbra_le_ellenoriz(tabla, &tabla[feher->x + 1][feher->y + 1], 'w')) return 1;
     }
     if (fekete->x + 1 <= 7 && fekete->y + 1 <= 7) {
          if (jobbra_le_ellenoriz(tabla, &tabla[fekete->x + 1][fekete->y + 1], 'b')) return 2;
     }

     if (feher->x - 1 >= 0 && feher->y - 1 >= 0) {
          if (balra_fel_ellenoriz(tabla, &tabla[feher->x - 1][feher->y - 1], 'w')) return 1;
     }
     if (fekete->x - 1 >= 0 && fekete->y - 1 >= 0) {
          if (balra_fel_ellenoriz(tabla, &tabla[fekete->x - 1][fekete->y - 1], 'b')) return 2;
     }

     if (feher->x + 1 <= 7 && feher->y - 1 >= 0) {
           if (balra_le_ellenoriz(tabla, &tabla[feher->x + 1][feher->y - 1], 'w')) return 1;
     }
     if (fekete->x + 1 <= 7 && fekete->y - 1 >= 0) {
          if (balra_le_ellenoriz(tabla, &tabla[fekete->x + 1][fekete->y - 1], 'b')) return 2;
     }

     //egyenes lépések
     if (feher->x - 1 >= 0) {
          if (egyenesen_fel_ellenoriz(tabla, &tabla[feher->x - 1][feher->y], 'w')) return 1;
     }
     if (fekete->x - 1 >= 0) {
          if (egyenesen_fel_ellenoriz(tabla, &tabla[fekete->x - 1][fekete->y], 'b')) return 2;
     }

     if (feher->x + 1 <= 7) {
          if (egyenesen_le_ellenoriz(tabla, &tabla[feher->x + 1][feher->y], 'w')) return 1;
     }
     if (fekete->x + 1 <= 7) {
          if (egyenesen_le_ellenoriz(tabla, &tabla[fekete->x + 1][fekete->y], 'b')) return 2;
     }

     if (feher->y + 1 <= 7) {
          if (egyenesen_jobbra_ellenoriz(tabla, &tabla[feher->x][feher->y + 1], 'w')) return 1;
     }
     if (fekete->y + 1 <= 7) {
          if (egyenesen_jobbra_ellenoriz(tabla, &tabla[fekete->x][fekete->y + 1], 'b')) return 2;
     }

     if (feher->y - 1 >= 0) {
          if (egyenesen_balra_ellenoriz(tabla, &tabla[feher->x][feher->y - 1], 'w')) return 1;
     }
     if (fekete->y - 1 >= 0) {
          if (egyenesen_balra_ellenoriz(tabla, &tabla[fekete->x][fekete->y - 1], 'b')) return 2;
     }

     //ló lépések
     if (lo_van_e(tabla, feher) == 1) return 1;
     if (lo_van_e(tabla, fekete) == 1) return 2;

     //paraszt lépések
     if (paraszt_van_e(tabla, feher) == 1) return 1;
     if (paraszt_van_e(tabla, fekete) == 1) return 2;

     return 0;
}

int oda_tud_e_lepni_seged(Mezo** tabla, Mezo* m, char szin) {
     if (jobbra_fel_ellenoriz(tabla, &tabla[m->x - 1][m->y + 1], szin)) return 1;
     if (jobbra_le_ellenoriz(tabla, &tabla[m->x + 1][m->y + 1], szin)) return 1;
     if (balra_fel_ellenoriz(tabla, &tabla[m->x - 1][m->y - 1], szin)) return 1;
     if (balra_le_ellenoriz(tabla, &tabla[m->x + 1][m->y - 1], szin)) return 1;

     if (egyenesen_fel_ellenoriz(tabla, &tabla[m->x - 1][m->y], szin)) return 1;
     if (egyenesen_le_ellenoriz(tabla, &tabla[m->x + 1][m->y], szin)) return 1;
     if (egyenesen_jobbra_ellenoriz(tabla, &tabla[m->x][m->y + 1], szin)) return 1;
     if (egyenesen_balra_ellenoriz(tabla, &tabla[m->x][m->y - 1], szin)) return 1;

     if (lo_van_e(tabla, m) == 1) return 1;

     if (paraszt_van_e(tabla, m) == 1) return 1;

     return 0;
}

//a fehér király mezőjét adja meg
Mezo* feher_kiraly_mezo(Mezo** tabla) {
     for (int i = 0; i < 8; ++i) {
          for (int j = 0; j < 8; ++j) {
               if (tabla[i][j].babu == 'k' && tabla[i][j].szin == 'w') return &tabla[i][j];
          }
     }
     return NULL;
}

//a fekete király mezőjét adja meg
Mezo* fekete_kiraly_mezo(Mezo** tabla) {
     for (int i = 0; i < 8; ++i) {
          for (int j = 0; j < 8; ++j) {
               if (tabla[i][j].babu == 'k' && tabla[i][j].szin == 'b') return &tabla[i][j];
          }
     }
     return NULL;
}

//ellenőrzi a bábuk lépésének helyességét
int lepes_ellenorzes(Mezo** tabla, Lepes* lepes, Mezo* honnan, Mezo* hova, char szin) {
     char ellenkezoszin; 
     if (szin == 'w') ellenkezoszin = 'b';
     if (szin == 'b') ellenkezoszin = 'w';

     //lo lépésének ellenőrzése
     if (honnan->babu == 'h') {
          if (lo_lepes(tabla, honnan, hova)) return 1;
          else return 0;
     }
     
     //futó lépésének ellenőrzése
     if (honnan->babu == 'b') {
          if (atlosan_jo_e(tabla, honnan, hova)) return 1;
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
          if (egyenesen_jo_e(tabla, honnan, hova)) return 1;
          else return 0;
     }
     
     //királynő lépésének ellenőrzése
     if (honnan->babu == 'q') {
          if (atlosan_jo_e(tabla, honnan, hova) || egyenesen_jo_e(tabla, honnan, hova)) return 1;
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
          if (kiraly_lepes(tabla, honnan, hova)) return 1;

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

int kiraly_tud_e_lepni(Mezo** tabla, Mezo* m) {
     if (tablan_belul_van_e(m->x - 1, m->y)) {
          if (tabla[m->x - 1][m->y].szin != m->szin &&
          oda_tud_e_lepni_seged(tabla, &tabla[m->x - 1][m->y], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }
     if (tablan_belul_van_e(m->x - 1, m->y + 1)) {
          if (tabla[m->x - 1][m->y + 1].szin != m->szin &&
          oda_tud_e_lepni_seged(tabla, &tabla[m->x - 1][m->y + 1], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }
     if (tablan_belul_van_e(m->x, m->y + 1)) {
          if (tabla[m->x][m->y + 1].szin != m->szin &&
          oda_tud_e_lepni_seged(tabla, &tabla[m->x][m->y + 1], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }
     if (tablan_belul_van_e(m->x + 1, m->y + 1)) {
          if (tabla[m->x + 1][m->y + 1].szin != m->szin &&
          oda_tud_e_lepni_seged(tabla, &tabla[m->x + 1][m->y + 1], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }
     if (tablan_belul_van_e(m->x + 1, m->y)) {
          if (tabla[m->x + 1][m->y].szin != m->szin &&
          oda_tud_e_lepni_seged(tabla, &tabla[m->x + 1][m->y], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }
     if (tablan_belul_van_e(m->x + 1, m->y - 1)) {
          if (tabla[m->x + 1][m->y - 1].szin != m->szin &&
          oda_tud_e_lepni_seged(tabla, &tabla[m->x + 1][m->y - 1], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }
     if (tablan_belul_van_e(m->x, m->y - 1)) {
          if (tabla[m->x][m->y - 1].szin != m->szin &&
          oda_tud_e_lepni_seged(tabla, &tabla[m->x][m->y - 1], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }
     if (tablan_belul_van_e(m->x - 1, m->y - 1)) {
          if (tabla[m->x - 1][m->y - 1].szin != m->szin &&
          oda_tud_e_lepni_seged(tabla, &tabla[m->x - 1][m->y - 1], (m->szin == 'w') ? 'b' : 'w') == 0) return 1;
     }

     return 0;
}

//kettő mezőt megcserél
int pozicio_cserel(Mezo** tabla, Lepes* lepes, Mezo* honnan, Mezo* hova, char szin) {
     int ervenytelenlepes = 0, lepesellenorzo = lepes_ellenorzes(tabla, lepes, honnan, hova, szin);
     char ideiglenes_honnan_babu = honnan->babu, ideiglenes_honnan_szin = honnan->szin;
     char ideiglenes_hova_babu = hova->babu, ideiglenes_hova_szin = hova->szin;
     
     if (honnan->babu == '-' || honnan->szin != szin) return 0; //ha nem a soron lévő játkos lép akkor 0-t ad vissza
     if (hova->szin == szin || lepesellenorzo == 0) return 2; //ha nem szabályosan lép a játékos 2-t ad vissza
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
     int sakke = sakk_ellenoriz(tabla);
     
     if (sakke == 1 && szin == 'w') ervenytelenlepes = 1;
     else if (sakke == 2 && szin == 'b') ervenytelenlepes = 1;

     if (ervenytelenlepes) {
          hova->babu = ideiglenes_hova_babu;
          hova->szin = ideiglenes_hova_szin;
          honnan->babu = ideiglenes_honnan_babu;
          honnan->szin = ideiglenes_honnan_szin;

          return 2;
     }

     if (lepesellenorzo == 2) paraszt_cserelese(hova);
     if (lepesellenorzo == 5) {
          if (hova->y == honnan->y + 2) { //jobbra sáncolás
               if (oda_tud_e_lepni_seged(tabla, &tabla[hova->x][5], hova->szin) == 0 && oda_tud_e_lepni_seged(tabla, &tabla[hova->x][6], hova->szin) == 0) {
                    tabla[hova->x][7].babu = '-';
                    tabla[hova->x][7].szin = '-';
                    tabla[hova->x][hova->y - 1].babu = 'r';
                    tabla[hova->x][hova->y - 1].szin = hova->szin;
               }
          } else if (hova->y == honnan->y - 2) { //balra sáncolás
               if (oda_tud_e_lepni_seged(tabla, &tabla[hova->x][1], hova->szin) == 0 && oda_tud_e_lepni_seged(tabla, &tabla[hova->x][2], hova->szin) == 0 &&
                    oda_tud_e_lepni_seged(tabla, &tabla[hova->x][3], hova->szin) == 0) {
                    tabla[hova->x][0].babu = '-';
                    tabla[hova->x][0].szin = '-';
                    tabla[hova->x][hova->y + 1].babu = 'r';
                    tabla[hova->x][hova->y + 1].szin = hova->szin;
               }
          }
     }
     
     Lepes* l;
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
     lepes->kovetkezo = l;
     l->elozo = lepes;
     lepes = l;

     if (sakke == 1 && szin != 'w') return 3;
     else if (sakke == 2 && szin != 'b') return 3;

     return 1;
}

void elozo_lepesek_kiir(Lepes* l, int szamol) {
     //a sakktábla oszlopait tárolja a karaktertömb
     char oszlopok[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
     if (szamol < 5 && l != NULL) {
          elozo_lepesek_kiir(l->elozo, szamol + 1);
          printf("%c%d->%c%d   ", oszlopok[l->honnan_y], 8 - l->honnan_x, oszlopok[l->hova_y], 8 - l->hova_x);
     }
}

//ez a metódus segí megtalálni, hogy paraszt cserélés volt-e a játszma során
int volt_e_paraszt_csere(Lepes* lepes) {
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
void visszalepes(Mezo** tabla, Lepes* lepes) {
     if (tabla[lepes->hova_x][lepes->hova_y].babu == 'k') {
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
          if (volt_e_paraszt_csere(lepes) == 6) tabla[lepes->hova_x][lepes->hova_y].babu = 'p';
     }

     if (lepes->honnan_x == 6 && lepes->hova_x == 7) {
          if (volt_e_paraszt_csere(lepes) == 1) tabla[lepes->hova_x][lepes->hova_y].babu = 'p';
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
     aktualis_megjelenit(tabla, lepes);
}

//betölt egy sakktáblát, innen kezdődik a játék
void uj_jatek() {
     Mezo** tabla = tabla_betolt();
     Lepes* lepes;
     lepes = (Lepes*) malloc(sizeof(Lepes));
     lepes->honnan_x = 2;
     printf("honnanx: %d\n", lepes->honnan_x);
     if (egy_lepes(tabla, lepes, "-", 0) == 1) {
          menu();
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
int egy_lepes(Mezo** tabla, Lepes* lepes, char* betolt_e, int betolt_vege) {
     int muvelet = 0, x, y, ellenoriz, sakk_e = 0;
     char sor, oszlop, jatekos = 'w';
     char bemenet[5];
     if (strcmp(betolt_e, "-") == 0) aktualis_megjelenit(tabla, lepes);

     if (betolt_vege == 1) {
          if (lepesek_megszamolasa(lepes, 0) % 2 == 1) jatekos = 'b';
          if (sakk_ellenoriz(tabla) != 0) sakk_e = 1;
     }

     if (strcmp(betolt_e, "-") == 1) {
          strcpy(bemenet, betolt_e);
          if (lepesek_megszamolasa(lepes, 0) % 2 == 1) jatekos = 'b';
     }

     while(muvelet != 9) {
          if (lepes != NULL) printf("lepesek: %d\n", lepes->honnan_x);
          if (sakk_e == 1) {
               if (strcmp(betolt_e, "-") == 0) aktualis_megjelenit(tabla, lepes);
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
                    ellenoriz = pozicio_cserel(tabla, lepes, &tabla[7 - (x - 1)][betubol_szamra_konvertal(&sor)],
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
                         if (strcmp(betolt_e, "-") == 0) aktualis_megjelenit(tabla, lepes);
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
                         visszalepes(tabla, lepes);

                         if (jatekos == 'w') jatekos = 'b';
                         else jatekos = 'w';
                         
                         if (sakk_ellenoriz(tabla) != 0) {
                              sakk_e = 1;
                              printf("Sakk e=%d\n", sakk_ellenoriz(tabla));
                         } else {
                              sakk_e = 0;
                         }
                    } else {
                         aktualis_megjelenit(tabla, lepes);
                         printf("Nem lehet visszalépni!\n\n");
                    }
               } else if (muvelet == 1) {
                    jatek_mentese(lepes);
               }
          } else if (muvelet != 2 && muvelet != 9 && sscanf(bemenet, "%c%d %c%d", &sor, &x, &oszlop, &y) != -1) {
               if (strcmp(betolt_e, "-") == 1) return 0;
               hibauzenet("bemeneti erteket");
          }
     }

     if (muvelet == 9) {
          printf("Elmenti a jatekot?: ");
          char valasz;
          getchar();
          scanf("%c", &valasz);
          if (valasz == 'i') {
               jatek_mentese(lepes);
               return 0;
          }
     }
     
     for(int i = 0; i < 8; i++) {
          free(tabla[i]);
     }

     free(tabla);
     
     while (lepes != NULL) {
          Lepes *seged = lepes->elozo;
          free(lepes);
          lepes = seged;
     }

     if (betolt_vege == 1) menu();
     return 1;
}

//megjeleníti az aktuális táblát és a navigációkat
void aktualis_megjelenit(Mezo** tabla, Lepes* lepes) {
     //a sakktábla oszlopait tárolja a karaktertömb
     char oszlopok[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
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
                    printf(" %s |", baburakonvertal(tabla[szamol][j].babu, tabla[szamol][j].szin));
               }
               ++szamol;
          }
          printf("\n");
     }
     printf("\n1. Jatek mentese\n2. Visszalepes\n\n9. Kilepes\n\n");
}

//betölt egy üres táblát
Mezo** tabla_betolt() {
     Mezo** tabla;

     tabla = malloc(sizeof(Mezo*) * 8);
     for (int i = 0; i < 8; i++) tabla[i] = malloc(sizeof(Mezo) * 8);

     //tábla feltöltése
     for(int j = 0; j < 8; j++) {
          for(int i = 0; i < 8; i++) {
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

     return tabla;
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

//menti az aktuális játékot
void jatek_mentese(Lepes* lepes) {
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

//betölt egy elmentett sakkjátszmát
void jatek_betolt() {
     //a sakktábla oszlopait tárolja a karaktertömb
     char oszlopok[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
     FILE *jatszma;
     char jatek[50];

     printf("Melyik játékot szeretné megnyitni?: ");
     scanf("%s", jatek);

     jatszma = fopen(jatek, "r");
     if (jatszma == NULL) {
          printf("Nincs ilyen fájl");
          menu();
     }

     Mezo** tabla = tabla_betolt();
     Lepes* lepes;

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

          if (egy_lepes(tabla, lepes, bemenet, 0) == 0) {
               while (lepes != NULL) {
                    Lepes *seged = lepes->elozo;
                    free(lepes);
                    lepes = seged;
               }
               free(beolvasott);
               fclose(jatszma);
               system("cls");
               printf("Hibás lépés van ebben a játszmában!\n");
               menu();
               return;
          }
     }
     free(beolvasott);
     fclose(jatszma);
     
     egy_lepes(tabla, lepes, "-", 1);
}

//megjeleníti a használati útmutatót, megjeleníti a programmal kapcsolatos tudnivalókat
void hasznalati_utmutato() {
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
     int beolvas;
     scanf("%d", &beolvas);
     if (beolvas != 9) {
          hibauzenet("erteket");
          printf("9. Vissza a menube\n\nValasztas: ");
          scanf("%d", &beolvas);
          system("cls");
     }
     system("cls");
     menu();
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
void menu() {
     int beolvas;
     printf("- Sakk -\n\n1. Uj jatek\n2. Jatek betoltese\n3. Hasznalati utmutato\n\n9. Kilepes\n\n");
     printf("Valasztas: ");
     scanf("%d", &beolvas);
     switch (beolvas) {
          case 1:
               system("cls");
               uj_jatek();
               break;
          case 2:
               system("cls");
               jatek_betolt();
               break;
          case 3:
               system("cls");
               hasznalati_utmutato();
               break;
          case 9:
               kilepes();
               break;
          default:
               system("cls");
               hibauzenet("erteket");
               menu();
               break;
     }
}

int main(void) {
     SetConsoleOutputCP(650001);
     menu();
}