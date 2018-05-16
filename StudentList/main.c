#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TStudent.h"

int main()
{
    TStudent *head;

//    head = readStudents();
    head = readStudentsFromFile("students.txt");
    if (head!=NULL)
    {
        printList(head);
        printListInFile("students.out.txt",head);
        head = deleteElement(head);
        printList(head);
        printListInBinFile("students.bin",head);
        head = deleteList(head);
        head = readStudentsFromBinFile("students.bin");
        if (head!=NULL)
        {
            printList(head);
            head = deleteList(head);
        }
   }
    printf("Hello world!\n");
    return 0;
}

TStudent* readStudents()
{
    TStudent *begin=NULL;
    TStudent *temp;
    int fNom;
    char name[30];
    float mark;

    do {
        printf("Input number: ");
        scanf("%d",&fNom);
        if (fNom==0)
        {
            break;
        }
        printf("Input name: ");
        scanf("%s",name);
        printf("Input mark: ");
        scanf("%f",&mark);

        temp = (TStudent*)malloc(sizeof(TStudent));
        if (temp==NULL)
        {
            if (begin!=NULL)
                begin = deleteList(begin);
            printf("Memory error\n");
            exit (-1);
        }
        temp->fNom = fNom;
        strcpy(temp->name,name);
        temp->mark = mark;
        temp->next = begin;
        begin = temp;
    } while (1);
    return begin;
}

TStudent* deleteList(TStudent *list)
{
    TStudent *temp;

    for(temp=list;temp!=NULL;)
    {
        list = temp;
        temp = temp->next;
        free(list);
    }
    return NULL;
}

void printList(TStudent *list)
{
    TStudent *p;

    printf("\n\n");
    for (p=list;p!=NULL;p=p->next)
    {
        printf("%d\t%s\t%g\n",p->fNom,p->name,
               p->mark);
    }
}

TStudent* readStudentsFromFile(char *fName)
{
    TStudent *begin=NULL;
    TStudent *temp;
    FILE *f;

    if ((f=fopen(fName,"r"))==NULL)
    {
        printf("I/O error\n");
        exit(-2);
    }

    while(!feof(f))
    {
        temp = (TStudent*)malloc(sizeof(TStudent));
        if (temp==NULL)
        {
            if (begin!=NULL)
                begin = deleteList(begin);
            printf("Memory error\n");
            fclose(f);
            exit (-1);
        }
        fscanf(f,"%d%s%f",&(temp->fNom),temp->name,
               &(temp->mark));
//        temp->next = begin;
//        begin = temp;
        if (begin==NULL)
        {
            begin = temp;
        }else{
            TStudent *end = atEnd(begin);
            end->next = temp;
        }
        temp->next = NULL;
    }
    fclose(f);
    return begin;
}

TStudent *atEnd(TStudent *list)
{
    TStudent *q;

    for(q=list;q->next!=NULL;q=q->next) ;

    return q;
}

void printListInFile(char *fName,TStudent *list)
{
    TStudent *p;
    FILE *f;

    if ((f=fopen(fName,"w"))==NULL)
    {
        printf("Writing error\n");
        return;
    }

    for (p=list;p!=NULL;p=p->next)
    {
        fprintf(f,"%d\t%s\t%g\n",p->fNom,p->name,
               p->mark);
    }
    fclose(f);
}

TStudent* deleteElement(TStudent *list)
{
    TStudent *q,*prev;

    for(prev=q=list;q!=NULL;)
    {
        if (q->mark>=5)
        {
            if(list==q)
                list=q->next;
            prev->next = q->next;
            free(q);
            q = prev;
        }else
            prev = q;
            q = q->next;
    }
    return list;
}

void printListInBinFile(char *fName,TStudent *list)
{
    TStudent *p;
    FILE *f;

    if ((f=fopen(fName,"wb"))==NULL)
    {
        printf("Writing error\n");
        return;
    }

    for (p=list;p!=NULL;p=p->next)
    {
        fwrite(&(p->fNom),sizeof(int),1,f);
        fwrite(p->name,30,1,f);
        fwrite(&(p->mark),sizeof(float),1,f);
    }
    fclose(f);
}

TStudent* readStudentsFromBinFile(char *fName)
{
    TStudent *begin=NULL;
    TStudent *temp;
    FILE *f;

    if ((f=fopen(fName,"rb"))==NULL)
    {
        printf("I/O error\n");
        exit(-2);
    }

    while(!feof(f))
    {
        temp = (TStudent*)malloc(sizeof(TStudent));
        if (temp==NULL)
        {
            if (begin!=NULL)
                begin = deleteList(begin);
            printf("Memory error\n");
            fclose(f);
            exit (-1);
        }
        if (fread(&(temp->fNom),sizeof(int),1,f)!=1)
        {
            free(temp);
            temp=NULL;
            break;
        }
        fread(temp->name,30,1,f);
        fread(&(temp->mark),sizeof(float),1,f);
        temp->next = begin;
        begin = temp;
    }
    fclose(f);
    return begin;
}
