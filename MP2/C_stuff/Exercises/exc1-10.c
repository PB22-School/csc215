#include <stdio.h>

#define TRUE 1
#define FALSE 0

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
        printf("USAGE: exc1-10 {infile}\n");
        return;
    }

    infile = fopen(argv[1], "r");
    wordCount = lineCount = inWord = 0;

    while ((chr = fgetc(infile)) != EOF) {

        if (chr == '\n' || chr == ' ' || chr == '\t') {
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
        else if (!inWord) {
            inWord = TRUE;
        }
    }

    if (inWord) {
        wordCount++;
    }
    
    printf("Line %d had %d words.\n", lineCount, wordCount);

    fclose(infile);
}