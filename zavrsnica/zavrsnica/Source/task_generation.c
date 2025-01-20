#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/task_generation.h"

const char* rime[] = { "most - kost", "livada - trava", "snijeg - brijeg", "lopta - krov", "ptica - skica" };
const char* fonemi[] = { "m-o-s-t", "p-t-i-c-a", "t-r-a-v-a", "l-o-p-t-a", "s-k-i-c-a", "k-u-l-a" };
const char* slogovi[] = { "ka-me-nje", "o-bi-telj", "sa-nja-ti", "sli-ka-ti", "bro-do-vi", "te-le-fon" };

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

void rima_zadaci(const char* fileName) {
    FILE* file = fopen(fileName, "w");
    if (!file) {
        printf("Greska pri otvaranju datoteke: %s\n", fileName);
        return;
    }

    // Zadatci za prepoznavanje rime
    fprintf(file, "Prepoznavanje rime:\n\n");
    fprintf(file, "1 soba - roba\n");
    fprintf(file, "2 grana - brana\n");
    fprintf(file, "3 suma - vina\n");
    fprintf(file, "4 crkva - mrkva\n");
    fprintf(file, "5 padobran - knjizara\n");
    fprintf(file, "6 gljiva - sljiva\n");
    fprintf(file, "7 vodopad - sudoper\n");

    fprintf(file, "\nProizvodnja rime:\n\n");
    fprintf(file, "1 most\n");
    fprintf(file, "2 meta\n");
    fprintf(file, "3 puska\n");
    fprintf(file, "4 crv\n");
    fprintf(file, "5 lonac\n");
    fprintf(file, "6 trava\n");
    fprintf(file, "7 guma\n");

    fclose(file);
}

void slogovni_zadaci(const char* fileName) {
    FILE* file = fopen(fileName, "w");
    if (!file) {
        printf("Greska pri otvaranju datoteke: %s\n", fileName);
        return;
    }

    fprintf(file, "\nSlogovna rasclamba:\n\n");
    char* zadaci1[] = { "kugla", "sedam", "pravac", "tramvaj", "kutija", "suncokret", "vješalica" };
    for (int i = 0; i < 7; i++) {
        fprintf(file, "%d %s\n", i + 1, zadaci1[i]);
    }
    fprintf(file, "\nSlogovno stapanje:\n\n");
    char* zadaci2[] = { "va-za", "ka-men", "pro-zor", "vo-æka", "lo-pa-ta", "vi-li-ca", "he-li-ko-pter" };
    for (int i = 0; i < 7; i++) {
        fprintf(file, "%d %s\n", i + 1, zadaci2[i]);
    }

    fclose(file);
}

void fonemski_zadaci(const char* fileName) {
    FILE* file = fopen(fileName, "w");
    if (!file) {
        printf("Greska pri otvaranju datoteke: %s\n", fileName);
        return;
    }

    // Zadatci za fonemsku rašclambu
    fprintf(file, "Fonemska rašclamba:\n\n");
    fprintf(file, "1 vuk\n");
    fprintf(file, "2 njuh\n");
    fprintf(file, "3 usna\n");
    fprintf(file, "4 hrana\n");
    fprintf(file, "5 maèak\n");
    fprintf(file, "6 maškare\n");
    fprintf(file, "7 mrvica\n");

    // Zadatci za fonemsko stapanje
    fprintf(file, "\nFonemsko stapanje:\n\n");
    fprintf(file, "1 z-e-k-o\n");
    fprintf(file, "2 k-o-l-a-è\n");
    fprintf(file, "3 k-nj-i-g-a\n");
    fprintf(file, "4 b-o-j-i-c-a\n");
    fprintf(file, "5 z-a-v-j-e-s-a\n");
    fprintf(file, "6 m-a-s-l-a-è-a-k\n");
    fprintf(file, "7 v-j-e-v-e-r-i-c-a\n");

    fclose(file);
}

void vjezba() {
    char unos[10];

    while (1) {
        // Generiranje nasumiène rime
        const char* rima = rime[random_int(0, 4)];

        // Generiranje nasumiènog fonema
        const char* fonem = fonemi[random_int(0, 6)];

        // Generiranje nasumiène rijeèi sastavljene od dva sloga
        const char* slog1 = slogovi[random_int(0, 5)];
        const char* slog2 = slogovi[random_int(0, 5)];
        char rijec[50];
        snprintf(rijec, sizeof(rijec), "%s, %s", slog1, slog2);

        // Ispisivanje zadatka
        printf("\nNasumicna rima: %s\n", rima);
        printf("Nasumicni fonem: %s\n", fonem);
        printf("Nasumicna rijeè: %s\n", rijec);

        // Èekanje na Enter ili "kraj"
        printf("\nPritisnite Enter za promjenu nasumicnih rijeci ili unesite 'kraj' za izlaz: ");
        fgets(unos, sizeof(unos), stdin);
        unos[strcspn(unos, "\n")] = '\0';
        if (strncmp(unos, "kraj", 4) == 0) {
            break;
        }
    }
}