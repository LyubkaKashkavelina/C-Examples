#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _LIST_
{
    char name_of_product[20];
    double weight;
    char type_of_icecream[20];
    double price;
    struct _LIST_*next;
}LIST;

LIST * root;


void add()
{
    LIST * node;
    FILE * fp;
    fp=fopen("sladoled.txt","a+");
    if(fp==NULL)
    {
        printf("Error!");
        exit (1);
    }

    if (root == NULL)
        {
        root = (LIST*)calloc(1,sizeof(LIST));
        root->next=NULL;
        node = root;
        }
    else
        {
            node->next=(LIST*)calloc(1,sizeof(LIST));
            node=node->next;
            node->next=NULL;
        }

printf("Enter name of product:");
scanf("%s",node->name_of_product);
fprintf(fp,"%s",node->name_of_product);
printf("Enter weight of product:");
scanf("%lf",&node->weight);
fprintf(fp,"%lf",node->weight);
printf("Enter type of ice cream:");
scanf("%s",node->type_of_icecream);
fprintf(fp,"%s",node->type_of_icecream);
printf("Enter price of product:");
scanf("%lf",&node->price);
fprintf(fp,"%lf",node->price);

fclose(fp);
}

void printList(){
LIST * temp;
for(temp=root;temp!=NULL;temp=temp->next)
{
    printf("%s %lf %s %lf",temp->name_of_product, temp->weight, temp->type_of_icecream,temp->price);
}
}
 double totalCost(LIST*head,char ch[])
 {
     LIST * temp;
     double result=0;
     for(temp=head;temp!=NULL;temp=temp->next)
     {
         if(strcmp(temp->type_of_icecream,ch)==0)
           {
               result += temp->weight * temp->price;
           }
     }

  return result;
 }

LIST * createStackList(LIST* head,FILE*fp)
{
head = NULL;
LIST * temp;
LIST * node;

fp=fopen("sladoled.txt","r");
if(fp==NULL)
{
    printf("Error2!");
    exit (2);
}
while(!feof(fp)){
temp = (LIST*)calloc(1,sizeof(LIST));
node = (LIST*)calloc(1,sizeof(LIST));
fscanf(fp,"%s",node->name_of_product);
fscanf(fp,"%lf",&node->weight);
fscanf(fp,"%s",node->type_of_icecream);
fscanf(fp,"%lf",&node->price);

strcpy (temp->name_of_product,node->name_of_product);
temp->weight=node->weight;
strcpy (temp->type_of_icecream, node->name_of_product);
temp->price=node->price;

temp->next=head;
head = temp;
}
fclose(fp);
return head;
}

//void addStackList()
//{
   // LIST * node;
    //node = (LIST*)calloc(1,sizeof(LIST));

//printf("Enter name of product:");
//scanf("%s",node->name_of_product);
//printf("Enter weight of product:");
//scanf("%lf",&node->weight);

//node->next=root;
//root = node;


//}

void writeningInFile(FILE*fout,LIST*head,int numbs [])
{
    LIST * temp;
    int i;
    int count = 0;
    int len;
    len = sizeof(numbs)/sizeof(int);
    fout=fopen("result","w");
    if(fout==NULL)
    {
        printf("Error3!");
        exit (5);
    }

    for(temp=head;temp!=NULL;temp=temp->next){
             count++;
        for(i=0;i<len;i++)
        {
            if(numbs[i]==count)
            {
         fprintf(fout,"%s",temp->name_of_product);
         fprintf(fout,"%lf",temp->weight);
         fprintf(fout,"%s",temp->type_of_icecream);
         fprintf(fout,"%lf",temp->price);
            }

        }
    }



}

int main()
{
    FILE * fp;
    fp=fopen("sladoled.txt","r");
    if(fp==NULL)
    {
        printf("Error2!");
        exit (5);
    }
    LIST * begin;
    double sth;
    int arr[3]={1,2,3};

    add();
    add();
    //addStackList();
    printList(root);
    printf("Total is price is %lf",sth=totalCost(root,"levo"));
    begin = createStackList(root,fp);
    if(begin!=NULL){
        printList(begin);
    }
    fclose(fp);
    FILE * fout;
    fout=fopen("result","w");
    if(fout==NULL)
    {
        printf("Error3!");
        exit (5);
    }
    writeningInFile(fout,root,arr);
    fclose(fout);
    return 0;
}
