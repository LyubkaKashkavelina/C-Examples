#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 50

void writeBinary(char *fileName,char*s);
void writeBinaryArray(char *fileName,char s[][LEN],int size);

int main()
{
    char text[LEN];
    char text2[3][LEN];

    printf("Input text1:");
    gets(text);
    printf("Input text1:");
    gets(text2[0]);
    printf("Input text2:");
    gets(text2[1]);
    printf("Input text3:");
    gets(text2[2]);
//    puts(text);
    writeBinary("string.out",text);
    writeBinaryArray("stringArray.out",text2,3);
    printf("Hello world!\n");
    return 0;
}

void writeBinary(char *fileName,char*s)
{
    FILE *fout;

    if((fout=fopen(fileName,"wb"))==NULL)
    {
        printf("Error\n");
        return;
    }
    fwrite(s,strlen(s),sizeof(char),fout);
    fwrite(s,LEN,sizeof(char),fout);
    fclose(fout);
}

void writeBinaryArray(char *fileName,char s[][LEN],int size)
{
    FILE *fout;
    int i;
    int lText;

    if((fout=fopen(fileName,"wb"))==NULL)
    {
        printf("Error\n");
        return;
    }
    for(i=0;i<size;i++)
    {
        lText = strlen(s[i])+1;
        fwrite(&lText,1,sizeof(int),fout);
        fwrite(s[i],lText,sizeof(char),fout);
    }
    for(i=0;i<size;i++)
    {
        fwrite(s[i],LEN,sizeof(char),fout);
    }
    fclose(fout);
}
