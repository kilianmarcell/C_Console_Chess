//ebben a structban egy lépést lehet eltárolni
typedef struct {
     char lepes[5];
     struct Lepes *kovetkezo_lepes;
} Lepes;