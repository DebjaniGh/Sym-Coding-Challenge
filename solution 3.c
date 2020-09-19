//reads arbitrary data from standard input and writes it to a file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function to take arbitrary data from keyboard
void readFromKeyboard()
{
    //In this function, I am taking input one character at a time.
    //User has to press CTRL-Z to stop giving input.
    char c;

    //file pointer
    FILE *fp;

    //open the file in which you want to store data
    fp = fopen("randomTxt.txt", "w");

    if(fp == NULL)
        printf("\n Error in opening file.");

    else
    {
        while((c = getchar()) != EOF) //get characters from keyboard
            fputc(c, fp);

        fclose(fp);
    }
}

//this function reads from a text file and stores the data into another file
void readFromTextFile(char *inputFileName)
{
    FILE *fpi, *fpo;
    char ch;

    //open the input file from which you want to read
    fpi = fopen(inputFileName, "r");
    if(fpi == NULL)
        printf("\n Error in opening input text file.");

    fpo = fopen("TxtOutputFile.txt","w");
    if(fpo == NULL)
        printf("\n Error in opening output file for storing text.");

    //read from input file one character at a time and store it in another file
    while(!feof(fpi))
    {
        ch = fgetc(fpi);

        if(ch == '\n')  continue;   //ignore the first newline character

        fputc(ch, fpo);
    }

    fclose(fpi);
    fclose(fpo);
}

//this function reads from a binary file and stores the output in another file
void readFromBinaryFile(char *inputFileName)
{
    //file pointer
    FILE *fpin, *fpo;
    unsigned long fileLength, i;

    //open the binary file from which you want to read
    fpin = fopen(inputFileName, "rb");
    if(fpin == NULL)
        printf("\n Error in opening input file.");

    fpo = fopen("outputFile.bin","wb");
    if(fpo == NULL)
        printf("\n Error in opening output file.");

    /*read from the input file */

    fseek(fpin, 0, SEEK_END);   //position the file pointer to the end of file position
    fileLength = ftell(fpin);   //size of the file
    fseek(fpin, 0, SEEK_SET);   //position the file pointer to the beginning of the file

    /*write to the output file */
    for(i = 0; i < fileLength; i++)
        fputc(fgetc(fpin), fpo);    //read from input file and store into outputFile.bin

    fclose(fpin);
    fclose(fpo);
}

int main()
{
    //ask user how he wants to enter data
    int choice;
    char inputFile[100];
    char *ptr;
    int ch = '.';

    printf("\nEnter 0 if you want to enter data through keyboard\n ");
    printf("\nEnter 1 if you want to enter a file: ");
    scanf("%d",&choice);

    //if data entered from keyboard
    if(choice == 0)
        readFromKeyboard();

    else
    {
        printf("\nEnter file name: ");
        scanf("%s",inputFile);

        //find the first occurrence of '.'
        ptr = strchr(inputFile, ch);

        //binary files - images, videos, audio, executable etc.
        if((strcmp(ptr,".bin")) == 0)
            readFromBinaryFile(inputFile);

        //text files
        if((strcmp(ptr,".txt")) == 0)
            readFromTextFile(inputFile);
    }

    return 0;
}
