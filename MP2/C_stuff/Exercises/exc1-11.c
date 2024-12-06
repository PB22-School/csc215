#include <stdio.h>

#define TRUE 1
#define FALSE 0

int isSeperator(chr) 
int chr;
{
    if (chr == ' ' || chr == '\t' || chr == '\n') {
        return TRUE;
    }
    
    return FALSE;
}

int isValidWordCharacter(chr)
int chr;
{
    if ((chr >= '0' && chr <= '9') || (chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z')) {
        return TRUE;
    }

    return FALSE;
}

void main(argc, argv)
int argc;
char* argv[];
{
    FILE *infile;
    int chr;
    int wordCount;
    int lineCount;
    int inWord;

    if (argc != 2) {
        printf("Usage: exc1-11 {infile}\n");
        return;
    }

    infile = fopen(argv[1], "r");
    wordCount = lineCount = inWord = 0;

    while ((chr = fgetc(infile)) != EOF) {
        if (isSeperator(chr)) {
            if (inWord) {
                wordCount++;
                inWord = FALSE;
            }

            if (chr == '\n') {
                printf("Line %d had %d words.\n", lineCount, wordCount);
                wordCount = 0;
                lineCount++;
            }
        }
        else if (!inWord && isValidWordCharacter(chr)) {
            inWord = TRUE;
        }
    }

    if (inWord) {
        wordCount++;
    }

    printf("Line %d had %d words.\n", lineCount, wordCount);
    fclose(infile);
}