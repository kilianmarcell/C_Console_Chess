#ifndef LEPES_H_INCLUDED
#define LEPES_H_INCLUDED

//ebben a structban egy lépést lehet eltárolni
typedef struct Lepes {
     int honnan_x;
     int honnan_y;
     int hova_x;
     int hova_y;
     char leutott_szin;
     char leutott_babu;
     struct Lepes *elozo, *kov;
} Lepes;

#endif