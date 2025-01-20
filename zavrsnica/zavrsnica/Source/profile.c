#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/profile.h"
#include "../Headers/date_validation.h"

position CreatePerson(char* name, char* lastName, char* spol, char* datumIspitivanja, int dob, char* materinjiJezik, char* ispitivac, char* napomene) {
    position newPerson = (position)malloc(sizeof(Person));
    if (!newPerson) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }

    strcpy(newPerson->ime, name);
    strcpy(newPerson->prezime, lastName);
    strcpy(newPerson->spol, spol);
    strcpy(newPerson->datumIspitivanja, datumIspitivanja);
    newPerson->dob = dob; // Ispravno spremanje dobi kao int
    strcpy(newPerson->materinjiJezik, materinjiJezik);
    strcpy(newPerson->ispitivac, ispitivac);
    strcpy(newPerson->napomene, napomene);
    newPerson->next = NULL;

    return newPerson;
}

position InputProfile() {
    char ime[50], prezime[50], spol[10];
    char datumIspitivanja[11], materinjiJezik[30], ispitivac[50], napomene[200];
    int dob;  // Dob je integer

    printf("Unesite ime: ");
    scanf("%s", ime);
    ime[strcspn(ime, "\n")] = '\0';

    printf("Unesite prezime: ");
    scanf("%s", prezime);
    prezime[strcspn(prezime, "\n")] = '\0';

    getchar();

    printf("Unesite spol (M/Z): ");
    fgets(spol, sizeof(spol), stdin);
    spol[strcspn(spol, "\n")] = '\0';

    unos_i_provjera_datuma(datumIspitivanja);

    while (getchar() != '\n' && !feof(stdin)); // Èišæenje ulaznog spremnika

    char c;  // Koristimo za èišæenje ulaznog spremnika
    printf("Unesite dob ispitanika: ");
    // Petlja za validaciju unosa
    while (scanf("%d", &dob) != 1) {
        printf("Pogrešan unos! Molimo unesite broj: ");
        while ((c = getchar()) != '\n' && c != EOF);  // Èisti ulazni spremnik
    }
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Unesite materinji jezik: ");
    fgets(materinjiJezik, sizeof(materinjiJezik), stdin);
    materinjiJezik[strcspn(materinjiJezik, "\n")] = '\0';

    printf("Unesite ime ispitivaca: ");
    fgets(ispitivac, sizeof(ispitivac), stdin);
    ispitivac[strcspn(ispitivac, "\n")] = '\0';

    printf("Unesite napomene: ");
    fgets(napomene, sizeof(napomene), stdin);
    napomene[strcspn(napomene, "\n")] = '\0';

    return CreatePerson(ime, prezime, spol, datumIspitivanja, dob, materinjiJezik, ispitivac, napomene);
}

void SaveProfileToFile(position person, const char* fileName) {
    FILE* file = fopen(fileName, "a");
    if (!file) {
        printf("Greska pri otvaranju datoteke!\n");
        return;
    }

    fprintf(file, "\nPodaci o ispitaniku:\n");

    fprintf(file, "\nIme: %s\n", person->ime);
    fprintf(file, "Prezime: %s\n", person->prezime);
    fprintf(file, "Spol: %s\n", person->spol);
    fprintf(file, "Datum ispitivanja: %s\n", person->datumIspitivanja);
    fprintf(file, "Dob: %d\n", person->dob); // Ispravno spremanje dobi kao int
    fprintf(file, "Materinji jezik: %s\n", person->materinjiJezik);
    fprintf(file, "Ispitivac: %s\n", person->ispitivac);
    fprintf(file, "Napomene: %s\n", person->napomene);

    fclose(file);
    printf("Profil uspjesno spremljen u datoteku: %s\n", fileName);
}

void popisivanje(position person, const char* fileName, int bodovi) {
    FILE* file = fopen(fileName, "a");
    if (!file) {
        printf("Greska pri otvaranju datoteke!\n");
        return;
    }
    fprintf(file, "Ime: %s\n", person->ime);
    fprintf(file, "Prezime: %s\n", person->prezime);
    fprintf(file, "Bodovi: %d\n", bodovi);
    fclose(file);
}