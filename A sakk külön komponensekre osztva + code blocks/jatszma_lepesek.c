#include <stdio.h>
#include <stdlib.h>
#include "mezo.h"
#include "lepes.h"
#include "konvertalasok.h"
#include "jatszma.h"

extern char oszlopok[];
extern Mezo tabla[8][8];
extern Lepes *lepes;
extern Mezo* feher_kiraly;
extern Mezo* fekete_kiraly;

void elozo_lepesek_kiir(Lepes* l, int szamol) {
     if (szamol < 5 && l != NULL) {
          elozo_lepesek_kiir(l->elozo, szamol + 1);
          printf("%c%d->%c%d   ", oszlopok[l->honnan_y], 8 - l->honnan_x, oszlopok[l->hova_y], 8 - l->hova_x);
     }
}

//megjelen�ti az aktu�lis t�bl�t �s a navig�ci�kat
void aktualis_megjelenit(Mezo* m) {
     // system("cls");
     if (lepesek_megszamolasa(lepes, 0) > 0) {
          printf("Utols� 5 l�p�s:   ");
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

//ez a met�dus seg� megtal�lni, hogy paraszt cser�l�s volt-e a j�tszma sor�n
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

//vissza�ll�tja az el�z� l�p�sre a sakkt�bl�t
void visszalepes() {
     if (tabla[lepes->hova_x][lepes->hova_y].babu == 'k') {
          if (tabla[lepes->hova_x][lepes->hova_y].szin == 'w') feher_kiraly = &tabla[lepes->honnan_x][lepes->honnan_y];
          if (tabla[lepes->hova_x][lepes->hova_y].szin == 'b') fekete_kiraly = &tabla[lepes->honnan_x][lepes->honnan_y];

          if (lepes->honnan_y == lepes->hova_y - 2) { //ha jobbra s�ncol�s volt
               tabla[lepes->honnan_x][5].babu = '-';
               tabla[lepes->honnan_x][5].szin = '-';
               tabla[lepes->honnan_x][7].babu = 'r';
               tabla[lepes->honnan_x][7].szin = tabla[lepes->hova_x][lepes->hova_y].szin;
          } else if (lepes->honnan_y == lepes->hova_y + 2) { //ha balra s�ncol�s volt
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

     //ha feh�r paraszt csin�lt en passant-ot
     if (lepes->leutott_babu == 'p' && lepes->leutott_szin == 'b' && lepes->honnan_x == 3 && lepes->elozo->honnan_x == 1 && lepes->elozo->hova_x == 3) {
          tabla[lepes->elozo->hova_x][lepes->elozo->hova_y].babu = 'p';
          tabla[lepes->elozo->hova_x][lepes->elozo->hova_y].szin = 'b';
          lepes->leutott_babu = '-';
          lepes->leutott_szin = '-';
     }

     //ha fekete paraszt csin�lt en passant-ot
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
