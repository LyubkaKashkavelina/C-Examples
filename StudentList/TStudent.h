#ifndef TSTUDENT_H_INCLUDED
#define TSTUDENT_H_INCLUDED

typedef struct TTStudent{
    int fNom;
    char name[30];
    float mark;
    struct TTStudent *next;
} TStudent;

TStudent* readStudents();
TStudent* deleteList(TStudent *list);
void printList(TStudent *list);
TStudent* readStudentsFromFile(char *fName);
TStudent *atEnd(TStudent *list);
void printListInFile(char *fName,TStudent *list);
TStudent* deleteElement(TStudent *list);
void printListInBinFile(char *fName,TStudent *list);
TStudent* readStudentsFromBinFile(char *fName);


#endif // TSTUDENT_H_INCLUDED
