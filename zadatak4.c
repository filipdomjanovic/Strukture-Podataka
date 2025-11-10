#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct polynome* Position;
typedef struct polynome{
	int coefficient;
	int power;
	Position Next;
}polynomes;

int FileRead(Position Head, const char* filepath);
int SortedInput(Position Head, int coefficient, int power);
int Addition(Position Head1, Position Head2, Position HeadR);
int Multiplication(Position Head1, Position Head2, Position HeadR);
int PrintPoly(Position Head);
void FreePoly(Position Head);

int main()
{
	polynomes Head = { .coefficient = 0, .power = 0,.Next = NULL };
	polynomes FirstPoly = { .coefficient = 0, .power = 0,.Next = NULL };
	polynomes SecondPoly = { .coefficient = 0, .power = 0,.Next = NULL };
	polynomes ResultPolyA = { .coefficient = 0, .power = 0,.Next = NULL };
	polynomes ResultPolyM = { .coefficient = 0, .power = 0,.Next = NULL };

	FileRead(&FirstPoly,"polynome1.txt");
	FileRead(&SecondPoly,"polynome2.txt"); 

	printf("Prvi : ");
	PrintPoly(&FirstPoly);
	printf("\nDrugi : ");
	PrintPoly(&SecondPoly);

	Addition(&FirstPoly, &SecondPoly, &ResultPolyA);
	printf("\nZbroj: ");
	PrintPoly(&ResultPolyA);

	Multiplication(&FirstPoly, &SecondPoly, &ResultPolyM);
	printf("\nProdukt : ");
	PrintPoly(&ResultPolyM);

	FreePoly(FirstPoly.Next);
	FreePoly(SecondPoly.Next);
	FreePoly(ResultPolyA.Next);
	FreePoly(ResultPolyM.Next);


return EXIT_SUCCESS;
}


int FileRead(Position Head, const char* filepath)
{
	FILE* fp = fopen(filepath, "r");
	if (fp == NULL)
	{
		printf("Error file opening");
		return EXIT_FAILURE;
	}
	int NumBytes;
	int c, p;
	char* ptr;
	char buffer[1024];

	fgets(buffer, sizeof(buffer), fp);

	ptr = buffer;
	while (*ptr != '\0')
	{
		if (sscanf(ptr, "%d %d %n", &c, &p, &NumBytes) == 2)
		{
			ptr = ptr + NumBytes;
			SortedInput(Head, c, p);
		}
		else break;
	}
	fclose(fp);

	return EXIT_SUCCESS;
}

int SortedInput(Position Head, int co, int po)
{
	Position NewEl;
	Position CurretEl = Head;

	if (Head == NULL)
	{
		printf("Error: Head is NULL\n");
		return EXIT_FAILURE;
	}

	NewEl = (Position)malloc(sizeof(polynomes));
	if (NewEl == NULL)
	{
		printf("Erroe allocating memmory");
		return EXIT_FAILURE;
	}
	NewEl->coefficient = co;
	NewEl->power = po;
	NewEl->Next = NULL;

	if (Head->Next == NULL || po > Head->Next->power)
	{
		NewEl->Next = Head->Next;
		Head->Next = NewEl;
	return EXIT_SUCCESS;
	}
	while (CurretEl->Next != NULL && CurretEl->Next->power > po)
	{
		CurretEl = CurretEl->Next;
	}
		
	NewEl->Next = CurretEl->Next;
	CurretEl->Next = NewEl;
		
return EXIT_SUCCESS;
}

int Addition(Position Head1,Position Head2,Position HeadR)
{
	Position p1 = Head1->Next;
	Position p2 = Head2->Next;

	while (p1 != NULL && p2 != NULL)
	{
		if (p1->power > p2->power)
		{
			SortedInput(HeadR, p1->coefficient, p1->power);
			p1 = p1->Next;
		}
		else if (p2->power > p1->power) 
		{
			SortedInput(HeadR, p2->coefficient, p2->power);
			p2 = p2->Next;
		}
		else
		{
			int sum = p1->coefficient + p2->coefficient;
			if (sum != 0)
			{
				SortedInput(HeadR, sum, p1->power);
			}
			p1 = p1->Next;
			p2 = p2->Next;
		}
	}
	while (p1 != NULL)
	{
		SortedInput(HeadR, p1->coefficient, p1->power);
		p1 = p1->Next;
	}
	while (p2 != NULL)
	{
		SortedInput(HeadR, p2->coefficient, p2->power);
		p2 = p2->Next;
	}
	return EXIT_SUCCESS;
}

int Multiplication(Position HeadA, Position HeadB, Position HeadR)
{
	Position p1 = HeadA->Next;
	Position p2 = NULL;

	if (p1 == NULL || HeadB->Next == NULL)
		return EXIT_SUCCESS;

	while (p1 != NULL)
	{
		p2 = HeadB->Next;
		while (p2 != NULL)
		{
			int newCoeff = p1->coefficient * p2->coefficient;
			int newPower = p1->power + p2->power;

			SortedInput(HeadR, newCoeff, newPower);

			p2 = p2->Next;
		}
		p1 = p1->Next;
	}

	return EXIT_SUCCESS;
}

int PrintPoly(Position Head)
{
	Position p = Head->Next;
	if (p == NULL) 
	{ 
		printf("Error ");
		return EXIT_SUCCESS;
	}

	while (p != NULL) {
		printf("%dx^%d", p->coefficient, p->power);
		p = p->Next;
		if (p != NULL && p->coefficient >= 0) printf(" + ");
		else if (p != NULL) printf(" ");
	}
	return EXIT_SUCCESS;
}

void FreePoly(Position Head)
{
	Position temp;
	while (Head != NULL) {
		temp = Head;
		Head = Head->Next;
		free(temp);
	}
}