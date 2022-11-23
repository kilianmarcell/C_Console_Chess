#include <stdio.h>
#include "mezo.h"
#include "lepes.h"
#include "konstansok.h"
#include "konvertalasok.h"
#include "lepes_ellenorzes_fuggvenyek.h"
#include "debugmalloc.h"

void menu(int* navigal);
void hibauzenet(char *uzenet);

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
     
     if (honnan->babu == '-' || honnan->szin != szin) return 0; //ha nem a soron lévő játkos lép akkor 0-t ad vissza
     if (hova->szin == szin || lepes_ellenorzes(honnan, hova, szin) == 0) return 2; //ha nem szabályosan lép a játékos 2-t ad vissza
     if (honnan->babu == 'k') {
          if (honnan->szin == 'w') feher_kiraly = hova;
          else fekete_kiraly = hova;
     }

     char ideiglenesbabu = honnan->babu;
     char ideiglenesszin = honnan->szin;

     if (hova->szin != szin && hova->szin != '-') {
          hova->babu = '-';
          hova->szin = '-';
     }

     honnan->babu = hova->babu;
     honnan->szin = hova->szin;
     hova->babu = ideiglenesbabu;
     hova->szin = ideiglenesszin;

     int sakke = sakk_ellenoriz(feher_kiraly, fekete_kiraly);
     printf("\n%d\n\n", sakke);
     if (sakke == 1) {
          if (szin == 'w') {
               ervenytelenlepes = 1;
          } else {
               printf("\nSakk!\n");
          }
     } else if (sakke == 2) {
          if (szin == 'b') {
               ervenytelenlepes = 1;
          } else {
               printf("\nSakk!\n");
          }
     }

     if (ervenytelenlepes) {
          hova->babu = honnan->babu;
          hova->szin = honnan->szin;
          honnan->babu = ideiglenesbabu;
          honnan->szin = ideiglenesszin;
          
          if (honnan->babu == 'k') {
               if (honnan->szin == 'w') feher_kiraly = honnan;
               else fekete_kiraly = honnan;
          }

          return 2;
     }

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

//megjeleníti az aktuális táblát és a navigációkat
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

     feher_kiraly = &tabla[7][4];
     fekete_kiraly = &tabla[0][4];
     
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