#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "../Headers/date_validation.h"

void unos_i_provjera_datuma(char* datumIspitivanja) {
    int dan, mjesec, godina;
    char input[11];
    const int trenutna_godina = 2025;

    // Broj dana u svakom mjesecu
    int dani_u_mjesecu[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    while (1) {
        // Unos datuma
        printf("Unesite datum ispitivanja (DD.MM.GGGG.): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  // Ukloni newline na kraju unosa
        getchar();

        // Provjera formata datuma
        if (sscanf(input, "%d.%d.%d", &dan, &mjesec, &godina) != 3) {
            printf("Pogrešan format datuma. Unesite u formatu DD.MM.GGGG.\n");
            continue;
        }

        // Provjera raspona godine
        if (godina < 1900 || godina > trenutna_godina) {
            printf("Godina mora biti u rasponu od 1900. do trenutne godine.\n");
            continue;
        }

        // Provjera raspona mjeseca
        if (mjesec < 1 || mjesec > 12) {
            printf("Mjesec mora biti u rasponu od 1 do 12.\n");
            continue;
        }

        // Provjera prijestupne godine
        if (mjesec == 2 && ((godina % 4 == 0 && godina % 100 != 0) || (godina % 400 == 0))) {
            dani_u_mjesecu[1] = 29;
        }
        else {
            dani_u_mjesecu[1] = 28;
        }

        // Provjera raspona dana
        if (dan < 1 || dan > dani_u_mjesecu[mjesec - 1]) {
            printf("Dan nije ispravan za zadani mjesec.\n");
            continue;
        }

        // Ako je datum ispravan, pohranjuje se u varijablu datum
        snprintf(datumIspitivanja, 11, "%02d.%02d.%04d", dan, mjesec, godina); // Ispravno pohranjivanje datuma u string
        printf("Datum validan!\n");

        break; // Izlazak iz petlje nakon valjanog unosa
    }
}