#include "mezo.h"
#include "konvertalasok.h"

//l� l�p�sei
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

//kir�ly l�p�sei
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

//�tl�s l�p�sek
//egy b�bunak a jobbra felfele �tl�s l�p�s�t ellen�rzi
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

//egy b�bunak a jobbra lefele �tl�s l�p�s�t ellen�rzi
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

//egy b�bunak a balra felfele �tl�s l�p�s�t ellen�rzi
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

//egy b�bunak a balra lefele �tl�s l�p�s�t ellen�rzi
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

//�tl�s l�p�sek ellen�rz�se
int atlosan_jo_e(Mezo* honnan, Mezo* hova) {
     if (jobbra_fel_lepes(&tabla[honnan->x - 1][honnan->y + 1], hova)) return 1;
     if (jobbra_le_lepes(&tabla[honnan->x + 1][honnan->y + 1], hova)) return 1;
     if (balra_fel_lepes(&tabla[honnan->x - 1][honnan->y - 1], hova)) return 1;
     if (balra_le_lepes(&tabla[honnan->x + 1][honnan->y - 1], hova)) return 1;

     return 0;
}

//egyenes l�p�sek
//az egyenesen felfele l�p�s helyess�g�t ellen�rzi a met�dus
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

//az egyenesen lefele l�p�s helyess�g�t ellen�rzi a met�dus
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

//az egyenesen jobbra l�p�s helyess�g�t ellen�rzi a met�dus
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

//az egyenesen balra l�p�s helyess�g�t ellen�rzi a met�dus
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

//egyenes l�p�sek ellen�rz�se
int egyenesen_jo_e(Mezo* honnan, Mezo* hova) {
     if (egyenes_fel_lepes(&tabla[honnan->x - 1][honnan->y], hova)) return 1;
     if (egyenes_le_lepes(&tabla[honnan->x + 1][honnan->y], hova)) return 1;
     if (egyenes_jobbra_lepes(&tabla[honnan->x][honnan->y + 1], hova)) return 1;
     if (egyenes_balra_lepes(&tabla[honnan->x][honnan->y - 1], hova)) return 1;

     return 0;
}

//-------------------------------------------------------------------------------------------------------

//elen�rz�s, hogy �tl�s ir�nyba van-e sakk
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

//elen�rz�s, hogy egyenes ir�nyba van-e sakk
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

//ellen�zi, hogy l� l�p�sben van-e sakk
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

//ellen�zi, hogy paraszt l�p�sben van-e sakk
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
