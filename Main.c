// Main.c
#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"

int main()
{
    int izbor;
    do
    {
        clearScreen();
        printf(" __  _____\n");
        printf(" _\\_/_____\\______\n");
        printf(" |              |\n");
        printf(" '-(_)------(_)-'\n");
        printf(" AUTOKUCA - Dobrodosli!\n\n");
        printf(" 1. Dodaj auto\n");
        printf(" 2. Ispisi sve aute\n");
        printf(" 3. Azuriraj auto\n");
        printf(" 4. Obrisi auto\n");
        printf(" 5. Sortiraj\n");
        printf(" 6. Pretrazi\n");
        printf(" 7. Brisanje/Preimenovanje datoteke\n");
        printf(" 0. Izlaz\n");
        printf(" Izbor: ");
        scanf("%d", &izbor);
        getchar();
        clearScreen();
        switch (izbor)
        {
        case DODAJ:
            dodajAuto();
            break;
        case ISPISI:
            ispisiAute();
            break;
        case AZURIRAJ:
            azurirajAuto();
            break;
        case OBRISI:
            obrisiAuto();
            break;
        case SORTIRAJ:
            sortirajAute();
            break;
        case PRETRAZI:
            pretraziAuto();
            break;
        case REMOVE_RENAME:
            removeRenameDatoteka();
            break;
        }
    } while (izbor != IZLAZ);
    oslobodiMemoriju();
    return 0;
}
