#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *nehezseg;
    char *kerdes;
    char *a_valasz;
    char *b_valasz;
    char *c_valasz;
    char *d_valasz;
    char *megoldas;
    char *kategoria;
} Kerdes;

void kiir(Kerdes *values, int hossz) {
    for (int i = 0; i < hossz; i++)
    printf("%s %s %s %s %s %s %s %s\n", 
        values[i].nehezseg,
        values[i].kerdes,
        values[i].a_valasz,
        values[i].b_valasz,
        values[i].c_valasz,
        values[i].d_valasz,
        values[i].megoldas,
        values[i].kategoria);
    printf("\n");
}

int main(void)
{
  FILE *fp = fopen("kerdesek.csv", "r"); 
  
  if (fp == NULL) {
    printf("Error opening file.\n");
    return 1;
  }
  
  // array of structs for storing the Student data from the file
  char buff[1024];
  int row_count = 0;
  int field_count = 0;

  Kerdes values[5100];

    int i = 0;
    while(fgets(buff, 1024, fp)) {
        field_count = 0;
        row_count++;

        if (row_count == 1) {
            continue;
        }

        char *field = strtok(buff, ';');

        while (field) {
            if (field_count == 0) strcpy(values[i].nehezseg, field);
            if (field_count == 1) strcpy(values[i].kerdes, field);
            if (field_count == 2) strcpy(values[i].a_valasz, field);
            if (field_count == 3) strcpy(values[i].b_valasz, field);
            if (field_count == 4) strcpy(values[i].c_valasz, field);
            if (field_count == 5) strcpy(values[i].d_valasz, field);
            if (field_count == 6) strcpy(values[i].megoldas, field);
            if (field_count == 7) strcpy(values[i].kategoria, field);

            field = strtok(NULL, ";");
            field_count++;
        }
        i++;
    }
    fclose(fp);

    kiir(values, row_count);

  return 0;
}