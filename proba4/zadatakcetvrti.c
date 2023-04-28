/*4.	Iz datoteke osobe.txt proèitati imena osoba i njihov matièni broj. Izgraditi vezanu listu osoba.
Nakon toga, iz datoteke testiranja.txt proèitati datum dogovorenog testiranja za pojedinu osobu i njen matièni broj te od tih
podataka kreirati novu vezanu listu.
Ocjena 2:
Za uneseni datum ispisati imena svih osoba koje su na taj dan naruèene na testiranje.
Napomena 1:
Paziti na uredno oslobaðanje memorije na kraju programa, uspješno/neuspješno alociranje memorije te otvaranje i
zatvaranje datoteka.
Zabranjeno korištenje globalnih varijabli.
Napomena 2:
U datoteci osobe.txt prvo ide matièni broj, pa prezime i zatim ime.
U datoteci testiranja.txt prvo ide matièni broj pa datum (u formatu DD.MM.YYYY.).
    Napomena 3:
U rješavanju zadatka koristiti sljedeæe strukture:
struct Osoba {
        char ime[20], prezime[20];
        int maticniBroj;
        struct Osoba* nextOsoba;
};
    struct Datum {
        int day, mjesec, godina;
};
    struct Test {
        int maticniBroj;
        struct Datum datumTestiranja;
        struct Test* nextTest;
};
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _osobe;
typedef struct _osobe osobe;
typedef osobe* position;

struct _test;
typedef struct _test test;
typedef test* pozicija;

struct Datum {

    int dan, mjesec, godina;
};

struct _osobe {

    int id;
    char ime[20];
    char prezime[20];

    position next;
};

struct _test {

    int id;
    struct Datum dattest;

    pozicija next;
};


int CitajDatOsobe(position head);
int UnesiUListuOsobe(position head, int id, char ime[20], char prezime[20]);
int CitajDatTest(pozicija head);
int UnesiUListuTest(pozicija head, int id, struct Datum datumtesta);
int TraziDatum(position head_osobe, pozicija head_test);
int IspisOsobe(position head, int id);


int main()
{

    osobe head_osobe;
    head_osobe.next = NULL;

    test head_test;
    head_test.next = NULL;

    int result;

    result = CitajDatOsobe(&head_osobe);
    result = CitajDatTest(&head_test);
    result = TraziDatum(&head_osobe, &head_test);


    return 0;
}

int CitajDatOsobe(position head)
{
    char buffer[1024] = "\0";
    int id;
    char ime[20] = "\0";
    char prezime[20] = "\0";
    int result;

    FILE* file;
    file = fopen("osobe.txt", "r");
    if (file == NULL)
    {
        return -1;
    }

    while (!feof(file))
    {
        strcpy(buffer, "\0");
        strcpy(ime, "\0");
        strcpy(prezime, "\0");
        id = 0;

        fgets(buffer, 1024 - 1, file);
            if (strlen(buffer) > 1)
            {
                sscanf(buffer, "%d %s %s", &id, ime, prezime);
            }
            result = UnesiUListuOsobe(head, id, ime, prezime);
            if (result == -1)
            {
                fclose(file);
                return -1;
            }
    }
    fclose(file);
    return 0;
}

int UnesiUListuOsobe(position head, int id, char ime[20], char prezime[20])
{
    position temp;
    temp = (position)malloc(sizeof(osobe));

    if (temp == NULL)
    {
        printf("nije se alociralo");
        return -1;
    }

    temp->id = id;
    strcpy(temp->ime, ime);
    strcpy(temp->prezime, prezime);

    while (head->next != NULL)
    {
        head = head->next;
    }

    temp->next = NULL;
    head->next = temp;

    return 0;
}

int CitajDatTest(pozicija head)
{
    char buffer[1024] = "\0";
    int id;
    struct Datum datumtesta;
    int result;

    FILE* file;
    file = fopen("testiranja.txt", "r");
    if (file == NULL)
    {
        return -1;
    }

    while (!feof(file))
    {
        strcpy(buffer, "\0");
        
        id = 0;

        fgets(buffer, 1024 - 1, file);
        if (strlen(buffer) > 1)
        {
            sscanf(buffer, "%d %d.%d.%d.", &id, &datumtesta.dan, &datumtesta.mjesec, &datumtesta.godina);
        }
        result = UnesiUListuTest(head, id, datumtesta);
        if (result == -1)
        {
            fclose(file);
            return -1;
        }
    }
    fclose(file);
    return 0;








    return 0;
}

int UnesiUListuTest(pozicija head, int id, struct Datum datumtesta)
{
    pozicija temp;
    temp = (pozicija)malloc(sizeof(test));

    temp->id = id;
    temp->dattest.dan = datumtesta.dan;
    temp->dattest.mjesec = datumtesta.mjesec;
    temp->dattest.godina = datumtesta.godina;

    while (head->next != NULL)
    {
        head = head->next;
    }
    
    temp->next = NULL;
    head->next = temp;

    return 0;
}

int TraziDatum(position head_osobe, pozicija head_test)
{
    int result;
    head_test = head_test->next;
    struct Datum datum;
    printf("upisite datum: dan <enter> mjesec <enter> godina <enter>\n");

    scanf("%d", &datum.dan);
    scanf("%d", &datum.mjesec);
    scanf("%d", &datum.godina);
    printf("\n na ovaj datum naruceni su ovi ljudi \n");

    while (head_test != NULL)
    {
        if (head_test->dattest.dan == datum.dan && head_test->dattest.mjesec == datum.mjesec && head_test->dattest.godina == datum.godina)
        {
            result = IspisOsobe(head_osobe, head_test->id);
        }
        head_test = head_test->next;
    }
    return 0;
}


int IspisOsobe(position head, int id)
{
    if (head->next == NULL)
    {
        printf("NULL");

    }
    else
    {
        head = head->next;
        while (head != NULL)
        {
            if (id == head->id)
            {
                printf("\n%d %s %s", head->id, head->ime, head->prezime);
            }
        
            head = head->next;
            
        }
    }

    return 0;
}
















































