#include <stdio.h>
#include <stdlib.h>

int main()
{
    //In this program, I am taking input one character at a time.
    //User has to press CTRL-Z to stop giving input
    char c;

    //file pointer
    FILE *fp;

    //open the file in which you want to store data
    fp = fopen("randomTxt1.txt", "w");

    if(fp == NULL)
        printf("\n Error in opening file.");

    else
    {
        while((c = getchar()) != EOF) //get characters from input
            fputc(c, fp);

        fclose(fp);
    }

    return 0;
}
