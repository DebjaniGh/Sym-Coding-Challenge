//reads arbitrary data from standard input and writes it to a file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100000
int main()
{
    //in this program, I assume that the user stops giving input by pressing ';'
    //I am storing the input in a character array
    char inputString[MAX];

    //file pointer
    FILE *fp;

    //enter data
    printf("Enter input (press ';' to stop): ");
    scanf("%[^;]s", inputString);

    //open the file where you want to store the input
    fp = fopen("randomTxt.txt","w");

    if(fp == NULL)
        printf("\nError in opening file");

    else
    {
        if(strlen(inputString) > 0)
        {
            fputs(inputString, fp);
        }

        fclose(fp);
    }

    return 0;
}
