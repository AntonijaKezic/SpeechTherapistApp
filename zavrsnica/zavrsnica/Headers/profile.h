
#ifndef PROFILE_H
#define PROFILE_H

typedef struct _person* position;

typedef struct _person {
    char ime[50];
    char prezime[50];
    char spol[10];
    char datumIspitivanja[11];
    int dob;
    char materinjiJezik[30];
    char ispitivac[50];
    char napomene[200];
    position next;
} Person;

position CreatePerson(char* name, char* lastName, char* spol, char* datumIspitivanja, int dob, char* materinjiJezik, char* ispitivac, char* napomene);
position InputProfile();
void SaveProfileToFile(position person, const char* fileName);
void popisivanje(position person, const char* fileName, int bodovi);

#endif // PROFILE_H