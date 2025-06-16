#define _CRT_SECURE_NO_WARNINGS

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IME 50
#define MAX_BOJA 20
#define MAX_MOTOR 20
#define MAX_VERZIJA 20
#define MAX_TRANSMISIJA 20
#define MAX_AUTA 100
#define AUTI_FILE "auti.txt"

// Makro funkcija (koncept 9)
#define MAKS(a, b) ((a) > (b) ? (a) : (b))

// Enum za izbornik (koncept 11)
typedef enum {
    IZLAZ,
    DODAJ,
    ISPISI,
    AZURIRAJ,
    OBRISI,
    SORTIRAJ,
    PRETRAZI,
    REMOVE_RENAME
} GlavniIzbornik;

typedef enum {
    NE,
    DA
} OpcijaFinanciranja;

// Struktura za auto (koncepti 3, 4, 13)
typedef struct {
    char ime[MAX_IME];
    int godina;
    float kilometraza;
    float kubikaza;
    int brojCilindara;
    char vrstaMotora[MAX_MOTOR];
    char boja[MAX_BOJA];
    int brojVlasnika;
    char verzija[MAX_VERZIJA];
    char mjenjac[MAX_TRANSMISIJA];
    OpcijaFinanciranja financiranje;
    int garancija; 
} Auto;

// Funkcije (koncept 7)
void dodajAuto();
void ispisiAute();
void azurirajAuto();
void obrisiAuto();
void sortirajAute();
void pretraziAuto();
void removeRenameDatoteka();
void quickSortGodina(Auto* arr, int low, int high);
void oslobodiMemoriju();
void clearScreen();
int usporedbaGodinaAsc();
int usporedbaGodinaDesc();
int usporedbaImeAsc();
int usporedbaImeDesc();
int usporedbaKubikazaAsc();
int usporedbaKubikazaDesc();
int usporedbaVlasnikaAsc();
int usporedbaVlasnikaDesc();
int usporedbaGarancijaAsc();
int usporedbaGarancijaDesc();
void ucitajIzDatoteke();
void spremiUDatoteku();
float unesiKubikazu();
void unosStringa();
long velicinaDatoteke();

extern Auto* auti;
extern int brojAuta;

#endif
