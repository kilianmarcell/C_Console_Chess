#include <stdio.h>
#include "debugmalloc.h"

void menu(int* navigal);
void hibauzenet(char *uzenet);

//itt adom meg, hogy milyen tulajdonságai vannak egy mezőnek
typedef struct {
     int x; //sor
     int y; //oszlop
     char babu; //király = k, királynő = q, futó = b, ló = h, bástya = r, paraszt = p
     char szin; //fehér = w, fekete = b
} Mezo;

//a sakktábla oszlopait tárolja a karaktertömb
char oszlopok[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

//a sakkbábuk betűit tárolja a karaktertömb
char babubetuk[] = { 'k', 'q', 'r', 'b', 'h', 'p' };

//a sakkbábukat tárolja el a "karaktertömb"
char *babuk[] = { "♔", "♕", "♖", "♗", "♘", "♙", "♚", "♛", "♜", "♝", "♞", "♟︎" };


//ez a metódus kiírja az aktuális táblát és a navigációkat
void aktualismegjelenit(Mezo* m) {
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
                    printf(" %c |", m->babu);
                    m++;
               }
               szamol++;
          }
          printf("\n");
     }
     printf("\n1. Jatek mentese\n2. Visszalepes\n\n9. Kilepes\n\n");
}

//ellenőrzi, hogy érvényes sorokat adott-e meg a felhasználó (sakk játszma közben)
int helyesxy(int* x, int* y) {
     return (*x >= 1 && *x <= 8 && *y >= 1 && *y <= 8);
}

//ellenőrzi, hogy érvényes oszlopokat adott-e meg a felhasználó (sakk játszma közben)
int helyessoroszlop(char* sor, char* oszlop) {
     *sor = tolower(*sor);
     *oszlop = tolower(*oszlop);
     int szamol = 0;
     for(int i = 0; i < 8; i++) {
          if (oszlopok[i] == *oszlop) ++szamol;
          if (oszlopok[i] == *sor) ++szamol;
     }

     return (szamol == 2);
}

//a játékos által megadott betűt egy y koordinátává változtatja
int betubolszamrakonvertal(char* betu) {
     int szamol = 0;
     for(int i = 0; i < 8; i++) {
          if (oszlopok[i] == *betu) return (i);
     }

     return 0;
}

//kettő mezőt megcserél
int poziciocserel(Mezo* honnan, Mezo* hova, char szin) {
     if (honnan->babu != '-' && honnan->szin == szin) {
          int x = honnan->x, y = honnan->y;
          char babu = honnan->babu, szin = honnan->szin;

          honnan->x = hova->x;
          honnan->y = hova->y;
          honnan->babu = hova->babu;
          honnan->szin = hova->szin;

          hova->x = x;
          hova->y = y;
          hova->babu = babu;
          hova->szin = szin;
          return 1;
     }
     
     return 0;
}

//betölt egy sakktáblát, innen kezdődik a játék
void ujjatek() {
     Mezo tabla[8][8];
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
     
     int muvelet, x, y;
     char sor, oszlop, jatekos = 'w';
     char bemenet[5];

     gets(bemenet);
     aktualismegjelenit(&tabla[0][0]);
     do {
          (jatekos == 'w') ? printf("Feher") : printf("Fekete");
          printf(" jatekos: ");
          gets(bemenet);
          if (sscanf(bemenet, "%c%d %c%d", &sor, &x, &oszlop, &y) == 4) {
               if (helyesxy(&x, &y) && helyessoroszlop(&sor, &oszlop)) {
                    if (poziciocserel(&tabla[7 - (x - 1)][betubolszamrakonvertal(&sor)],
                         &tabla[7 - (y - 1)][betubolszamrakonvertal(&oszlop)],
                         jatekos) == 0) {
                              if (jatekos == 'w') {
                                   printf("A feher jatekos kovetkezik!\n");
                              } else if (jatekos == 'b') {
                                   printf("A fekete jatekos kovetkezik!\n");
                              }
                    } else {
                         if (jatekos == 'w') {
                              jatekos = 'b';
                         } else if (jatekos == 'b') {
                              jatekos = 'w';
                         }
                         aktualismegjelenit(&tabla[0][0]);
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
void jatekbetolt(int* navigal) {
}

//megjeleníti a használati útmutatót, megjeleníti a programmal kapcsolatos tudnivalókat
void hasznalatiutmutato(int* navigal) {
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
               ujjatek();
               break;
          case 2:
               system("cls");
               jatekbetolt(navigal);
               break;
          case 3:
               system("cls");
               hasznalatiutmutato(navigal);
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