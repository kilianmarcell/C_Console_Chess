#include <stdio.h>
#include <stdlib.h>
#include "mezo.h"
#include "lepes.h"
#include "babu_lepesek.h"
#include "konvertalasok.h"
#include "sakk_ellenorzo.h"

extern Mezo tabla[8][8];
extern Lepes *lepes;
extern Mezo* feher_kiraly;
extern Mezo* fekete_kiraly;

//ellenõrzi a bábuk lépésének helyességét
int lepes_ellenorzes(Mezo* honnan, Mezo* hova, char szin) {
     char ellenkezoszin;
     if (szin == 'w') ellenkezoszin = 'b';
     if (szin == 'b') ellenkezoszin = 'w';

     //lo lépésének ellenõrzése
     if (honnan->babu == 'h') {
          if (lo_lepes(honnan, hova)) return 1;
          else return 0;
     }

     //futó lépésének ellenõrzése
     if (honnan->babu == 'b') {
          if (atlosan_jo_e(honnan, hova)) return 1;
          else return 0;
     }

     //paraszt lépésének ellenõrzése
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

     //bástya lépésének ellenõrzése
     if (honnan->babu == 'r') {
          if (egyenesen_jo_e(honnan, hova)) return 1;
          else return 0;
     }

     //királynõ lépésének ellenõrzése
     if (honnan->babu == 'q') {
          if (atlosan_jo_e(honnan, hova) || egyenesen_jo_e(honnan, hova)) return 1;
          else return 0;
     }

     //király lépésének ellenõrzése
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
     printf("\nMilyen bábura váltasz? (q = királynõ, r = bástya, b = futó, h = ló) ");
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

//kettõ mezõt megcserél
int pozicio_cserel(Mezo* honnan, Mezo* hova, char szin) {
     int ervenytelenlepes = 0, lepesellenorzo = lepes_ellenorzes(honnan, hova, szin);
     char ideiglenes_honnan_babu = honnan->babu, ideiglenes_honnan_szin = honnan->szin;
     char ideiglenes_hova_babu = hova->babu, ideiglenes_hova_szin = hova->szin;

     if (honnan->babu == '-' || honnan->szin != szin) return 0; //ha nem a soron lévõ játkos lép akkor 0-t ad vissza
     if (hova->szin == szin || lepesellenorzo == 0) return 2; //ha nem szabályosan lép a játékos 2-t ad vissza
     if (honnan->babu == 'k') {
          if (honnan->szin == 'w') feher_kiraly = hova;
          else fekete_kiraly = hova;
     }
     if (hova->szin != szin && hova->szin != '-') { //ha ütés történik
          hova->babu = '-';
          hova->szin = '-';
     }

     //mezõk cserélése
     honnan->babu = hova->babu;
     honnan->szin = hova->szin;
     hova->babu = ideiglenes_honnan_babu;
     hova->szin = ideiglenes_honnan_szin;

     //sakk ellenõrzése
     int sakke = sakk_ellenoriz(feher_kiraly, fekete_kiraly);

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
