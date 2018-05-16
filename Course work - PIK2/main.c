#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


typedef struct _painting_ {
    char uniqueCode[50];
    char nameOfPainting[50];
    char author[50];
    double price;
    int yearOfCreation;
} Painting;

typedef struct _author_ {
    char author[50];
} author;

typedef struct _node_{
    Painting* painting;
    struct _node_* next;
} Node;

typedef struct _authorNode_{
    author* author;
    struct _authorNode_* next;
} authorNode;


void printAll(Node*);
void add(Painting*, Node*);
void clearList(Node*);
void deleteFromList(char*, Node*);
void printPainting(Painting* painting);
void clearListWithoutPaintings(Node*);
void bubbleSort(Node*);
void swap(Node*, Node*);
void addToList(authorNode*, char*);
int alreadyInList(authorNode*, char*);
int getNumberOfElementsInList(Node*);

Painting* readFromTerminal();
Painting* readFromFile(char*);
Painting* getPaintingByCode(Node*, char*);
void createFile(Painting);
Node* getPaintingsByAuthorSorted(Node* head, char* authorName);
void specialPrint(Node* head);

int main() {
    int n;
    Node* root = malloc(sizeof(Node)*1);
    root->next = NULL;
    while(1){
        printf("%s%s%s%s%s666. To exit\n",
               "1. To add\n", "2. To delete\n", "3. To print sorted\n",
               "4. Print all the data in the painting list\n", "5. Edit painting\n");
        scanf("%d",&n);
        fflush(stdin);
        switch(n){
            case 1: {
                Painting* painting;
                char fileName[50];
                printf("1 terminal\n2 file.\n");
                scanf("%d",&n);
                fflush(stdin);
                if(n==1){
                    painting = readFromTerminal();
                    add(painting, root);
                }else if(n==2){
                    printf("Name of file: ");
                    gets(fileName);
                    fileName[strlen(fileName)]='\0';
                    painting = readFromFile(fileName);
                    if(painting) {
                        add(painting,root);
                    } else {
                        printf("File wasnt opened...\n");
                    }
                }
                break;
            }
            case 2: {
                char uniqueCode[50];
                printf("Unique code: ");
                gets(uniqueCode);
                uniqueCode[strlen(uniqueCode)] = '\0';
                printf("%s\n", uniqueCode);
                deleteFromList(uniqueCode,root);
                break;
            }
            case 3: {
                specialPrint(root);
                break;
            }

            case 4: {
                printAll(root);
                break;
            }

            case 5: {
                char uniqueCode[50];
                printf("Enter unique code to actualize: ");
                fflush(stdin);
                gets(uniqueCode);
                uniqueCode[strlen(uniqueCode)] = '\0';
                Painting* painting = getPaintingByCode(root, uniqueCode);
                if(!painting) {
                    printf("No such painting found!\n");
                    break;
                }

                while(1){
                    printf("Which do you want to edit?\n/1: Name, 2: ID, 3: author, 4: price, 5: yearOfCreation, 666. To exit/\n");
                    fflush(stdin);
                    scanf("%d", &n);
                    fflush(stdin);
                    remove(painting->nameOfPainting);
                    switch(n) {
                        case 1: {
                            char newName[50];
                            fflush(stdin);
                            printf("Enter new name of painting: ");
                            gets(newName);
                            newName[strlen(newName)] = '\0';
                            fflush(stdin);

                            strcpy(painting->nameOfPainting, newName);
                            break;
                        }

                        case 2: {
                            char newUnique[50];
                            fflush(stdin);
                            printf("Enter new unique identifier of painting: ");
                            gets(newUnique);
                            newUnique[strlen(newUnique)] = '\0';
                            fflush(stdin);

                            strcpy(painting->uniqueCode, newUnique);
                            break;
                        }

                        case 3: {
                            char newAuthor[50];
                            fflush(stdin);
                            printf("Enter new author of painting: ");
                            gets(newAuthor);
                            newAuthor[strlen(newAuthor)] = '\0';
                            fflush(stdin);

                            strcpy(painting->author, newAuthor);
                            break;
                        }

                        case 4: {
                            double newPrice;
                            fflush(stdin);
                            printf("Enter new price of painting: ");
                            scanf("%lf", &newPrice);
                            painting->price = newPrice;
                            break;
                        }

                        case 5: {
                            int newYearOfCreation;
                            fflush(stdin);
                            printf("Enter new year of creation of painting: ");
                            scanf("%d", &newYearOfCreation);
                            painting->yearOfCreation= newYearOfCreation;
                            break;
                        }

                        case 666: {
                            break;
                        }
                    }

                    if(n == 666) {
                        n = 667;
                        break;
                    }
                }



                createFile(*painting);
                break;
            }
        }

        if(n == 666){
            clearList(root);
            break;
        }

    }
    free(root);
    return 0;
}

void printPainting(Painting* painting){
    printf("\tUnique code: %s\n",painting->uniqueCode);
    printf("\tName of painting: %s\n",painting->nameOfPainting);
    printf("\tAuthor: %s\n",painting->author);
    printf("\tYear of creation: %d\n",painting->yearOfCreation);
    printf("\tPrice: %lf\n",painting->price);
}

int getNumberOfElementsInList(Node* head) {
    int length = 0;
    Node* currentNode = head->next;
    while(currentNode->next != NULL) {
        length++;
        currentNode = currentNode -> next;
    }

    length++;
    return length;
}

void bubbleSort(Node *head) {
    if(head == NULL || head->next == NULL) {
        return;
    }
    int i;
    int sizeOfList = getNumberOfElementsInList(head);
    for(i = 0; i < sizeOfList; i++) {
        Node* current = head->next;
        Node* next = head->next->next;

        while(next != NULL) {
            int compare = current->painting->price < next->painting->price;
            if(compare) {
                swap(current, next);
            }

            current = next;
            next = next->next;
        }
    }
}

void swap(Node* cur, Node* next) {
    Painting* tmp = cur->painting;
    cur->painting = next->painting;
    next->painting = tmp;
}

void deleteFromList(char* name, Node* head) {
    Node* currentNode = head;
    Node* currentNodeBefore = head;
    if(!currentNode->next) {
        return;
    }
    currentNode = currentNode -> next;

    while(1) {
        if(!strcmp(currentNode->painting->uniqueCode, name)) {
            break;
        }

        currentNodeBefore = currentNodeBefore->next;
        currentNode = currentNode->next;

        if(!(currentNode)) {
            printf("Name not found\n");
            return;
        }
    }

    currentNodeBefore->next = currentNode->next;
    remove(currentNode->painting->nameOfPainting);
    free(currentNode->painting);
    free(currentNode);

}

void printAll(Node* head) {
    if(head->next == NULL) {
        printf("List is empty, please add paintings...\n");
        return;
    }

    Node* currentNode = head->next;
    while(currentNode->next != NULL) {
        printPainting(currentNode->painting);
        currentNode = currentNode -> next;
    }

    printPainting(currentNode->painting);
}

Painting* readFromTerminal() {
    char currentUnique[50];
    char currentName[50];
    char currentauthor[50];
    double currentPrice;
    int currentYear;

    printf("Unique code: ");
    fflush(NULL);
    gets(currentUnique);
    currentUnique[strlen(currentUnique)] = '\0';

    printf("Name of painting: ");
    fflush(NULL);
    gets(currentName);
    currentName[strlen(currentName)] = '\0';

    printf("Painter: ");
    gets(currentauthor);
    currentauthor[strlen(currentauthor)] = '\0';

    printf("Price: ");
    fscanf(stdin,"%lf",&currentPrice);

    printf("Year of painting: ");
    fscanf(stdin,"%d",&currentYear);

    Painting *painting = malloc(sizeof(Painting) * 1);

    strcpy(painting->uniqueCode, currentUnique);
    strcpy(painting->nameOfPainting, currentName);
    strcpy(painting->author , currentauthor);
    painting->price = currentPrice;
    painting ->yearOfCreation = currentYear;

    return painting;
}

Painting* readFromFile(char* fileName) {
    FILE *f = fopen(fileName, "rb");

    if(!f) {
        return NULL;
    }

    char currentUnique[50];
    char currentName[50];
    char currentauthor[50];
    double currentPrice;
    int currentYear;

    fread(currentUnique, sizeof(char), 50, f);
    fread(currentName, sizeof(char), 50, f);
    fread(currentauthor, sizeof(char), 50, f);
    fread(&currentPrice, sizeof(double), 1, f);
    fread(&currentYear, sizeof(int), 1, f);

    Painting *painting = malloc(sizeof(Painting) * 1);

    strncpy(painting->uniqueCode, currentUnique, 50);
    strncpy(painting->nameOfPainting, currentName, 50);
    strncpy(painting->author , currentauthor, 50);

    painting->price = currentPrice;
    painting->yearOfCreation = currentYear;

    fclose(f);
    printPainting(painting);
    return painting;
}

void createFile(Painting painting) {
    FILE* f = fopen(painting.nameOfPainting, "wb");

    if(!f) {
        printf("Unable to open %s with size %d: %ld\n", painting.nameOfPainting, strlen(painting.nameOfPainting));
    }

    fwrite(painting.uniqueCode,sizeof(char),50,f);
    fwrite(painting.nameOfPainting,sizeof(char),50,f);
    fwrite(painting.author,sizeof(char),50,f);
    fwrite(&painting.price,sizeof(double),1,f);
    fwrite(&painting.yearOfCreation,sizeof(int),1,f);

    fclose(f);
}

void add(Painting* currentPainting, Node* head) {

    Node* nodeToBeAdded = malloc(sizeof(Node) * 1);
    nodeToBeAdded->painting = currentPainting;
    nodeToBeAdded->next = NULL;

    Node* currentNode = head;
    while(currentNode->next != NULL) {
        currentNode = currentNode -> next;
    }

    currentNode->next = nodeToBeAdded;
    createFile(*currentPainting);
}

void clearList(Node* root) {
    Node* currentNode = root->next;
    Node* prevNode = root;
    if(!currentNode) {
        return;
    }
    while(1) {
        if(currentNode->next == NULL) {
            free(currentNode->painting);
            free(currentNode);
            break;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;

        free(prevNode->painting);
        free(prevNode);
    }

    free(root);
}

void clearListWithoutPaintings(Node* root) {
    Node* currentNode = root->next;
    Node* prevNode = root;
    while(1) {
        if(currentNode->next == NULL) {
           free(currentNode);
            break;
        }

        prevNode = currentNode;
        currentNode = currentNode->next;

        free(prevNode);
    }

    free(root);
}


Painting* getPaintingByCode(Node* head, char* uniquecode) {
    Node* currentNode = head->next;
    while(1) {
        if(!currentNode) {
            return NULL;
        }

        if(!strcmp(currentNode->painting->uniqueCode, uniquecode)) {
            return currentNode->painting;
        }

        currentNode = currentNode->next;
    }
}

Node* getPaintingsByAuthorSorted(Node* head, char* authorName) {
    Node* currentNode = head->next;
    Node* currentHead = malloc(sizeof(Node) * 1);
    currentHead->next = NULL;
    if(!head || !head->next) {
        return NULL;
    }

    while(1) {
        if(!strcmp(currentNode->painting->author, authorName)) {
            add(currentNode->painting, currentHead);
        }

        if(currentNode->next == NULL) {
            break;
        }

        currentNode = currentNode->next;
    }

    bubbleSort(currentHead);
    return currentHead;
}

void specialPrint(Node* head) {
    system("cls");

    if(head == NULL || head->next == NULL) {
        printf("Head is empty\n");
        return;
    }

    authorNode* authorHead = malloc(sizeof(authorNode) * 1);
    authorHead->next = NULL;

    if(head->next == NULL) {
        return;
    }

    Node* currNode = head->next;
    while(1) {

        if(currNode == NULL) {
            break;
        }

        if(!alreadyInList(authorHead, currNode->painting->author)) {
            addToList(authorHead, currNode->painting->author);

            Node* currentListWithImagesFromAuthor = getPaintingsByAuthorSorted(head, currNode->painting->author);

            if(!currentListWithImagesFromAuthor) {
                return;
            }

            printAll(currentListWithImagesFromAuthor);
            clearListWithoutPaintings(currentListWithImagesFromAuthor);
        }

        currNode = currNode->next;
    }
}

void addToList(authorNode* head, char name[50]) {
    author* dir = malloc(sizeof(author) * 1);
    strcpy(dir->author, name);

    authorNode* nodeToBeAdded = malloc(sizeof(authorNode) * 1);
    nodeToBeAdded->author = dir;
    nodeToBeAdded->next = NULL;

    authorNode* currentNode = head->next;
    if (currentNode == NULL) {
        currentNode = nodeToBeAdded;
        head->next = currentNode;
    } else {
        while(1) {

            if(currentNode == NULL || currentNode->next == NULL) {
                break;
            }

            currentNode = currentNode->next;
        }
        currentNode->next = nodeToBeAdded;
    }

}

int alreadyInList(authorNode* head, char name[50]) {
    authorNode* currentNode = head->next;
    if(currentNode == NULL) {
        return 0;
    }

    if(!strcmp(currentNode->author->author, name)) {
        return 1;
    }

    while(currentNode->next != NULL) {
        currentNode = currentNode -> next;
        if(!strcmp(currentNode->author->author, name)) {
            return 1;
        }
    }

    return 0;

}
