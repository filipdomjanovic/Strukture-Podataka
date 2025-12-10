#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*Napisati program koji pomoæu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguæiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Toènije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

typedef struct directory* PositionDirectory;
typedef struct directory
{
	char name[50];
	PositionDirectory subDirect;
	PositionDirectory Next;
	PositionDirectory ParentD;
}Directory;

PositionDirectory createDirectory(char* name);
int createSubdirectory(char* name, PositionDirectory currentDirectory);
PositionDirectory changeDirectory(char* name, PositionDirectory currentDirectory);
PositionDirectory exitDirectory(PositionDirectory currentDirectory);
int listDirectories(PositionDirectory currentDirectory);

int main()
{
	Directory HeadDirectory = { .name = {0} , .subDirect = NULL, .Next = NULL };

	PositionDirectory RootDirectory = createDirectory("C:");
	HeadDirectory.Next = RootDirectory;
	PositionDirectory CurrentDirectory = RootDirectory;

	int choice = 0;

	while (1) {
		printf("\nOdaberite opciju: \n");
		printf("1 - make directory\n");
		printf("2 - change directory\n");
		printf("3 - exit directory\n");
		printf("4 - list directories\n");
		printf("5 - exit\n");
		scanf("%d", &choice);
		

		char DirectoryName[50] = { 0 };

		switch (choice) {
		case 1:
			printf("Enter directory name: ");
			scanf(" %s", DirectoryName);
			createSubdirectory(DirectoryName, CurrentDirectory);
			break;
		case 2:
			printf("Enter directory name: ");
			scanf(" %s", DirectoryName);
			CurrentDirectory = changeDirectory(DirectoryName, CurrentDirectory);
			break;
		case 3:
			CurrentDirectory = exitDirectory(CurrentDirectory);
			break;
		case 4:
			listDirectories(CurrentDirectory);
			break;
		case 5:
			break;
		default:
			printf("Undefined charachter.\n");
			break;
		}
		if (choice == 5)
			break;
	}
	free(RootDirectory);

	return 0;
}

PositionDirectory createDirectory(char* name)
{
	PositionDirectory NewDir = (PositionDirectory)malloc(sizeof(Directory));

	if (!NewDir) {
		printf("Error in memory allocation\n");
		return NULL;
	}

	strcpy(NewDir->name, name);
	NewDir->Next = NULL;
	NewDir->subDirect = NULL;
	NewDir->ParentD = NULL;
	return NewDir;
}


int createSubdirectory(char* name, PositionDirectory currentDirectory) {
	PositionDirectory NewDir = createDirectory(name);

	if (!NewDir) {
		printf("Error in memory allocation\n");
		return 1;
	}

	NewDir->Next = currentDirectory->subDirect;
	NewDir->ParentD = currentDirectory;
	currentDirectory->subDirect = NewDir;
	return 0;
}

PositionDirectory changeDirectory(char* name, PositionDirectory currentDirectory) {
	PositionDirectory current = currentDirectory->subDirect;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0) {
			return current;
		}
		current = current->Next;
	}

	printf("Nepostoji takav directory.\n");
	return currentDirectory;
}
PositionDirectory exitDirectory(PositionDirectory currentDirectory) {
	if (currentDirectory->ParentD != NULL)
		currentDirectory = currentDirectory->ParentD;
	else
		printf("Error in directory construction.\n");

	return currentDirectory;
}
int listDirectories(PositionDirectory currentDirectory) {
	PositionDirectory current = currentDirectory->subDirect;

	if (current == NULL) {
		printf("Directory has no subdirectories.\n");
		return 0;
	}
	while (current != NULL) {
		printf("%s ", current->name);
		current = current->Next;
	}
	return 0;
}
