#ifndef BABU_LEPESEK_H_INCLUDED
#define BABU_LEPESEK_H_INCLUDED

int lo_lepes(Mezo* jelenlegi, Mezo* hova);
int kiraly_lepes(Mezo* jelenlegi, Mezo* hova);
int jobbra_fel_lepes(Mezo* jelenlegi, Mezo* hova);
int jobbra_le_lepes(Mezo* jelenlegi, Mezo* hova);
int balra_fel_lepes(Mezo* jelenlegi, Mezo* hova);
int balra_le_lepes(Mezo* jelenlegi, Mezo* hova);
int atlosan_jo_e(Mezo* honnan, Mezo* hova);
int egyenes_fel_lepes(Mezo *jelenlegi, Mezo *hova);
int egyenes_le_lepes(Mezo *jelenlegi, Mezo *hova);
int egyenes_jobbra_lepes(Mezo *jelenlegi, Mezo *hova);
int egyenes_balra_lepes(Mezo *jelenlegi, Mezo *hova);
int egyenesen_jo_e(Mezo* honnan, Mezo* hova);
int jobbra_fel_ellenoriz(Mezo* jelenlegi, char szin);
int jobbra_le_ellenoriz(Mezo* jelenlegi, char szin);
int balra_fel_ellenoriz(Mezo* jelenlegi, char szin);
int balra_le_ellenoriz(Mezo* jelenlegi, char szin);
int egyenesen_fel_ellenoriz(Mezo* jelenlegi, char szin);
int egyenesen_le_ellenoriz(Mezo* jelenlegi, char szin);
int egyenesen_jobbra_ellenoriz(Mezo* jelenlegi, char szin);
int egyenesen_balra_ellenoriz(Mezo* jelenlegi, char szin);
int lo_van_e(Mezo* kiraly);
int paraszt_van_e(Mezo* kiraly);

#endif // BABU_LEPESEK_H_INCLUDED
