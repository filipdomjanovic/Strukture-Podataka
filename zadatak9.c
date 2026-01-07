#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _binTree* Position;
typedef struct _binTree
{
    int el;
    Position lt;
    Position rt;
} BinTree;


Position insert(int el, Position root);
int inorder(Position root);
int replace(Position root);
Position randomInsert(Position root);
int inorderINfile(Position root, FILE* fileP);
void freeTree(Position root);

int main()
{
    Position root = NULL;
    int el = 0, choice = 0;

    srand((unsigned)time(NULL));

    printf("Unesi prvi clan: ");
    scanf("%d", &el);
    root = insert(el, root);

    FILE* fileP = fopen("BinTree.txt", "w");
    if (fileP == NULL)
    {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    do
    {
        printf("\nMENU:\n");
        printf("1 - Unos novog elementa\n");
        printf("2 - Inorder ispis stabla\n");
        printf("3 - Replace (zamjena sa sumom djece)\n");
        printf("4 - Random unos elementa\n");
        printf("5 - Ispis u BinTree.txt\n");
        printf("6 - EXIT\n");
        printf("Odabir: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Novi element: ");
            scanf("%d", &el);
            root = insert(el, root);
            break;

        case 2:
            printf("Inorder ispis:\n");
            inorder(root);
            printf("\n");
            break;

        case 3:
            replace(root);
            printf("Replace izvrsen.\n");
            break;

        case 4:
            root = randomInsert(root);
            break;

        case 5:
            inorderINfile(root, fileP);
            printf("Ispisano u BinTree.txt\n");
            break;

        case 6:
            printf("Izlaz iz programa.\n");
            break;

        default:
            printf("Neispravan odabir!\n");
        }

    } while (choice != 6);

    freeTree(root);
    fclose(fileP);

    return 0;
}


Position insert(int el, Position root)
{
    if (root == NULL)
    {
        Position newEl = (Position)malloc(sizeof(BinTree));
        if (newEl == NULL)
        {
            printf("Greska pri alokaciji memorije!\n");
            return NULL;
        }

        newEl->el = el;
        newEl->lt = NULL;
        newEl->rt = NULL;
        return newEl;
    }

    if (el < root->el)
        root->lt = insert(el, root->lt);
    else if (el > root->el)
        root->rt = insert(el, root->rt);

    return root;
}

int inorder(Position root)
{
    if (root != NULL)
    {
        inorder(root->lt);
        printf("%d ", root->el);
        inorder(root->rt);
    }
    return 0;
}

int replace(Position root)
{
    if (root == NULL)
        return 0;

    int sumL = replace(root->lt);
    int sumR = replace(root->rt);

    int temp = root->el;
    root->el = sumL + sumR;

    return temp + root->el;
}

Position randomInsert(Position root)
{
    int r = rand() % 90 + 1;
    printf("Random element: %d\n", r);
    return insert(r, root);
}

int inorderINfile(Position root, FILE* fileP)
{
    if (root != NULL)
    {
        inorderINfile(root->lt, fileP);
        fprintf(fileP, "%d ", root->el);
        inorderINfile(root->rt, fileP);
    }
    return 0;
}

void freeTree(Position root)
{
    if (root != NULL)
    {
        freeTree(root->lt);
        freeTree(root->rt);
        free(root);
    }
}
