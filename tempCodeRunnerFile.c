lepni_seged(&tabla[hova->x][5], hova->szin) == 0 && oda_tud_e_lepni_seged(&tabla[hova->x][6], hova->szin) == 0) {
                    tabla[hova->x][7].babu = '-';
                    tabla[hova->x][7].szin = '-';
                    tabla[hova->x][hova->y - 1].babu = 'r';
                    tabla[hova->x][hova->y - 1].szin = hova->szin;
               }