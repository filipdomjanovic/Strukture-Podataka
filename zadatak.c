#define _CRT_SECURE_NO_WARNINGS
/* Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/

#include <stdio.h>
#include <stdlib.h>
#define MAXB 50
#define MAXSIZE 50
#define MAXRDULJ 120

typedef struct studenti {
    char ime[MAXSIZE];
    char prezime[MAXSIZE];
    double bodovi;
} stud;


int brojredaka();

int main(void)
{
    FILE* fp = fopen("ocjene.txt", "r");
    int i;
    int redci = brojredaka();
    stud *student = (stud*)malloc(redci * sizeof(stud));

    for (i = 0; i < redci; i++)
    {
        fscanf(fp, "%s %s %lf", student[i].ime, student[i].prezime, &student[i].bodovi);
    }

    for (i = 0; i < redci; i++)
    {
        printf("%s %s %.1lf %.1lf %% \n", student[i].ime, student[i].prezime, student[i].bodovi, (student[i].bodovi/MAXB) * 100);
    }
    
    fclose(fp);
    
    return 0;
}

int brojredaka()
{
    FILE* fp = fopen("ocjene.txt", "r");

    int brojac = 0;
    char bufflinija[MAXRDULJ];

    while (fgets(bufflinija, sizeof(bufflinija), fp))
    {
        brojac++;
    }

    fclose(fp);
    return brojac;
}# Strukture-Podataka
