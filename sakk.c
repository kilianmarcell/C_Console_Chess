#include <stdio.h>
#include <stdbool.h>
#include "mezo.h"
#include "lepes.h"
#include "debugmalloc.h"

void menu(int* navigal);
void hibauzenet(char *uzenet);
int jobbra_fel_lepes(Mezo* jelenlegi, Mezo* hova, char szin);
int jobbra_le_lepes(Mezo* jelenlegi, Mezo* hova, char szin);
int balra_fel_lepes(Mezo* jelenlegi, Mezo* hova, char szin);
int balra_le_lepes(Mezo* jelenlegi, Mezo* hova, char szin);

Mezo tabla[8][8];

Lepes *lepes;
Lepes *elsolepes;
//lepes->kovetkezo_lepes = elsolepes;

//a sakktábla oszlopait tárolja a karaktertömb
char oszlopok[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

//a sakkbábuk betűit tárolja a karaktertömb
char babubetuk[] = { 'k', 'q', 'r', 'b', 'h', 'p' };

//a sakkbábukat tárolja el a "karaktertömb"
char *babuk[] = { "♔", "♕", "♖", "♗", "♘", "♙", "♚", "♛", "♜", "♝", "♞", "♟︎" };

//ellenőrzi, hogy érvényes sorokat adott-e meg a felhasználó (sakk játszma közben)
bool helyesxy(int* x, int* y) {
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

//Különböző lépések ellenőrzései
//egy bábunak a jobbra lefele átlós lépését ellenőrzi
int jobbra_le_lepes(Mezo *jelenlegi, Mezo* hova, char szin) {
     if (jelenlegi->x >= 0 && jelenlegi->x <= 7 && jelenlegi->y >= 0 && jelenlegi->y <= 7) {
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->x + 1 >= 0 && jelenlegi->y + 1 <= 7) {
               if (jobbra_fel_lepes(&tabla[jelenlegi->x + 1][jelenlegi->y + 1], hova, szin)) return 1;
          }
     }
     return 0;
}

//egy bábunak a balra felfele átlós lépését ellenőrzi
int balra_fel_lepes(Mezo *jelenlegi, Mezo* hova, char szin) {
     if (jelenlegi->x >= 0 && jelenlegi->x <= 7 && jelenlegi->y >= 0 && jelenlegi->y <= 7) {
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->x - 1 >= 0 && jelenlegi->y - 1 <= 7) {
               if (jobbra_fel_lepes(&tabla[jelenlegi->x - 1][jelenlegi->y - 1], hova, szin)) return 1;
          }
     }
     return 0;
}

//egy bábunak a balra lefele átlós lépését ellenőrzi
int balra_le_lepes(Mezo *jelenlegi, Mezo* hova, char szin) {
     if (jelenlegi->x >= 0 && jelenlegi->x <= 7 && jelenlegi->y >= 0 && jelenlegi->y <= 7) {
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->x + 1 >= 0 && jelenlegi->y - 1 <= 7) {
               if (jobbra_fel_lepes(&tabla[jelenlegi->x + 1][jelenlegi->y - 1], hova, szin)) return 1;
          }
     }
     return 0;
}

//-------------------------------------------------------------------------------------------------------

//ez a metódus kiírja az aktuális táblát és a navigációkat
void aktualis_megjelenit(Mezo* m) {
     //system("cls");
     printf("\n    ");
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

//ellenőrzi a léptetni kívánt bábu lépését
int leptetes_ellenorzes(Mezo* honnan, Mezo* hova, char szin) {
     if (honnan->babu == 'k') {
          if (honnan->szin == 'w') {
          }
          if (honnan->szin == 'w') {
          }
     }
     if (honnan->babu == 'q') {
          if (honnan->szin == 'w') {
          }
          if (honnan->szin == 'w') {
          }
     }
     if (honnan->babu == 'h') {
          if (honnan->szin == 'w') {
          }
          if (honnan->szin == 'w') {
          }
     }
     if (honnan->babu == 'r') {
          if (honnan->szin == 'w') {
          }
          if (honnan->szin == 'w') {
          }
     }

     return 0;
}

//az átlós lépés helyességét ellenőrzi a metódus
void atlos_lepes_ellenorzes(Mezo *honnan, Mezo *hova) {
     //int honnanx = honnan->x, honnany = honnan->y, hovax = hova->x, hovay = hova->y;

     int i = 0;
     int siker = 0;
     if (helyesxy(&honnan->x + 1, &honnan->y + 1) == 1) {
          if (tabla[honnan->x + 1][honnan->y + 1].babu == '-' ||
          &tabla[honnan->x + 1][honnan->y + 1] == &tabla[hova->x][hova->y]) {

               atlos_lepes_ellenorzes(&tabla[honnan->x + 1][honnan->y + 1], hova);
          }
     }
     while(helyesxy(&honnan->x + i, &honnan->y + i) == 1 && tabla[honnan->x + i][honnan->y + i].babu == '-') {
          ++i;
     }
}

//az egyenes lépés helyességét ellenőrzi a metódus
void egyenes_lepes_ellenorzes(Mezo *honnan, Mezo *hova) {
     int honnanx = honnan->x, honnany = honnan->y, hovax = hova->x, hovay = hova->y;
}

void ideiglenesellenoriz(Mezo* honnan, Mezo* hova, char szin) {
     char ellenkezoszin; 
     if (szin == 'w') ellenkezoszin = 'b';
     if (szin == 'b') ellenkezoszin = 'w';

     if (honnan->babu == 'p') {
          if (honnan->szin == 'w') {
               if (honnan->y == hova->y) {
                    if (honnan->x == hova->x + 1 && hova->babu == '-') {
                         printf("\nsikeres elore lepes\n");
                         //return 1;
                    } else if (honnan->x == 6 && honnan->x == hova->x + 2) {
                         printf("\nsikeres 2 lepes\n");
                         //return 1;
                    } else {
                         printf("sikertelen lepes");
                         //return 0;
                    }
               } else {
                    if (honnan->x == hova->x + 1 && (honnan->y == hova->y - 1 || honnan->y == hova->y + 1 ) &&
                    hova->szin == ellenkezoszin) {
                         printf("sikeres utes");
                         //return 1;
                    } else {
                         printf("sikertelen lepes");
                         //return 0;
                    }
                    printf("nem fuggoleges");
               }
               //TODO: csere, en passant
          } else if (honnan->szin == 'b') {
               if (honnan->y == hova->y) {
                    if (honnan->x == hova->x - 1 && hova->babu == '-') {
                         printf("\nsikeres elore lepes\n");
                         //return 1;
                    } else if (honnan->x == 1 && honnan->x == hova->x - 2) {
                         printf("\nsikeres 2 lepes\n");
                         //return 1;
                    } else {
                         printf("sikertelen lepes");
                         //return 0;
                    }
               } else {
                    if (honnan->x == hova->x - 1 && (honnan->y == hova->y + 1 || honnan->y == hova->y - 1 ) &&
                    hova->szin == ellenkezoszin) {
                         printf("sikeres utes");
                         //return 1;
                    } else {
                         printf("sikertelen lepes");
                         //return 0;
                    }
                    printf("nem fuggoleges");
               }
               //TODO: csere, en passant
          } else {
               printf("sikertelen lepes");
               //return 0;
          }
     }
     
     if (honnan->babu == 'b') {
          if (honnan->szin == 'w') {
               if (jobbra_fel_lepes(&tabla[honnan->x - 1][honnan->y + 1], hova, szin)) printf("Siekres lepes"); //return 1;
               if (jobbra_le_lepes(&tabla[honnan->x + 1][honnan->y + 1], hova, szin)) printf("Siekres lepes"); //return 1;
               if (balra_fel_lepes(&tabla[honnan->x - 1][honnan->y - 1], hova, szin)) printf("Siekres lepes"); //return 1;
               if (balra_le_lepes(&tabla[honnan->x + 1][honnan->y - 1], hova, szin)) printf("Siekres lepes"); //return 1;
          }else if (honnan->szin == 'b') {
               if (jobbra_fel_lepes(&tabla[honnan->x - 1][honnan->y + 1], hova, szin)) printf("Siekres lepes"); //return 1;
               if (jobbra_le_lepes(&tabla[honnan->x + 1][honnan->y + 1], hova, szin)) printf("Siekres lepes"); //return 1;
               if (balra_fel_lepes(&tabla[honnan->x - 1][honnan->y - 1], hova, szin)) printf("Siekres lepes"); //return 1;
               if (balra_le_lepes(&tabla[honnan->x + 1][honnan->y - 1], hova, szin)) printf("Siekres lepes"); //return 1;
          } else {
               printf("Sikertelen lepes");
               //return 0;
          }
     }
}

//egy bábunak a jobbra felfele átlós lépését ellenőrzi
int jobbra_fel_lepes(Mezo *jelenlegi, Mezo* hova, char szin) {
     if (jelenlegi->x >= 0 && jelenlegi->x <= 7 && jelenlegi->y >= 0 && jelenlegi->y <= 7) {
          if (jelenlegi != hova && jelenlegi->babu != '-') return 0;
          if (jelenlegi == hova) return 1;
          if (jelenlegi != hova && jelenlegi->x - 1 >= 0 && jelenlegi->y + 1 <= 7) {
               if (jobbra_fel_lepes(&tabla[jelenlegi->x - 1][jelenlegi->y + 1], hova, szin)) return 1;
          }
     }
     return 0;
}

//kettő mezőt megcserél
int pozicio_cserel(Mezo* honnan, Mezo* hova, char szin) {
     char ellenkezoszin; 
     if (szin == 'w') ellenkezoszin = 'b';
     if (szin == 'b') ellenkezoszin = 'w';

     if (honnan->babu == '-' || honnan->szin != szin) return 0; //ha nem a soron lévő játkos lép akkor 0-t ad vissza
     if (hova->szin == szin/* || ellenoriz == 0*/) return 2; //ha nem szabályosan lép a játékos 2-t ad vissza
     ideiglenesellenoriz(honnan, hova, szin);
     char ideiglenesbabu = honnan->babu;
     char ideiglenesszin = honnan->szin;

     if (hova->szin == ellenkezoszin) {
          honnan->babu = '-';
          honnan->szin = '-';
     } else {
          honnan->babu = hova->babu;
          honnan->szin = hova->szin;
     }

     hova->babu = ideiglenesbabu;
     hova->szin = ideiglenesszin;

     // Lepes *l;
     // l = (Lepes*) malloc(sizeof(Lepes));
     // char jelenlepes[5];
     // l->lepes[0] = (char) oszlopok[honnan->y];
     // l->lepes[1] = (char) honnan->x;
     // l->lepes[2] = ' ';
     // l->lepes[3] = (char) oszlopok[hova->y];
     // l->lepes[4] = (char) hova->x;
     // l->kovetkezo_lepes = NULL;
     //utsolepes

     return 1;
}

//betölt egy sakktáblát, innen kezdődik a játék
void uj_jatek() {
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
     
     int muvelet, x, y, ellenoriz;
     char sor, oszlop, jatekos = 'w';
     char bemenet[5];

     gets(bemenet);
     aktualis_megjelenit(&tabla[0][0]);
     do {
          (jatekos == 'w') ? printf("Feher") : printf("Fekete");
          printf(" jatekos: ");
          gets(bemenet);
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
                         if (jatekos == 'w') {
                              jatekos = 'b';
                         } else if (jatekos == 'b') {
                              jatekos = 'w';
                         }
                         aktualis_megjelenit(&tabla[0][0]);
                    }
               } else {
                    hibauzenet("bemeneti erteket");
               }
          } else if (sscanf(bemenet, "%d", &muvelet) == 1) {
          } else {
               hibauzenet("bemeneti erteket");
          }
     } while(muvelet != 9);
}

//betölt egy elmentett sakk játszmát, 
void jatek_betolt(int* navigal) {
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
               uj_jatek();
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