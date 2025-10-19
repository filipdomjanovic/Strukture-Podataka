<<<<<<< HEAD
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person* Position;
typedef struct Person
{
	char name[50];
	char surname[50];
	int birth_year;
	Position Next;
}NewPerson;

int InputStart(char* name, char* surname, int birth_year, Position P);
int Printing(Position P);
int InputEnd(char* name, char* surname, int birth_year, Position P);
int FindElement(char* surname, Position P);
int PopElement(char* surname, Position P);

int main()
{
	NewPerson Head = { .name = "",.surname = "",.birth_year = 0,.Next = NULL };
	char choice;
	do
	{
		printf("\nSto zelis:\n  A) Dodati osobu na pocetak\n  B) Dodati osobu na kraj\n  C) Ispisati listu\n  D) Pronaci osobu po prezimenu\n  E) Izbrisati osobu\n  F) KRAJ\n");
		printf("Izbor:  ");
		scanf(" %c", &choice);

		switch (choice)
		{
		case 'a':
		case 'A':
			printf("Izabrali ste A:\n");
			printf("Ime: "); scanf("%s", Head.name);
			printf("Prezime: "); scanf("%s", Head.surname);
			printf("Godina Rodenja: "); scanf("%d", &Head.birth_year);
			InputStart(Head.name, Head.surname, Head.birth_year, &Head);
			break;
		case 'b':
		case 'B':
			printf("Izabrali ste B:\n");
			printf("Ime: "); scanf("%s", Head.name);
			printf("Prezime: "); scanf("%s", Head.surname);
			printf("Godina Rodenja: "); scanf("%d", &Head.birth_year);
			InputEnd(Head.name, Head.surname, Head.birth_year, &Head);
			break;
		case 'c':
		case 'C':
			printf("Izabrali ste C:\n");
			Printing(Head.Next);
			break;
		case 'd':
		case 'D':
			printf("Izabrali ste D:\n");
			printf("Koga trazite(prezime): ");
			scanf("%s", Head.surname);
			FindElement(Head.surname, &Head);
			break;
		case 'e':
		case 'E':
			printf("Izabrali ste E:\n");
			printf("Koga zelite maknuti(prezime): ");
			scanf("%s", Head.surname);
			PopElement(Head.surname, &Head);
			break;
		case 'f':
			return 0;
		}
	} while (choice != 'F');

	Position current = Head.Next, temp;
	while (current != NULL)
	{
		temp = current;
		current = current->Next;
		free(temp);
	}
	return 0;
}

int InputStart(char* name, char* surname, int birth_year, Position P)
{
	Position q;
	q = (Position)malloc(sizeof(NewPerson));

	strcpy(q->name, name);
	strcpy(q->surname, surname);
	q->birth_year = birth_year;
	q->Next = P->Next;
	P->Next = q;
	return 0;
}

int InputEnd(char* name, char* surname, int birth_year, Position P)
{
	Position q;

	while (P->Next != NULL)
		P = P->Next;
	q = (Position)malloc(sizeof(NewPerson));
	strcpy(q->name, name);
	strcpy(q->surname, surname);
	q->birth_year = birth_year;
	q->Next = NULL;
	P->Next = q;
	return 0;
}
int Printing(Position P)
{
	printf("\nLista osoba:\n");
	while (P != NULL)
	{
		printf(" %s %s %d\n", P->name, P->surname, P->birth_year);
		P = P->Next;
	}
	return 0;
}

int FindElement(char* surname, Position P)
{
	P = P->Next;
	while (P != NULL)
	{
		if (strcmp(P->surname, surname) == 0)
		{
			printf("Osoba je tu: %s %s %d\n", P->name, P->surname, P->birth_year);
			return 1;
		}
		P = P->Next;
	}
	printf("Osobe nema.\n");
	return 0;
}

int PopElement(char* surname, Position Head)
{
	Position temp = Head;
	
	while (temp != NULL)
	{
		if (strcmp(temp->Next->surname, surname) == 0)
		{
			Position ToDelete = temp->Next;
			temp->Next = ToDelete->Next;
			free(ToDelete);
			return 0;
		}
		temp = temp->Next;
	}
	
	return 0;
=======
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person* Position;
typedef struct Person
{
	char name[50];
	char surname[50];
	int birth_year;
	Position Next;
}NewPerson;

int InputStart(char* name, char* surname, int birth_year, Position P);
int Printing(Position P);
int InputEnd(char* name, char* surname, int birth_year, Position P);
int FindElement(char* surname, Position P);
int PopElement(char* surname, Position P);

int main()
{
	NewPerson Head = { .name = "",.surname = "",.birth_year = 0,.Next = NULL };
	char choice;
	do
	{
		printf("\nSto zelis:\n  A) Dodati osobu na pocetak\n  B) Dodati osobu na kraj\n  C) Ispisati listu\n  D) Pronaci osobu po prezimenu\n  E) Izbrisati osobu\n  F) KRAJ\n");
		printf("Izbor:  ");
		scanf(" %c", &choice);

		switch (choice)
		{
		case 'a':
		case 'A':
			printf("Izabrali ste A:\n");
			printf("Ime: "); scanf("%s", Head.name);
			printf("Prezime: "); scanf("%s", Head.surname);
			printf("Godina Rodenja: "); scanf("%d", &Head.birth_year);
			InputStart(Head.name, Head.surname, Head.birth_year, &Head);
			break;
		case 'b':
		case 'B':
			printf("Izabrali ste B:\n");
			printf("Ime: "); scanf("%s", Head.name);
			printf("Prezime: "); scanf("%s", Head.surname);
			printf("Godina Rodenja: "); scanf("%d", &Head.birth_year);
			InputEnd(Head.name, Head.surname, Head.birth_year, &Head);
			break;
		case 'c':
		case 'C':
			printf("Izabrali ste C:\n");
			Printing(Head.Next);
			break;
		case 'd':
		case 'D':
			printf("Izabrali ste D:\n");
			printf("Koga trazite(prezime): ");
			scanf("%s", Head.surname);
			FindElement(Head.surname, &Head);
			break;
		case 'e':
		case 'E':
			printf("Izabrali ste E:\n");
			printf("Koga zelite maknuti(prezime): ");
			scanf("%s", Head.surname);
			PopElement(Head.surname, &Head);
			break;
		case 'f':
			return 0;
		}
	} while (choice != 'F');

	Position current = Head.Next, temp;
	while (current != NULL)
	{
		temp = current;
		current = current->Next;
		free(temp);
	}
	return 0;
}

int InputStart(char* name, char* surname, int birth_year, Position P)
{
	Position q;
	q = (Position)malloc(sizeof(NewPerson));

	strcpy(q->name, name);
	strcpy(q->surname, surname);
	q->birth_year = birth_year;
	q->Next = P->Next;
	P->Next = q;
	return 0;
}

int InputEnd(char* name, char* surname, int birth_year, Position P)
{
	Position q;

	while (P->Next != NULL)
		P = P->Next;
	q = (Position)malloc(sizeof(NewPerson));
	strcpy(q->name, name);
	strcpy(q->surname, surname);
	q->birth_year = birth_year;
	q->Next = NULL;
	P->Next = q;
	return 0;
}
int Printing(Position P)
{
	printf("\nLista osoba:\n");
	while (P != NULL)
	{
		printf(" %s %s %d\n", P->name, P->surname, P->birth_year);
		P = P->Next;
	}
	return 0;
}

int FindElement(char* surname, Position P)
{
	P = P->Next;
	while (P != NULL)
	{
		if (strcmp(P->surname, surname) == 0)
		{
			printf("Osoba je tu: %s %s %d\n", P->name, P->surname, P->birth_year);
			return 1;
		}
		P = P->Next;
	}
	printf("Osobe nema.\n");
	return 0;
}

int PopElement(char* surname, Position Head)
{
	Position temp = Head;
	
	while (temp != NULL)
	{
		if (strcmp(temp->Next->surname, surname) == 0)
		{
			Position ToDelete = temp->Next;
			temp->Next = ToDelete->Next;
			free(ToDelete);
			return 0;
		}
		temp = temp->Next;
	}
	
	return 0;
>>>>>>> d6333f1c0132d56dd7291a79f5546da3e1a20b69
}# Strukture-Podataka
# Strukture-Podataka
# Strukture-Podataka
