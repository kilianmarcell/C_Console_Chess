#include <stdio.h>
#include <stdlib.h>
#include "hibauzenet.h"
#include "menu.h"

//megjeleníti a használati útmutatót, megjeleníti a programmal kapcsolatos tudnivalókat
void hasznalati_utmutato(int* navigal) {
     printf("- Sakk -\n\n- Leptetes\n");
     printf("Ket bemeneti erteket kell beirni (ketto darab koordinatat) a babuk leptetesehez egy jatszmaban. ");
     printf("Az elso az a pozicio amelyik helyrol szeretnenk leptetni a babunkat, ");
     printf("a masodik azt a koordinatat jelenti, ahova leptetni szeretnenk a kivalasztott babut.");
     printf("\nA koordinatak ketto karakterbol allnak, az elso a karakter egy betu (A-H), a masodik egy szam (1-8). ");
     printf("A betuknel kis es nagybetu is elfogadott.");
     printf("\nHa helytelen lepest adott meg, ellenõrizze, hogy mit rontott el es ujra adja meg a koordinatakat.");
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
