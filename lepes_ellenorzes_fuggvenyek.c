#include "mezo.h"
#include "konstansok.h"
#include "lepes_ellenorzes_fuggvenyek.h"

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