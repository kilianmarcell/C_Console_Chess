#include <stdio.h>
#include <stdlib.h>
#include "lepes.h"
#include "jatszma.h"
#include "konvertalasok.h"
#include "menu.h"
#include "mentes_beolvas.h"

extern char oszlopok[];
extern Lepes *lepes;

//menti az aktu�lis j�t�kot
void jatek_mentese() {
     printf("Hova szeretn� menteni a j�tszm�t? ");
     char jatek[50];
     scanf(" %[^\n]s", jatek);

     FILE *mentes = fopen(jatek, "w");
     if (mentes == NULL) {
          printf("Sikertelen ment�s!");
     }

     fajlbair(mentes, lepes);

     printf("\nSikeres ment�s!\n");
     fclose(mentes);
}

//helyes sorrendben menti el a l�p�seket
void fajlbair(FILE* mentes, Lepes* lepes) {
     if (lepes->elozo != NULL) fajlbair(mentes, lepes->elozo);

     fputc(lepes->honnan_x + '0', mentes);
     fputc(lepes->honnan_y + '0', mentes);
     fputc(lepes->hova_x + '0', mentes);
     fputc(lepes->hova_y + '0', mentes);
     fputc('\n', mentes);
}

//bet�lt egy elmentett sakkj�tszm�t
void jatek_betolt(int* navigal) {
     FILE *jatszma;
     char jatek[50];

     printf("Melyik j�t�kot szeretn� megnyitni?: ");
     scanf("%s", jatek);

     jatszma = fopen(jatek, "r");
     if (jatszma == NULL) {
          printf("Nincs ilyen f�jl");
          menu(navigal);
     }

     tabla_betolt();

     fseek(jatszma, 0, SEEK_END);
     int length = ftell(jatszma);
     fseek(jatszma, 0, SEEK_SET); //a f�jl elej�re vissz�k vissza a pointert

     char *beolvasott = malloc(sizeof(char) * (length + 1));

     char c;
     int szamol = 0;

     while ((c = fgetc(jatszma)) != EOF) {
          beolvasott[szamol] = c;
          szamol++;
     }

     beolvasott[szamol] = '\0';
     char bemenet[5];

     for(int i = 4; i <= szamol; i += 5) {
          bemenet[0] = oszlopok[karakterbol_szamra_konvertal(beolvasott[i - 3])];
          bemenet[1] = (8 - karakterbol_szamra_konvertal(beolvasott[i - 4])) + '0';
          bemenet[2] = oszlopok[karakterbol_szamra_konvertal(beolvasott[i - 1])];
          bemenet[3] = (8 - karakterbol_szamra_konvertal(beolvasott[i - 2])) + '0';
          bemenet[4] = '\0';

          if (egy_lepes(bemenet, 0) == 0) {
               while (lepes != NULL) {
                    Lepes *seged = lepes->elozo;
                    free(lepes);
                    lepes = seged;
               }
               free(beolvasott);
               fclose(jatszma);
               system("cls");
               printf("Hib�s l�p�s van ebben a j�tszm�ban!\n");
               menu(navigal);
          }
     }
     free(beolvasott);
     fclose(jatszma);

     egy_lepes("-", 1);
}
