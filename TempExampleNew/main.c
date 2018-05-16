#include <stdio.h>
#include <stdlib.h>
#define SIZE 12

typedef struct {
    double temp;
    int mounth;
} TTemp;

void readTemp(TTemp *temp,char *fileName);
char* nameOfMonth(int id);
void printTemp(TTemp *temp);
void selectionSort(TTemp *temp);
void writeBinary(char *fileName, TTemp *temp);
void readBinary(char *fileName, TTemp *temp);
void writeText(char *fileName, TTemp *temp);

int compare(const void *a, const void *b)
{
    double *ta=(double *)a;
    double *tb=(double *)b;

    if (*ta<*tb)
        return -1;
    else if(*ta==*tb)
        return 0;
    else
        return 1;
}

int main()
{
//    TTemp temperature;
//    printf("Input temp: ");
//    scanf("%lf",&temperature.temp);
//    printf("Input mounth: ");
//    scanf("%d",&temperature.mounth);
//
//    printf("Temp:%g\tfor %d\n",temperature.temp,
//           temperature.mounth);
    TTemp temps[SIZE];
    TTemp temps2[SIZE];
    readTemp(temps,"C:\\Lectures\\PIK2\\Samples\\2017\\TemperatureExample\\temperatures.txt");
    printTemp(temps);
//    qsort(temps,SIZE,sizeof(TTemp),compare);
    selectionSort(temps);
    printTemp(temps);
    writeBinary("temperatures.out",temps);
    readBinary("temperatures.out",temps2);
    printTemp(temps2);
    writeText("temperatures.dat.txt",temps2);
    printf("Hello world!\n");
    return 0;
}

void readTemp(TTemp *temp,char *fileName)
{
    FILE *fin;
    int i=0;

    fin=fopen(fileName,"r");
    if (fin==NULL)
    {
        perror(NULL);
        exit(1);
    }
    while(!feof(fin))
    {
        fscanf(fin,"%lf",&temp[i].temp);
        temp[i].mounth=i;
        i++;
        if(i==SIZE)
            break;
    }
    fclose(fin);
}

char* nameOfMonth(int id)
{
    switch(id)
    {
        case 0: return "IAnuari";
        case 1: return "Fewruari";
        case 2: return "Mart";
        case 3: return "April";
        case 4: return "Maj";
        case 5: return "Juni";
        case 6: return "Juli";
        case 7: return "Awgust";
        case 8: return "Spetemwri";
        case 9: return "Oktomwri";
        case 10:return "Noemwri";
        case 11:return "Dekemwri";
    }
    return "";
}

void printTemp(TTemp *temp)
{
    int i;

    for(i=0;i<SIZE;i++)
    {
        printf("%s\t%g\n",nameOfMonth(temp[i].mounth),
               temp[i].temp);
    }
    printf("\n\n");
}

void selectionSort(TTemp *temp)
{
    TTemp tempValue;
    int minIndex;
    int i,j;

    for(i=0;i<SIZE-1;i++)
    {
        minIndex=i;
        for(j=i+1;j<SIZE;j++)
        {
            if(temp[minIndex].temp>temp[j].temp)
                minIndex=j;
        }
        tempValue=temp[i];
        temp[i]=temp[minIndex];
        temp[minIndex]=tempValue;
    }
}

void writeBinary(char *fileName, TTemp *temp)
{
    FILE *fout;

    if((fout=fopen(fileName,"wb"))==NULL)
    {
        printf("Error I/O\n");
        return;
    }
    fwrite(temp,SIZE,sizeof(TTemp),fout);
    fclose(fout);
}

void readBinary(char *fileName, TTemp *temp)
{
    FILE *fin;

    if((fin=fopen(fileName,"rb"))==NULL)
    {
        printf("I/O Error\n");
        return;
    }
    fread(temp,SIZE,sizeof(TTemp),fin);
    fclose(fin);
}

void writeText(char *fileName, TTemp *temp)
{
    FILE *fout;
    int i;

    if((fout=fopen(fileName,"w"))==NULL)
    {
        printf("I/O text error\n");
        return;
    }
    for(i=0;i<SIZE;i++)
    {
        fprintf(fout,"%s\t%g\n",
            nameOfMonth(temp[i].mounth),
            temp[i].temp);
    }
    fclose(fout);
}
