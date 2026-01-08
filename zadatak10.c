#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CityTree* CityTreePos;
typedef struct CityTree {
    char name[20];
    int residents;
    CityTreePos left;
    CityTreePos right;
} CityTree;

typedef struct CityList* CityListPos;
typedef struct CityList {
    char name[20];
    int residents;
    CityListPos next;
} CityList;

typedef struct CountryList* CountryListPos;
typedef struct CountryList {
    char name[20];
    CityTreePos cityTree;
    CountryListPos next;
} CountryList;

typedef struct CountryTree* CountryTreePos;
typedef struct CountryTree {
    char name[20];
    CityListPos cityList;
    CountryTreePos left;
    CountryTreePos right;
} CountryTree;

CityTreePos insertCityTree(CityTreePos root, char* name, int residents)
{
    if (!root)
    {
        root = malloc(sizeof(CityTree));
        strcpy(root->name, name);
        root->residents = residents;
        root->left = root->right = NULL;
        return root;
    }
    if (residents > root->residents)
        root->right = insertCityTree(root->right, name, residents);
    else if (residents < root->residents)
        root->left = insertCityTree(root->left, name, residents);
    else
        strcmp(name, root->name) > 0 ?
        (root->right = insertCityTree(root->right, name, residents)) :
        (root->left = insertCityTree(root->left, name, residents));
    return root;
}

CityListPos insertCityList(CityListPos head, char* name, int residents)
{
    if (!head || strcmp(name, head->name) < 0)
    {
        CityListPos new = malloc(sizeof(CityList));
        strcpy(new->name, name);
        new->residents = residents;
        new->next = head;
        return new;
    }
    head->next = insertCityList(head->next, name, residents);
    return head;
}

void loadCities(char* filename, CityTreePos* tree, CityListPos* list)
{
    FILE* f = fopen(filename, "r");
    char name[20];
    int residents;
    while (fscanf(f, "%s %d", name, &residents) == 2)
    {
        if (tree)
            *tree = insertCityTree(*tree, name, residents);
        if (list)
            *list = insertCityList(*list, name, residents);
    }
    fclose(f);
}

CountryListPos insertCountryList(CountryListPos head, char* name, char* cityFile)
{
    if (!head || strcmp(name, head->name) < 0)
    {
        CountryListPos new = malloc(sizeof(CountryList));
        strcpy(new->name, name);
        new->cityTree = NULL;
        loadCities(cityFile, &new->cityTree, NULL);
        new->next = head;
        return new;
    }
    head->next = insertCountryList(head->next, name, cityFile);
    return head;
}

CountryTreePos insertCountryTree(CountryTreePos root, char* name, char* cityFile)
{
    if (!root)
    {
        root = malloc(sizeof(CountryTree));
        strcpy(root->name, name);
        root->cityList = NULL;
        loadCities(cityFile, NULL, &root->cityList);
        root->left = root->right = NULL;
        return root;
    }
    if (strcmp(name, root->name) < 0)
        root->left = insertCountryTree(root->left, name, cityFile);
    else if (strcmp(name, root->name) > 0)
        root->right = insertCountryTree(root->right, name, cityFile);
    return root;
}

void printCityTree(CityTreePos root)
{
    if (!root) return;
    printCityTree(root->right);
    printf("\t%s %d\n", root->name, root->residents);
    printCityTree(root->left);
}

void printCityList(CityListPos head)
{
    while (head)
    {
        printf("\t%s %d\n", head->name, head->residents);
        head = head->next;
    }
}

void printCountryList(CountryListPos head)
{
    while (head)
    {
        printf("%s\n", head->name);
        printCityTree(head->cityTree);
        head = head->next;
    }
}

void printCountryTree(CountryTreePos root)
{
    if (!root) return;
    printCountryTree(root->left);
    printf("%s\n", root->name);
    printCityList(root->cityList);
    printCountryTree(root->right);
}

CountryListPos findCountryList(CountryListPos head, char* name)
{
    while (head)
    {
        if (strcmp(head->name, name) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

CountryTreePos findCountryTree(CountryTreePos root, char* name)
{
    if (!root) return NULL;
    if (strcmp(name, root->name) == 0) return root;
    if (strcmp(name, root->name) < 0) return findCountryTree(root->left, name);
    return findCountryTree(root->right, name);
}

void printCityTreeFiltered(CityTreePos root, int min)
{
    if (!root) return;
    printCityTreeFiltered(root->right, min);
    if (root->residents >= min)
        printf("\t%s %d\n", root->name, root->residents);
    printCityTreeFiltered(root->left, min);
}

void printCityListFiltered(CityListPos head, int min)
{
    while (head)
    {
        if (head->residents >= min)
            printf("\t%s %d\n", head->name, head->residents);
        head = head->next;
    }
}

int main(void)
{
    FILE* file = fopen("countries.txt", "r");
    char country[20], cityFile[20];
    char searchCountry[20];
    int minResidents;

    CountryList head = { "", NULL, NULL };
    CountryTreePos treeRoot = NULL;

    while (fscanf(file, "%s %s", country, cityFile) == 2)
    {
        head.next = insertCountryList(head.next, country, cityFile);
        treeRoot = insertCountryTree(treeRoot, country, cityFile);
    }
    fclose(file);

    printf("A)\n");
    printCountryList(head.next);

    printf("\nB)\n");
    printCountryTree(treeRoot);

    printf("\nEnter country name: ");
    scanf("%s", searchCountry);
    printf("Minimal number of residents: ");
    scanf("%d", &minResidents);

    printf("\nA)\n");
    CountryListPos c1 = findCountryList(head.next, searchCountry);
    if (c1)
        printCityTreeFiltered(c1->cityTree, minResidents);
    else
        printf("Country not found\n");

    printf("\nB)\n");
    CountryTreePos c2 = findCountryTree(treeRoot, searchCountry);
    if (c2)
        printCityListFiltered(c2->cityList, minResidents);
    else
        printf("Country not found\n");

    return 0;
}
