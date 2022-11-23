#ifndef LEPES_ELLENORZES_H_INCLUDED
#define LEPES_ELLENORZES_H_INCLUDED

int lo_lepes(Mezo*, Mezo*);
int kiraly_lepes(Mezo*, Mezo*);

int jobbra_fel_lepes(Mezo*, Mezo*);
int jobbra_le_lepes(Mezo*, Mezo*);
int balra_fel_lepes(Mezo*, Mezo*);
int balra_le_lepes(Mezo*, Mezo*);

int egyenes_fel_lepes(Mezo*, Mezo*);
int egyenes_le_lepes(Mezo*, Mezo*);
int egyenes_jobbra_lepes(Mezo*, Mezo*);
int egyenes_balra_lepes(Mezo*, Mezo*);

//sakkot ellenőrző metódusok
int jobbra_fel_ellenoriz(Mezo*, char);
int jobbra_le_ellenoriz(Mezo*, char);
int balra_fel_ellenoriz(Mezo*, char);
int balra_le_ellenoriz(Mezo*, char);

int egyenesen_fel_ellenoriz(Mezo*, char);
int egyenesen_le_ellenoriz(Mezo*, char);
int egyenesen_jobbra_ellenoriz(Mezo*, char);
int egyenesen_balra_ellenoriz(Mezo*, char);

int lo_van_e(Mezo*);

int atlosan_jo_e(Mezo*, Mezo*);
int egyenesen_jo_e(Mezo*, Mezo*);
int sakk_ellenoriz(Mezo*, Mezo*);

#endif