#include <stdio.h>
#include <stdlib.h>
#include "jatszma.h"
#include "mentes_beolvas.h"
#include "hasznalati_utmutato.h"
#include "kilepes.h"
#include "hibauzenet.h"

//amikor bet�lt a program ez a met�dus fut le el�sz�r, ez a met�dus a men�t jelenti, itt d�nti el a felhaszn�l�,
//hogy mit szeretne a programon bel�l csin�lni, ez a met�dus a felhaszn�l� �ltal v�lasztott met�dust h�vja meg
void menu(int* navigal) {
     printf("- Sakk -\n\n1. Uj jatek\n2. Jatek betoltese\n3. Hasznalati utmutato\n\n9. Kilepes\n\n");
     printf("Valasztas: ");
     scanf("%d", navigal);
     printf("\n\n%d\n\n", *navigal);
     switch (*navigal) {
          case 1:
               system("cls");
               uj_jatek(navigal);
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
