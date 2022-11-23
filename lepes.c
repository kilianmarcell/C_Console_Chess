#include "lepes.h"

//ebben a structban egy lépést lehet eltárolni
typedef struct Lepes {
     char *lepes;
     struct Lepes *kovetkezo_lepes;
} Lepes;