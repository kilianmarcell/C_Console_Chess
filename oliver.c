#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <malloc.h>

typedef struct {
    int *nehezseg;
    char *kerdes;
    char *a_valasz;
    char *b_valasz;
    char *c_valasz;
    char *d_valasz;
    char *megoldas;
    char *kategoria;
}KERDES;

int main(){
    KERDES *kerdesek;
    FILE * open_kerdesek;
    open_kerdesek = fopen("kerdesek.csv", "r");
    if(open_kerdesek == NULL)
        printf("Nem nyilt meg a fajl!\n");
        
    char sor[1000];
    for (int i = 1; EOF != fscanf(open_kerdesek, "%s", sor);++i){
        KERDES*Uj_kerdesek = (KERDES*)malloc((i+1)*sizeof(KERDES));
        for(int j = 1; j<i; j++)
            Uj_kerdesek[j]=kerdesek[j];
        KERDES ujkerdes;




        Uj_kerdesek[i] = ujkerdes;
       // while(karakter[i] = '\n')
          //  sor[i] = karakter[i];
    printf("%s", sor);
    free(kerdesek);

    }


    fclose(open_kerdesek);
    return 0;
}