#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

Auto* auti = NULL;
int brojAuta = 0;

// Static varijabla za brojač poziva funkcije ispisiAute (koncept 6)
static int brojPozivaIspisa = 0;

// Inline funkcija (koncept 9)
static inline int minInt(int a, int b)
{
    return a < b ? a : b;
}

void clearScreen() //Funkcija za ciscenja ekrana nakon izbora
{
    system(CLEAR_COMMAND);
}

void unosStringa(char* polje, int maxLen) {
    if (polje == NULL || maxLen <= 0) return;
    fgets(polje, maxLen, stdin);
    polje[strcspn(polje, "\n")] = 0;
}

float unesiKubikazu()
{
    char unos[32];
    printf("Unesi kubikazu (moze tocka ili zarez): ");
    if (fgets(unos, sizeof(unos), stdin) == NULL) {
        printf("Greska pri unosu kubikaze.\n");
        return 0.0f;
    }
    unos[strcspn(unos, "\n")] = 0;
    for (int i = 0; unos[i]; i++) {
        if (unos[i] == ',') {
            unos[i] = '.';
        }
    }
    return strtof(unos, NULL);
}

void ucitajIzDatoteke() //Funkcija ucitava sve zapisane podatke u datoteci
{
    FILE* f = fopen(AUTI_FILE, "r");
    if (!f) {
        brojAuta = 0;
        free(auti);
        auti = NULL;
        return;
    }

    Auto temp;
    brojAuta = 0;
    free(auti);
    auti = NULL;
    
    while (fscanf(f, "%49[^;];%d;%f;%f;%d;%19[^;];%19[^;];%d;%19[^;];%19[^;];%d;%d\n", //čitanje jednog retka iz datoteke gdje su podaci o autu zapisani odvojeni točka-zarezom
        temp.ime, &temp.godina, &temp.kilometraza, &temp.kubikaza, &temp.brojCilindara, 
        temp.vrstaMotora, temp.boja, &temp.brojVlasnika, temp.verzija, temp.mjenjac, 
        (int*)&temp.financiranje, &temp.garancija) == 12)
    {
        Auto* novi = realloc(auti, (brojAuta + 1) * sizeof(Auto));
        if (!novi)
        {
            perror("realloc");
            fclose(f);
            exit(1);
        }
        auti = novi;
        auti[brojAuta++] = temp;
    }
    fclose(f);
}

void spremiUDatoteku() //FUnkcija sprama zapisane aute u datoteku
{
    FILE* f = fopen(AUTI_FILE, "w");
    if (!f)
    {
        perror("fopen");
        return;
    }
    for (int i = 0; i < brojAuta; i++)
    {
        fprintf(f, "%s;%d;%.2f;%.2f;%d;%s;%s;%d;%s;%s;%d;%d\n",
            auti[i].ime, auti[i].godina, auti[i].kilometraza, auti[i].kubikaza, auti[i].brojCilindara,
            auti[i].vrstaMotora, auti[i].boja, auti[i].brojVlasnika, auti[i].verzija, auti[i].mjenjac,
            auti[i].financiranje, auti[i].garancija);
    }
    fclose(f);
}

void dodajAuto() //Funkcija za dodavanje auta u datoteku
{
    ucitajIzDatoteke();
    Auto novi;
    printf("Unesi ime auta: ");
    unosStringa(novi.ime, MAX_IME);
    printf("Unesi godinu: ");
    scanf("%d", &novi.godina);
    getchar();
    printf("Unesi kilometrazu: ");
    scanf("%f", &novi.kilometraza);
    getchar();
    novi.kubikaza = unesiKubikazu();
    printf("Unesi broj cilindara: ");
    scanf("%d", &novi.brojCilindara);
    getchar();
    printf("Unesi vrstu motora: ");
    unosStringa(novi.vrstaMotora, MAX_MOTOR);
    printf("Unesi boju: ");
    unosStringa(novi.boja, MAX_BOJA);
    printf("Unesi broj vlasnika: ");
    scanf("%d", &novi.brojVlasnika);
    getchar();
    printf ("Unesi verziju (limuzina, suv, karavan...): ");
    unosStringa(novi.verzija, MAX_VERZIJA);
    printf("Unesi vrstu mjenjaca: ");
    unosStringa(novi.mjenjac, MAX_TRANSMISIJA);
    printf("Opcija financiranja (0=Ne, 1=Da): ");
    scanf("%d", (int*)&novi.financiranje);
    getchar();
    printf("Garancija (u mjesecima): ");
    scanf("%d", &novi.garancija);
    getchar();
    Auto* noviA = realloc(auti, (brojAuta + 1) * sizeof(Auto));
    if (!noviA)
    {
        perror("realloc");
        exit(1);
    }
    auti = noviA;
    auti[brojAuta++] = novi;
    spremiUDatoteku();
    printf("Auto dodan!\n");
    printf("Pritisni Enter za povratak na izbornik...");
    getchar();
}

void ispisiAute()
{
    ucitajIzDatoteke();
    brojPozivaIspisa++; // static varijabla broji pozive
    if (brojAuta == 0)
    {
        printf("Nema auta.\n");
        printf("Pritisni Enter za povratak na izbornik...\n");
        getchar();
        return;
    }
    printf("Poziva funkcije ispisiAute: %d\n", brojPozivaIspisa);
    for (int i = 0; i < brojAuta; i++)
    {
        printf("Ime: %s | Godina: %d | Km: %.2f | Kubikaza: %.2f | Cilindara: %d | Motor: %s | Boja: %s | Vlasnika: %d | Verzija: %s | Mjenjac: %s | Financiranje: %s | Garancija: %d mj\n",
            auti[i].ime, auti[i].godina, auti[i].kilometraza, auti[i].kubikaza, auti[i].brojCilindara,
            auti[i].vrstaMotora, auti[i].boja, auti[i].brojVlasnika, auti[i].verzija, auti[i].mjenjac,
            auti[i].financiranje == DA ? "Da" : "Ne", auti[i].garancija);
    }
    printf("Pritisni Enter za povratak na izbornik...\n");
    getchar();
}

void azurirajAuto() {
    ucitajIzDatoteke();

    if (brojAuta == 0) {
        printf("Nema auta za azuriranje.\n");
        printf("Pritisni Enter za povratak na izbornik...\n");
        getchar();
        return;
    }

    char ime[MAX_IME];
    printf("Unesi ime auta za azuriranje (moze i djelomicno): ");
    unosStringa(ime, MAX_IME);

    int indeksi[MAX_AUTA];
    int brojPronadjenih = 0;
    for (int i = 0; i < brojAuta; i++) {
        if (strstr(auti[i].ime, ime) != NULL) {
            indeksi[brojPronadjenih++] = i;
        }
    }

    if (brojPronadjenih == 0) {
        printf("Nema auta koji odgovara unesenom imenu.\n");
        printf("Pritisni Enter za povratak na izbornik...\n");
        getchar();
        return;
    }
    else if (brojPronadjenih == 1) {
        int i = indeksi[0];
        printf("Pronadjen je jedan auto:\n");
        printf("%d. %s | Godina: %d | Km: %.2f | Kubikaza: %.2f | Boja: %s\n",
            1, auti[i].ime, auti[i].godina, auti[i].kilometraza, auti[i].kubikaza, auti[i].boja);

        printf("Jeste li sigurni da zelite azurirati ovaj auto? (1=Da, 0=Ne): ");
        int potvrda = 0;
        if (scanf("%d", &potvrda) != 1) {
            printf("Neispravan unos!\n");
            while (getchar() != '\n');
            return;
        }
        getchar();

        if (potvrda == 1) {
            printf("Nova godina: ");
            scanf("%d", &auti[i].godina);
            getchar();
            printf("Nova kilometraza: ");
            scanf("%f", &auti[i].kilometraza);
            getchar();
            printf("Nova kubikaza (moze tocka ili zarez): ");
            auti[i].kubikaza = unesiKubikazu();
            printf("Novi broj cilindara: ");
            scanf("%d", &auti[i].brojCilindara);
            getchar();
            printf("Nova vrsta motora: ");
            unosStringa(auti[i].vrstaMotora, MAX_MOTOR);
            printf("Nova boja: ");
            unosStringa(auti[i].boja, MAX_BOJA);
            printf("Novi broj vlasnika: ");
            scanf("%d", &auti[i].brojVlasnika);
            getchar();
            printf("Nova verzija: ");
            unosStringa(auti[i].verzija, MAX_VERZIJA);
            printf("Novi mjenjac: ");
            unosStringa(auti[i].mjenjac, MAX_TRANSMISIJA);
            printf("Opcija financiranja (0=Ne, 1=Da): ");
            scanf("%d", (int*)&auti[i].financiranje);
            getchar();
            printf("Garancija (u mjesecima): ");
            scanf("%d", &auti[i].garancija);
            getchar();

            spremiUDatoteku();
            printf("Auto azuriran!\n");
        }
        else {
            printf("Azuriranje otkazano.\n");
        }
    }
    else {
        printf("Pronadjeno vise auta:\n");
        for (int k = 0; k < brojPronadjenih; k++) {
            int i = indeksi[k];
            printf("%d. %s | Godina: %d | Km: %.2f | Kubikaza: %.2f | Boja: %s\n",
                k + 1, auti[i].ime, auti[i].godina, auti[i].kilometraza, auti[i].kubikaza, auti[i].boja);
        }
        printf("Unesi redni broj auta kojeg zelis azurirati: ");
        int izbor = 0;
        if (scanf("%d", &izbor) != 1) {
            printf("Neispravan unos!\n");
            while (getchar() != '\n');
            return;
        }
        getchar();

        if (izbor < 1 || izbor > brojPronadjenih) {
            printf("Neispravan izbor.\n");
        }
        else {
            int i = indeksi[izbor - 1];
            printf("Jeste li sigurni da zelite azurirati ovaj auto? (1=Da, 0=Ne): ");
            int potvrda = 0;
            if (scanf("%d", &potvrda) != 1) {
                printf("Neispravan unos!\n");
                while (getchar() != '\n');
                return;
            }
            getchar();

            if (potvrda == 1) {
                printf("Nova godina: ");
                scanf("%d", &auti[i].godina);
                getchar();
                printf("Nova kilometraza: ");
                scanf("%f", &auti[i].kilometraza);
                getchar();
                printf("Nova kubikaza (moze tocka ili zarez): ");
                auti[i].kubikaza = unesiKubikazu();
                printf("Novi broj cilindara: ");
                scanf("%d", &auti[i].brojCilindara);
                getchar();
                printf("Nova vrsta motora: ");
                unosStringa(auti[i].vrstaMotora, MAX_MOTOR);
                printf("Nova boja: ");
                unosStringa(auti[i].boja, MAX_BOJA);
                printf("Novi broj vlasnika: ");
                scanf("%d", &auti[i].brojVlasnika);
                getchar();
                printf("Nova verzija: ");
                unosStringa(auti[i].verzija, MAX_VERZIJA);
                printf("Novi mjenjac: ");
                unosStringa(auti[i].mjenjac, MAX_TRANSMISIJA);
                printf("Opcija financiranja (0=Ne, 1=Da): ");
                scanf("%d", (int*)&auti[i].financiranje);
                getchar();
                printf("Garancija (u mjesecima): ");
                scanf("%d", &auti[i].garancija);
                getchar();

                spremiUDatoteku();
                printf("Auto azuriran!\n");
            }
            else {
                printf("Azuriranje otkazano.\n");
            }
        }
    }
    printf("Pritisni Enter za povratak na izbornik...\n");
    getchar();
}


void obrisiAuto()
{
    ucitajIzDatoteke();

    if (brojAuta == 0)
    {
        printf("Nema auta za brisanje.\n");
        printf("Pritisni Enter za povratak na izbornik...\n");
        getchar();
        return;
    }

    char ime[MAX_IME];
    printf("Unesi ime auta za brisanje (moze i djelomicno): ");
    unosStringa(ime, MAX_IME);

    int indeksi[MAX_AUTA];
    int brojPronadjenih = 0;
    for (int i = 0; i < brojAuta; i++)
    {
        if (strstr(auti[i].ime, ime) != NULL)
        {
            indeksi[brojPronadjenih++] = i;
        }
    }

    if (brojPronadjenih == 0)
    {
        printf("Nema auta koji odgovara unesenom imenu.\n");
        printf("Pritisni Enter za povratak na izbornik...\n");
        getchar();
        return;
    }
    else if (brojPronadjenih == 1)
    {
        int i = indeksi[0];
        printf("Pronadjen je jedan auto:\n");
        printf("%d. %s | Godina: %d | Km: %.2f | Kubikaza: %.2f | Boja: %s\n", 1, auti[i].ime, auti[i].godina, auti[i].kilometraza, auti[i].kubikaza, auti[i].boja);

        printf("Jeste li sigurni da želite obrisati ovaj auto? (1=Da, 0=Ne): ");
        int potvrda = 0;
        if (scanf("%d", &potvrda) != 1)
        {
            printf("Neispravan unos!\n");
            while (getchar() != '\n');
            return;
        }
        getchar();

        if (potvrda == 1)
        {
            for (int j = indeksi[0]; j < brojAuta - 1; j++)
            {
                auti[j] = auti[j + 1];
            }
            brojAuta--;
            spremiUDatoteku();
            printf("Auto obrisan.\n");
        }
        else
        {
            printf("Brisanje otkazano.\n");
        }
    }
    else
    {
        printf("Pronađeno više auta:\n");
        for (int k = 0; k < brojPronadjenih; k++)
        {
            int i = indeksi[k];
            printf("%d. %s | Godina: %d | Km: %.2f | Kubikaza: %.2f | Boja: %s\n",
                k + 1, auti[i].ime, auti[i].godina, auti[i].kilometraza, auti[i].kubikaza, auti[i].boja);
        }
        printf("Unesi redni broj auta kojeg želiš obrisati: ");
        int izbor = 0;
        if (scanf("%d", &izbor) != 1)
        {
            printf("Neispravan unos!\n");
            while (getchar() != '\n');
            return;
        }
        getchar();

        if (izbor < 1 || izbor > brojPronadjenih)
        {
            printf("Neispravan izbor.\n");
        }
        else
        {
            int indexZaBrisanje = indeksi[izbor - 1];
            printf("Jeste li sigurni da želite obrisati ovaj auto? (1=Da, 0=Ne): ");
            int potvrda = 0;
            if (scanf("%d", &potvrda) != 1)
            {
                printf("Neispravan unos!\n");
                while (getchar() != '\n');
                return;
            }
            getchar();

            if (potvrda == 1)
            {
                for (int j = indexZaBrisanje; j < brojAuta - 1; j++)
                {
                    auti[j] = auti[j + 1];
                }
                brojAuta--;
                spremiUDatoteku();
                printf("Auto obrisan.\n");
            }
            else
            {
                printf("Brisanje otkazano.\n");
            }
        }
    }

    printf("Pritisni Enter za povratak na izbornik...\n");
    getchar();
}

int usporedbaGodinaAsc(const void* a, const void* b)
{
    return ((Auto*)a)->godina - ((Auto*)b)->godina;
}
int usporedbaGodinaDesc(const void* a, const void* b)
{
    return ((Auto*)b)->godina - ((Auto*)a)->godina;
}
int usporedbaImeAsc(const void* a, const void* b)
{
    return strcmp(((Auto*)a)->ime, ((Auto*)b)->ime);
}
int usporedbaImeDesc(const void* a, const void* b)
{
    return strcmp(((Auto*)b)->ime, ((Auto*)a)->ime);
}
int usporedbaKubikazaAsc(const void* a, const void* b)
{
    float k1 = ((Auto*)a)->kubikaza, k2 = ((Auto*)b)->kubikaza;
    return (k1 > k2) - (k1 < k2);
}
int usporedbaKubikazaDesc(const void* a, const void* b)
{
    float k1 = ((Auto*)a)->kubikaza, k2 = ((Auto*)b)->kubikaza;
    return (k2 > k1) - (k2 < k1);
}
int usporedbaVlasnikaAsc(const void* a, const void* b)
{
    return ((Auto*)a)->brojVlasnika - ((Auto*)b)->brojVlasnika;
}
int usporedbaVlasnikaDesc(const void* a, const void* b)
{
    return ((Auto*)b)->brojVlasnika - ((Auto*)a)->brojVlasnika;
}
int usporedbaGarancijaAsc(const void* a, const void* b)
{
    return ((Auto*)a)->garancija - ((Auto*)b)->garancija;
}
int usporedbaGarancijaDesc(const void* a, const void* b)
{
    return ((Auto*)b)->garancija - ((Auto*)a)->garancija;
}

void quickSortGodina(Auto* arr, int low, int high)
{
    if (low < high)
    {
        int pivot = arr[high].godina;
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if (arr[j].godina <= pivot)
            {
                i++;
                Auto temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        Auto temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = i + 1;
        quickSortGodina(arr, low, pi - 1);
        quickSortGodina(arr, pi + 1, high);
    }
}

void sortirajAute()
{
    ucitajIzDatoteke();
    if (brojAuta == 0)
    {
        printf("Nema auta.\n");
        printf("Pritisni Enter za povratak na izbornik...\n");
        getchar();
        return;
    }
    int izbor, smjer;
    printf("Sortiraj po: 1-Godina 2-Ime 3-Kubikaza 4-Broj vlasnika 5-Garancija\nIzbor: ");
    scanf("%d", &izbor);
    printf("Smjer: 1-Uzlazno 2-Silazno: ");
    scanf("%d", &smjer);
    getchar();
    if (izbor == 1 && smjer == 1)
    {
        quickSortGodina(auti, 0, brojAuta - 1);
    }
    else if (izbor == 1 && smjer == 2)
    {
        qsort(auti, brojAuta, sizeof(Auto), usporedbaGodinaDesc);
    }
    else if (izbor == 2 && smjer == 1)
    {
        qsort(auti, brojAuta, sizeof(Auto), usporedbaImeAsc);
    }
    else if (izbor == 2 && smjer == 2)
    {
        qsort(auti, brojAuta, sizeof(Auto), usporedbaImeDesc);
    }
    else if (izbor == 3 && smjer == 1)
    {
        qsort(auti, brojAuta, sizeof(Auto), usporedbaKubikazaAsc);
    }
    else if (izbor == 3 && smjer == 2)
    {
        qsort(auti, brojAuta, sizeof(Auto), usporedbaKubikazaDesc);
    }
    else if (izbor == 4 && smjer == 1)
    {
        qsort(auti, brojAuta, sizeof(Auto), usporedbaVlasnikaAsc);
    }
    else if (izbor == 4 && smjer == 2)
    {
        qsort(auti, brojAuta, sizeof(Auto), usporedbaVlasnikaDesc);
    }
    else if (izbor == 5 && smjer == 1)
    {
        qsort(auti, brojAuta, sizeof(Auto), usporedbaGarancijaAsc);
    }
    else if (izbor == 5 && smjer == 2)
    {
        qsort(auti, brojAuta, sizeof(Auto), usporedbaGarancijaDesc);
    }
    else
    {
        printf("Neispravan izbor.\n");
        printf("Pritisni Enter za povratak na izbornik...\n");
        getchar();
        return;
    }
    spremiUDatoteku();
    ispisiAute();
}

int usporedbaImeBsearch(const void* a, const void* b)
{
    return strcmp(((Auto*)a)->ime, ((Auto*)b)->ime);
}

void pretraziAuto() 
{
    ucitajIzDatoteke();

    if (brojAuta == 0)
    {
        printf("Nema auta.\n");
        printf("Pritisni Enter za povratak na izbornik...\n");
        getchar();
        return;
    }

    int izbor;
    printf("Pretraga po: 1-Ime 2-Godina 3-Kilometraza: ");
    scanf("%d", &izbor);
    getchar();

    if (izbor == 1)
    {
        char ime[MAX_IME];
        printf("Unesi ime auta: ");
        unosStringa(ime, MAX_IME);
        qsort(auti, brojAuta, sizeof(Auto), usporedbaImeAsc);
        Auto kljuc;
        strncpy(kljuc.ime, ime, MAX_IME);
        Auto* pronadjen = bsearch(&kljuc, auti, brojAuta, sizeof(Auto), usporedbaImeAsc); //bsearch radi samo za jednu varijablu zato nemoze ispisati vise auta odjednom

        if (pronadjen)
        {
            printf("Ime: %s | Godina: %d | Km: %.2f | Kubikaza: %.2f | Cilindara: %d | Motor: %s | Boja: %s | Vlasnika: %d | Verzija: %s | Mjenjac: %s | Financiranje: %s | Garancija: %d mj\n",
                pronadjen->ime, pronadjen->godina, pronadjen->kilometraza, pronadjen->kubikaza, pronadjen->brojCilindara,
                pronadjen->vrstaMotora, pronadjen->boja, pronadjen->brojVlasnika, pronadjen->verzija, pronadjen->mjenjac,
                pronadjen->financiranje == DA ? "Da" : "Ne", pronadjen->garancija);
        }
        else
        {
            printf("Nema rezultata.\n");
        }
    }
    else if (izbor == 2)
    {
        int godina;
        printf("Unesi godinu: ");
        scanf("%d", &godina);
        getchar();
        int nadjeno = 0;
        for (int i = 0; i < brojAuta; i++)
        {
            if (auti[i].godina == godina)
            {
                printf("Ime: %s | Godina: %d | Km: %.2f | Kubikaza: %.2f | Cilindara: %d | Motor: %s | Boja: %s | Vlasnika: %d | Verzija: %s | Mjenjac: %s | Financiranje: %s | Garancija: %d mj\n",
                    auti[i].ime, auti[i].godina, auti[i].kilometraza, auti[i].kubikaza, auti[i].brojCilindara,
                    auti[i].vrstaMotora, auti[i].boja, auti[i].brojVlasnika, auti[i].verzija, auti[i].mjenjac,
                    auti[i].financiranje == DA ? "Da" : "Ne", auti[i].garancija);
                nadjeno = 1;
            }
        }
        if (!nadjeno)
        {
            printf("Nema rezultata.\n");
        }
    }
    else if (izbor == 3)
    {
        float km;
        printf("Unesi kilometrazu: ");
        scanf("%f", &km);
        getchar();
        int nadjeno = 0;
        for (int i = 0; i < brojAuta; i++)
        {
            if (auti[i].kilometraza == km)
            {
                printf("Ime: %s | Godina: %d | Km: %.2f | Kubikaza: %.2f | Cilindara: %d | Motor: %s | Boja: %s | Vlasnika: %d | Verzija: %s | Mjenjac: %s | Financiranje: %s | Garancija: %d mj\n",
                    auti[i].ime, auti[i].godina, auti[i].kilometraza, auti[i].kubikaza, auti[i].brojCilindara,
                    auti[i].vrstaMotora, auti[i].boja, auti[i].brojVlasnika, auti[i].verzija, auti[i].mjenjac,
                    auti[i].financiranje == DA ? "Da" : "Ne", auti[i].garancija);
                nadjeno = 1;
            }
        }
        if (!nadjeno)
        {
            printf("Nema rezultata.\n");
        }
    }
    else
    {
        printf("Neispravan izbor.\n");
    }

    printf("Pritisni Enter za povratak na izbornik...\n");
    getchar();
}


void removeRenameDatoteka()
{
    printf("1. Obrisi datoteku\n2. Preimenuj datoteku\nIzbor: ");
    int izbor;
    scanf("%d", &izbor);
    getchar();
    if (izbor == 1)
    {
        if (remove(AUTI_FILE) == 0)
        {
            printf("Datoteka obrisana.\n");
        }
        else
        {
            perror("Greska pri brisanju");
        }
    }
    else if (izbor == 2)
    {
        char novoIme[50];
        printf("Unesi novo ime datoteke: ");
        unosStringa(novoIme, 50);
        if (rename(AUTI_FILE, novoIme) == 0)
        {
            printf("Datoteka preimenovana.\n");
        }
        else
        {
            perror("Greska pri preimenovanju");
        }
    }
    else
    {
        printf("Neispravan izbor.\n");
    }
    printf("Pritisni Enter za povratak na izbornik...\n");
    getchar();
}

void oslobodiMemoriju()
{
    free(auti);
    auti = NULL;
    brojAuta = 0;
}
