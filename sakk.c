#include <stdio.h>
#include "debugmalloc.h"

/*
     betölt egy sakktáblát, innen kezdődik a játék
*/
void ujjatek(int* navigal) {
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
     printf("Hibas lepes eseten jelez a program.");
     printf("\n\n- Betoltes\n");
     printf("Ha be szeretne tolteni egy jatszmat, a jatszma nevet kell beirnia a kiterjesztesevel egyutt ");
     printf("(a kiterjesztes txt) peldaul: jatszma.txt");

     printf("\n\n9. Vissza a menube\n\nValasztas: ");
     scanf("%d", navigal);
     while (*navigal != 9) {
          hibauzenet();
          printf("9. Vissza a menube\n\nValasztas: ");
          scanf("%d", navigal);
     }
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
void hibauzenet() {
     printf("Kerem ervenyes erteket adjon meg!\n\n");
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
               ujjatek(navigal);
               break;
          case 2:
               jatekbetolt(navigal);
               break;
          case 3:
               hasznalatiutmutato(navigal);
               break;
          case 9:
               kilepes();
               break;
          default:
               hibauzenet();
               menu(navigal);
     }
}

int main(void) {
     int navigal;
     menu(&navigal);
}