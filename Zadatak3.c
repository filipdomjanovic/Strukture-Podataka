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
int InputBefore(char* name, char* surname, int birth_year, char* wsurname, Position P);
int InputAfter(char* name, char* surname, int birth_year, char* wsurname, Position P);
void SortList(Position P);
int FileSave(Position P);
int FileLoad(Position P);

int main()
{
	NewPerson Head = { .name = "",.surname = "",.birth_year = 0,.Next = NULL };
	char choice;
	char temps[50];
	do
	{
		printf("\nSto zelis:\n  A) Dodati osobu na pocetak\n  B) Dodati osobu na kraj\n  C) Ispisati listu\n  D) Pronaci osobu po prezimenu\n  E) Izbrisati osobu\n  G) Dodati nekog ispred nekog\n  H) Dodati nekog iza nekog\n  F) KRAJ\n");
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
		case 'g':
		case 'G':
			printf("Izabrali ste G:\n");
			printf("Ispred koga zelite dodati: "); scanf("%s", temps);
			printf("A koga:\n");
			printf("Ime: "); scanf("%s", Head.name);
			printf("Prezime: "); scanf("%s", Head.surname);
			printf("Godina Rodenja: "); scanf("%d", &Head.birth_year);
			InputBefore(Head.name, Head.surname, Head.birth_year, temps, &Head);
			break;
		case 'h':
		case 'H':
			printf("Izabrali ste H:\n");
			printf("Iza koga zelite dodati: "); scanf("%s", temps);
			printf("A koga:\n");
			printf("Ime: "); scanf("%s", Head.name);
			printf("Prezime: "); scanf("%s", Head.surname);
			printf("Godina Rodenja: "); scanf("%d", &Head.birth_year);
			InputAfter(Head.name, Head.surname, Head.birth_year, temps, &Head);
			break;
		case 'i':
		case 'I':
			printf("Izabrali ste I:\n");
			SortList(&Head);
			Printing(Head.Next);
			break;
		case 'j':
		case 'J':
			printf("Izabrali ste J:\n");
			FileSave(&Head);
			break;
		case 'k':
		case 'K':
			printf("Izabrali ste K:\n");
			FileLoad(&Head);
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
}
int InputBefore(char* name, char* surname, int birth_year, char* wsurname, Position P)
{
	Position q;

	while (P->Next != NULL && strcmp(P->Next->surname, wsurname) != 0)
	{
		P = P->Next;
	}
	if (P != NULL)
	{
		q = (Position)malloc(sizeof(NewPerson));
		strcpy(q->name, name);
		strcpy(q->surname, surname);
		q->birth_year = birth_year;
		q->Next = P->Next;
		P->Next = q;
	}
	return 0;
}
int InputAfter(char* name, char* surname, int birth_year, char* wsurname, Position P)
{
	Position q;

	while (P->Next != NULL && strcmp(P->surname, wsurname) != 0)
	{
		P = P->Next;
	}
	if (P != NULL)
	{
		q = (Position)malloc(sizeof(NewPerson));
		strcpy(q->name, name);
		strcpy(q->surname, surname);
		q->birth_year = birth_year;
		q->Next = P->Next;
		P->Next = q;
	}
	return 0;
}
void SortList(Position P)
{
	Position x, prev_x, temp, end;
	end = NULL;

	while (P->Next != end)
	{
		prev_x = P;
		x = P->Next;
		while(x->Next != end)
		{
			if(strcmp(x->surname,x->Next->surname)>0)
			{
				temp = x->Next;
				prev_x->Next = temp;
				x->Next = temp->Next;
				temp->Next = x;

				x = temp;
				
			}
			else 
			{
				prev_x = x;
				x = x->Next;
			}
		}
		end = x;
	}
}
int FileSave(Position P)
{
	FILE* fp = fopen("persons.txt", "w");
	P = P->Next;
	while (P != NULL)
	{
		fprintf(fp, "%s	%s	%d\n", P->name, P->surname, P->birth_year);
		P = P->Next;
	}
	
	fclose(fp);
	return 0;
}
int FileLoad(Position P)
{
	FILE* fp = fopen("persons.txt", "r");
	char name[50], surname[50];
	int birth_year;
	while (fscanf(fp, "%49s %49s %d", name, surname, &birth_year) == 3)
	{
		InputEnd(name, surname, birth_year, P); 
	}
	fclose(fp);
	return 0;
}
# Strukture-Podataka
# Strukture-Podataka
# Strukture-Podataka
# Strukture-Podataka
# Strukture-Podataka
# Strukture-Podataka
