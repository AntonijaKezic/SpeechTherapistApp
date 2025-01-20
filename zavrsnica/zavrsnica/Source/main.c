#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Headers/date_validation.h"
#include "../Headers/task_generation.h"
#include "../Headers/profile.h"

// Definicija strukture za korisnièki profil
typedef struct {
    char ime[100];
    char prezime[100];
    int bodovi;
} UserProfile;

// Definicija èvora u binarnom stablu
typedef struct TreeNode {
    UserProfile data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Funkcija za stvaranje novog èvora
TreeNode* createNode(UserProfile data) {
    TreeNode* newNode = malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);  // Izaðite iz programa ako malloc ne uspije
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Funkcija za umetanje èvora u binarno stablo
TreeNode* insertNode(TreeNode* root, UserProfile data) {
    if (root == NULL) {
        return createNode(data);
    }

    // Ako su bodovi manji, lijevo
    if (data.bodovi < root->data.bodovi) {
        root->left = insertNode(root->left, data);
    }
    // Ako su bodovi veæi, desno
    else if (data.bodovi > root->data.bodovi) {
        root->right = insertNode(root->right, data);
    }
    // Ako su bodovi isti, umetanje u lijevo podstablo
    else {
        root->left = insertNode(root->left, data);
    }

    return root;
}

// Funkcija za èitanje podataka iz datoteke i izgradnju stabla
void readFileAndBuildTree(const char* filename, TreeNode** root) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Greška pri otvaranju datoteke.\n");
        return;
    }

    UserProfile profile;  // Struktura za pohranu podataka o profilu
    char temp[200];  // Privremena varijabla za èitanje svake linije iz datoteke

    // Èitanje podataka
    while (fgets(temp, sizeof(temp), file)) {
        // Provjeravamo je li trenutna linija ime
        if (strncmp(temp, "Ime:", 4) == 0) {
            sscanf(temp, "Ime: %s", profile.ime);  // Spremamo ime korisnika
        }

        // Provjeravamo je li trenutna linija prezime
        if (strncmp(temp, "Prezime:", 8) == 0) {
            sscanf(temp, "Prezime: %s", profile.prezime);  // Spremamo prezime korisnika
        }

        // Provjeravamo je li trenutna linija uspjeh u bodovima
        if (strncmp(temp, "Uspjeh u bodovima:", 18) == 0) {
            sscanf(temp, "Uspjeh u bodovima: %d", &profile.bodovi);  // Spremamo bodove korisnika

            // Umetnemo profil u stablo pomoæu funkcije insertNode
            *root = insertNode(*root, profile);
        }
    }
    fclose(file);
}

// Funkcija za ispisivanje stabla (sortirano) u datoteku
void sortiranje(TreeNode* root, FILE* file) {
    if (root != NULL) {
        sortiranje(root->left, file);
        fprintf(file, "\nIme i prezime: %s %s\nBodovi: %d\n", root->data.ime, root->data.prezime, root->data.bodovi);
        sortiranje(root->right, file);
    }
}

// Funkcija za zapisivanje zadataka za prepoznavanje rime i proizvodnju rime u istu datoteku
void rima_test(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("Greška pri otvaranju datoteke: %s\n", fileName);
        return;
    }

    char line[100];

    // Èitanje i ispisivanje sadržaja datoteke
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void slogovi_test(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("Greška pri otvaranju datoteke: %s\n", fileName);
        return;
    }

    char line[100];

    // Èitanje zadataka iz datoteke i ispis
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void fonemi_test(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("Greška pri otvaranju datoteke: %s\n", fileName);
        return;
    }

    char line[100];

    // Èitanje i ispisivanje svih zadataka iz datoteke
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

// Funkcija za unos bodova
int unos_bodova() {
    int bodovi = 0;
    char unos[50];

    printf("Unesite bodove (npr. 1+1+2...) i pritisnite Enter:\n");
    fgets(unos, sizeof(unos), stdin);

    int trenutni_broj = 0;
    for (int i = 0; unos[i] != '\0'; i++) {
        if (unos[i] >= '0' && unos[i] <= '9') {  // Ako je broj
            trenutni_broj = trenutni_broj * 10 + (unos[i] - '0');
        }
        else if (unos[i] == '+') {  // Ako naiðemo na '+', dodajemo broj u bodove
            bodovi += trenutni_broj;
            trenutni_broj = 0;
        }
    }
    bodovi += trenutni_broj;  // Dodavanje zadnjeg broja
    printf("\nOstvaren broj bodova na ovom zadatku je: %d\n", bodovi);
    return bodovi;
}

// Funkcija za ispisivanje sortiranog popisa iz datoteke i izvoženje u drugu datoteku
void ispis_popisa(const char* inputFileName, const char* outputFileName) {
    FILE* inputFile = fopen(inputFileName, "r");
    FILE* outputFile = fopen(outputFileName, "w");
    if (!inputFile || !outputFile) {
        printf("Greška pri otvaranju datoteke: %s\n", inputFileName);
        if (inputFile) fclose(inputFile);
        if (outputFile) fclose(outputFile);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), inputFile)) {
        printf("%s", line);
        fprintf(outputFile, "%s", line);
    }

    fclose(inputFile);
    fclose(outputFile);
}

void popis_ispitanika(int ukupno_bodova) {
    FILE* file = fopen("popis_ispitanika.txt", "a");
    if (!file) {
        printf("Greska pri otvaranju datoteke!\n");
        return;
    }
    fprintf(file, "\nUspjeh u bodovima: %d\n", ukupno_bodova);

    fclose(file);
}

position kreiranje_profila() {
    printf("\nUnos novog profila:\n");
    position newPerson = InputProfile();

    if (newPerson) {
        SaveProfileToFile(newPerson, "../Seed/profil_korisnika.txt");

        // Sortiranje popisa odmah nakon kreiranja profila
        TreeNode* root = NULL;
        readFileAndBuildTree("popis_ispitanika.txt", &root);

        FILE* file = fopen("popis_ispitanika.txt", "w");
        if (file == NULL) {
            printf("Greška pri otvaranju datoteke za pisanje.\n");
            return NULL;
        }

        sortiranje(root, file);
        fclose(file);
    }
    else {
        printf("Greška pri unosu profila.\n");
        return NULL;
    }
    return newPerson;
}

const char* rime_vj[] = { "most - kost", "livada - trava", "snijeg - brijeg", "lopta - krov", "ptica - skica" };
const char* fonemi_vj[] = { "m-o-s-t", "p-t-i-c-a", "t-r-a-v-a", "l-o-p-t-a", "s-k-i-c-a", "k-u-l-a" };
const char* slogovi_vj[] = { "ka-me-nje", "o-bi-telj", "sa-nja-ti", "sli-ka-ti", "bro-do-vi", "te-le-fon" };

int velicinar = sizeof(rime_vj) / sizeof(rime_vj[0]);
int velicinaf = sizeof(fonemi_vj) / sizeof(fonemi_vj[0]);
int velicinas = sizeof(slogovi_vj) / sizeof(slogovi_vj[0]);

void ispis_vjezbe_rime(const char* rime[], int velicina) {
    printf("Slijedi nekoliko zadataka za vjezbu prije ponovnog testiranja:\n");
    for (int i = 0; i < velicina; i++) {
        printf("%d. %s\n", i + 1, rime[i]);
    }
}

void ispis_vjezbe_slogova(const char* slog[], int velicina) {
    printf("Ispis slogova:\n");
    for (int i = 0; i < velicina; i++) {
        printf("%d. %s\n", i + 1, slog[i]);
    }
}

void ispis_vjezbe_fonema(const char* fonem[], int velicina) {
    printf("Ispis fonema:\n");
    for (int i = 0; i < velicina; i++) {
        printf("%d. %s\n", i + 1, fonem[i]);
    }
}

int vjezba_rime() {
    int bod;
    int brojac = 0;
    const char* naziv_zadatka = "rime";
    while (1) { // Petlja za rimu
        bod = unos_bodova(naziv_zadatka);

        if (bod < 8) {
            printf("\nRima nije dovoljno usvojena.\n");
            if (brojac == 0) {
                ispis_vjezbe_rime(rime_vj, velicinar);
                brojac++;
                continue;
            }
            continue;
        }
        else if (bod >= 8 && bod <= 15) {
            printf("\nRima je usvojena.\n");
            return bod;
            break;  // Izlaz iz petlje ako su bodovi valjani
        }
        else {
            printf("\nNa ovom zadatku nije moguæe ostvariti navedeni broj bodova. Pokušajte ponovno.\n");
        }
        brojac++;
    }
}
int vjezba_slogova() {
    int bod;
    int brojac = 0;
    const char* naziv_zadatka = "slogova";
    while (1) { // Petlja za slogove
        bod = unos_bodova(naziv_zadatka);

        if (bod < 12) {
            printf("\nSlogovi nisu dovoljno usvojeni. Slijedi nekoliko zadataka za vjezbu prije ponovnog testiranja.\n");
            if (brojac == 0) {
                ispis_vjezbe_slogova(slogovi_vj, velicinas);
                brojac++;
                continue;
            }
            continue;
        }
        else if (bod >= 12 && bod <= 14) {
            printf("\nSlogovi su usvojeni.\n");
            return bod;
            break;  // Izlaz iz petlje ako su bodovi valjani
        }
        else {
            printf("\nNa ovom zadatku nije moguæe ostvariti navedeni broj bodova. Pokušajte ponovno.\n");
        }
    }
}
int vjezba_fonema() {
    int bod;
    int brojac = 0;
    const char* naziv_zadatka = "fonema";
    while (1) { // Petlja za foneme
        bod = unos_bodova(naziv_zadatka);

        if (bod < 4) {
            printf("\nFonemi nisu dovoljno usvojeni. Slijedi nekoliko zadataka za vjezbu prije ponovnog testiranja.\n");
            if (brojac == 0){
                ispis_vjezbe_fonema(fonemi_vj, velicinaf);
                brojac++;
                continue;
            }
            continue;
        }
        else if (bod >= 4 && bod <= 14) {
            printf("\nFonemi su usvojeni.\n");
            return bod;
            break;  // Izlaz iz petlje ako su bodovi valjani
        }
        else {
            printf("\nNa ovom zadatku nije moguæe ostvariti navedeni broj bodova. Pokušajte ponovno.\n");
        }
    }
}

int main() {

    char izbor[4];
    srand(time(NULL));

    rima_zadaci("rima.txt");
    slogovni_zadaci("slogovi.txt");
    fonemski_zadaci("fonemi.txt");

    int opcija = 0;

    while (1) {
        printf("\nOdaberite opciju:\n");
        printf("1. Kreiranje profila i testiranje\n");
        printf("2. Vjezbanje\n");
        printf("3. Kraj\n");
        printf("Unesite broj opcije: ");
        fgets(izbor, sizeof(izbor), stdin);
        opcija = atoi(izbor);
        printf("\n");

        if (opcija == 1) {
            do {
                system("cls");
                position person = kreiranje_profila();

                printf("\nZadatak 1: Rima\n");
                rima_test("rima.txt");
                int bod_r = vjezba_rime(rime_vj, velicinar);

                printf("\nZadatak 2: Slogovna svjesnost\n");
                slogovi_test("slogovi.txt");
                int bod_s = vjezba_slogova(slogovi_vj, velicinas);

                printf("\nZadatak 3: Fonemska svjesnost\n");
                fonemi_test("fonemi.txt");
                int bod_f = vjezba_fonema(fonemi_vj, velicinaf);

                int ukupno_bodova = bod_r + bod_s + bod_f;
                printf("\nUkupni bodovi: %d\n", ukupno_bodova);
                printf("\n-------------------------------------------\n");
                printf("Ukupni bodovi za sve zadatke: %d\n", ukupno_bodova);
                if (ukupno_bodova >= 20) {
                    printf("Svjesnost jezika je na izvrsnoj razini!\n");
                }
                else {
                    printf("Rezultat nije zadovoljavajuci. Preporuka: nastaviti s vjezbanjem.\n");
                }

                popisivanje(person, "popis_ispitanika.txt", ukupno_bodova);

                printf("\nŽelite li ispitati još osoba? (da/ne): ");
                fgets(izbor, sizeof(izbor), stdin);
                izbor[strcspn(izbor, "\n")] = '\0';

            } while (strcmp(izbor, "da") == 0);
        }
        else if (opcija == 2) {
            system("cls");
            printf("Vjezbanje zapocinje. Pritisnite Enter za promjenu nasumicnih rijeci.\n");
            vjezba();
        }
        else if (opcija == 3) {
            break;
        }
        else {
            getchar();
            printf("Nepostojeca opcija. Molimo pokusajte ponovno.\n");
        }
    }

    return 0;
}
