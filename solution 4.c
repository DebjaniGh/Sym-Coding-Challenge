//reads arbitrary data from standard input and writes it to a file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//this function returns the size of a file in bytes
unsigned long fileSize(char *filename)
{
    FILE *fp;
    unsigned long fileLength;

    fp = fopen(filename, "r");

    if(fp == NULL)
    {
        printf("\n Error - could not open file, so could not calculate size of file.");
        exit(1);
    }

    fseek(fp, 0L, SEEK_END);     //position the file pointer to the end of file position
    fileLength = ftell(fp);     //size of the file
    fseek(fp, 0L, SEEK_SET);     //position the file pointer to the beginning of the file

    fclose(fp);
    return fileLength;
}

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
    {
        printf("\n Error in opening file.");
        exit(1);
    }

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
    int ch;

    //open the input file from which you want to read
    fpi = fopen(inputFileName, "r");
    if(fpi == NULL)
    {
        printf("\n Error in opening input text file.");
        exit(1);
    }

    //open the file where you will store the data read from input File
    fpo = fopen("TxtOutputFile.txt","w");
    if(fpo == NULL)
    {
        printf("\n Error in opening output file for storing text.");
        exit(1);
    }

    //read from input file one character at a time and store it in another file
    while((ch = fgetc(fpi)) != EOF)
        fputc(ch, fpo);

    fclose(fpi);
    fclose(fpo);
}

//this function reads from a binary file and stores the output in another file
void readFromBinaryFile(char *inputFileName)
{
    //file pointer
    FILE *fpin, *fpo;
    unsigned long fileLength, temp;
    int ch;

    //open the binary file from which you want to read
    fpin = fopen(inputFileName, "rb");
    if(fpin == NULL)
        printf("\n Error in opening input file.");

    fpo = fopen("BinaryOutputFile.bin","wb");
    if(fpo == NULL)
        printf("\n Error in opening output file.");

    /*calculate size of input file */
    fileLength = fileSize(inputFileName);

    /*read from input file and write to the output file */
    temp = fileLength;
    while(temp--)
    {
        ch = fgetc(fpin);
        if(ch == EOF)   break;
        fputc(ch, fpo);
    }

    fclose(fpin);
    fclose(fpo);
}

/* Test */

// To simulate input from keyboard, I am storing the input in
//"inFileNoData.txt" and "inFileWithData.txt" and associating the standard input "stdin" to these files

void Test_readFromKeyboard(char *InputFilename, char *OutputFilename)
{
    /* this function will test what happens when user gives data via keyboard and writes it to a file
        There are 2 cases: a) user gives no data
                           b) user gives some arbitrary data
        In both the cases, input data is being stored in a file.
        So, size of input file should be equal to the size of the file in which we are writing the data */

    unsigned long inFileLength, outFileLength, temp;
    FILE *fpi, *fpo;
    int ch;

    //simulate input from keyboard
    fpi = freopen(InputFilename, "r", stdin);

    if(fpi == NULL)
    {
        printf("\nError in reading data.");
        exit(1);
    }

    //write to a file
    fpo = fopen(OutputFilename, "w");
    if(fpo == NULL)
    {
        printf("\nError - could not open file for writing.");
        exit(1);
    }

    inFileLength = fileSize(InputFilename);
   // printf("\n Input file length: %lu", inFileLength);

    /*read from input file and write to the output file */
    temp = inFileLength;
    while(temp--)
    {
        ch = fgetc(fpi);
        if(ch == EOF)   break;
        fputc(ch, fpo);
    }

    fclose(fpi);
    fclose(fpo);

    outFileLength = fileSize(OutputFilename);
    //printf("\n Output file length: %lu", outFileLength);

    if(inFileLength == outFileLength)
        printf("\ntest case - read from standard input - passed.");
    else    printf("\ntest case - read from standard input - failed.");
}

int main()
{

    char *inputFile, *outputFile;

    //test when user gives no input from keyboard
    inputFile = "inFileNoData.txt";
    outputFile = "TestOutFileNoData.txt";
    Test_readFromKeyboard(inputFile, outputFile);

    printf("\n");

    //test when user gives some arbitrary data from keyboard
    inputFile = "inFileWithData.txt";
    outputFile = "TestOutFileWithData.txt";
    Test_readFromKeyboard(inputFile, outputFile);

 /*   int choice;

    char *ptr;
    int ch = '.';


    //ask user how he wants to enter data
    printf("\nEnter 0 if you want to enter data through keyboard\n ");
    printf("\nEnter 1 if you want to enter a file: ");
    scanf("%d\n",&choice);

    //if data entered from keyboard
    if(choice == 0)
        readFromKeyboard();

    else
    {
        printf("\nEnter file name (with extension): ");
        scanf("%s",inputFile);

        //prompt user for input
        while(strcmp(inputFile,"") == 0)
        {
            printf("\nEnter file name (with extension): ");
            scanf("%s",inputFile);
        }

        //find the first occurrence of '.'
        ptr = strchr(inputFile, ch);

        //binary files - images, videos, audio, executable etc.
        if((strcmp(ptr,".bin")) == 0)
            readFromBinaryFile(inputFile);

        //text files
        if((strcmp(ptr,".txt")) == 0)
            readFromTextFile(inputFile);
    } */

    return 0;
}
