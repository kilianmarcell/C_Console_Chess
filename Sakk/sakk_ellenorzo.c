#include "mezo.h"
#include "babu_lepesek.h"

//ellen�rzi, hogy sakk van-e
int sakk_ellenoriz(Mezo* feher, Mezo* fekete) {
     //�tl�s l�p�sek
     if (jobbra_fel_ellenoriz(&tabla[feher->x - 1][feher->y + 1], 'w')) return 1;
     if (jobbra_fel_ellenoriz(&tabla[fekete->x - 1][fekete->y + 1], 'b')) return 2;

     if (jobbra_le_ellenoriz(&tabla[feher->x + 1][feher->y + 1], 'w')) return 1;
     if (jobbra_le_ellenoriz(&tabla[fekete->x + 1][fekete->y + 1], 'b')) return 2;

     if (balra_fel_ellenoriz(&tabla[feher->x - 1][feher->y - 1], 'w')) return 1;
     if (balra_fel_ellenoriz(&tabla[fekete->x - 1][fekete->y - 1], 'b')) return 2;

     if (balra_le_ellenoriz(&tabla[feher->x + 1][feher->y - 1], 'w')) return 1;
     if (balra_le_ellenoriz(&tabla[fekete->x + 1][fekete->y - 1], 'b')) return 2;

     //egyenes l�p�sek
     if (egyenesen_fel_ellenoriz(&tabla[feher->x - 1][feher->y], 'w')) return 1;
     if (egyenesen_fel_ellenoriz(&tabla[fekete->x - 1][fekete->y], 'b')) return 2;

     if (egyenesen_le_ellenoriz(&tabla[feher->x + 1][feher->y], 'w')) return 1;
     if (egyenesen_le_ellenoriz(&tabla[fekete->x + 1][fekete->y], 'b')) return 2;

     if (egyenesen_jobbra_ellenoriz(&tabla[feher->x][feher->y + 1], 'w')) return 1;
     if (egyenesen_jobbra_ellenoriz(&tabla[fekete->x][fekete->y + 1], 'b')) return 2;

     if (egyenesen_balra_ellenoriz(&tabla[feher->x][feher->y - 1], 'w')) return 1;
     if (egyenesen_balra_ellenoriz(&tabla[fekete->x][fekete->y - 1], 'b')) return 2;

     //l� l�p�sek
     if (lo_van_e(feher) == 1) return 1;
     if (lo_van_e(fekete) == 1) return 2;

     //paraszt l�p�sek
     if (paraszt_van_e(feher) == 1) return 1;
     if (paraszt_van_e(fekete) == 1) return 2;

     return 0;
}

//ellen�rzi, hogy a bemenetk�nt �rkez� b�bu ha kir�ly lenne, sakk lenne e
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
