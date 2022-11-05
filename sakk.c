#include <stdio.h>
#include "debugmalloc.h"

/*
     itt adom meg, hogy milyen tulajdonságai vannak egy mezőnek
*/
typedef struct {
     int x; //sor
     int y; //oszlop
     char babu; //király = k, királynő = q, futó = b, ló = h, bástya = r, paraszt = p
     char szin; //fehér = w, fekete = b
} Mezo;

// /*
//      ez a metódus hozza létre a 8x8-as táblát, ennek a táblának fogjuk az értékeit állítani,
//      amikor lépnek a játékosok
// */
// Mezo* sakktablaletrehozasa() {
//      Mezo tabla[7][7];
//      //tábla feltöltése
//      for(int i = 0; i < 7; ++i) {
//           for(int j = 0; j < 7; ++j) {
//                tabla[i][j].x = i;
//                tabla[i][j].y = j;
//                //a paraszt bábuk beállítása
//                if (i == 1) {
//                     tabla[i][j].babu = 'p';
//                     tabla[i][j].szin = 'b';
//                }
//                if (i == 6) {
//                     tabla[i][j].babu = 'p';
//                     tabla[i][j].szin = 'w';
//                }
//           }
//      }

//      //fekete bábuk beállítása, a parasztokon kívül
//      tabla[0][0].babu = 'r';
//      tabla[0][1].babu = 'h';
//      tabla[0][2].babu = 'b';
//      tabla[0][3].babu = 'q';
//      tabla[0][4].babu = 'k';
//      tabla[0][5].babu = 'b';
//      tabla[0][6].babu = 'h';
//      tabla[0][7].babu = 'r';

//      tabla[0][0].szin = 'b';
//      tabla[0][1].szin = 'b';
//      tabla[0][2].szin = 'b';
//      tabla[0][3].szin = 'b';
//      tabla[0][4].szin = 'b';
//      tabla[0][5].szin = 'b';
//      tabla[0][6].szin = 'b';
//      tabla[0][7].szin = 'b';

//      //fehér bábuk beállítása, a parasztokon kívül
//      tabla[7][0].babu = 'r';
//      tabla[7][1].babu = 'h';
//      tabla[7][2].babu = 'b';
//      tabla[7][3].babu = 'k';
//      tabla[7][4].babu = 'q';
//      tabla[7][5].babu = 'b';
//      tabla[7][6].babu = 'h';
//      tabla[7][7].babu = 'r';

//      tabla[7][0].szin = 'w';
//      tabla[7][1].szin = 'w';
//      tabla[7][2].szin = 'w';
//      tabla[7][3].szin = 'w';
//      tabla[7][4].szin = 'w';
//      tabla[7][5].szin = 'w';
//      tabla[7][6].szin = 'w';
//      tabla[7][7].szin = 'w';
// }

/*
     betölt egy sakktáblát, innen kezdődik a játék
*/
void ujjatek(int* navigal) {
     system("cls");
     printf("- Sakk -\n\n1. Uj jatek\n2. Jatek mentese\n3. Visszalepes\n\n9. Kilepes\n\n");
     
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

     tabla[0][0].szin = 'b';
     tabla[0][1].szin = 'b';
     tabla[0][2].szin = 'b';
     tabla[0][3].szin = 'b';
     tabla[0][4].szin = 'b';
     tabla[0][5].szin = 'b';
     tabla[0][6].szin = 'b';
     tabla[0][7].szin = 'b';

     //fehér bábuk beállítása, a parasztokon kívül
     tabla[7][0].babu = 'r';
     tabla[7][1].babu = 'h';
     tabla[7][2].babu = 'b';
     tabla[7][3].babu = 'q';
     tabla[7][4].babu = 'k';
     tabla[7][5].babu = 'b';
     tabla[7][6].babu = 'h';
     tabla[7][7].babu = 'r';

     tabla[7][0].szin = 'w';
     tabla[7][1].szin = 'w';
     tabla[7][2].szin = 'w';
     tabla[7][3].szin = 'w';
     tabla[7][4].szin = 'w';
     tabla[7][5].szin = 'w';
     tabla[7][6].szin = 'w';
     tabla[7][7].szin = 'w';
     
     for(int i = 0; i < 8; i++) {
          for(int j = 0; j < 8; j++) {
               printf("%c ", tabla[i][j].babu);
          }
          printf("\n");
     }
}

/*
     betölt egy elmentett sakk játszmát, 
*/
void jatekbetolt(int* navigal) {
}

/*
     megjeleníti a használati útmutatót, megjeleníti a programmal kapcsolatos tudnivalókat
*/
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

/*
     ez a metódus kilép a programból
*/
void kilepes() {
     exit(0);
}

/*
     hibaüzenetet ír a felhasználónak, visszajelzést ad, ha helytelen bemeneti értéket adott meg a felhasználó
*/
void hibauzenet(char *uzenet) {
     printf("Kerem ervenyes %s adjon meg!\n\n", uzenet);
}

/*
     amikor betölt a program ez a metódus fut le először, ez a metódus a menüt jelenti, itt dönti el a felhasználó,
     hogy mit szeretne a programon belül csinálni, ez a metódus a felhasználó által választott metódust hívja meg
*/
void menu(int* navigal) {
     printf("- Sakk -\n\n1. Uj jatek\n2. Jatek betoltese\n3. Hasznalati utmutato\n\n9. Kilepes\n\n");
     printf("Valasztas: ");
     scanf("%d", navigal);
     printf("\n\n%d\n\n", *navigal);
     switch (*navigal) {
          case 1:
               system("cls");
               ujjatek(navigal);
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