#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mezo.h"
#include "lepes.h"
#include "jatszma.h"
#include "konvertalasok.h"
#include "lepes_ellenorzo.h"
#include "jatszma_lepesek.h"
#include "sakk_ellenorzo.h"
#include "menu.h"
#include "hibauzenet.h"
#include "mentes_beolvas.h"

//betölt egy sakktáblát, innen kezdõdik a játék
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
