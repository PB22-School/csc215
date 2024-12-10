#include "stdio.h"

#define MAXLENGTH 80

void reverse(string)
char* string;
{
    int length;
    
    length = 0;
    while (string[length] != '\0') {
        length++;
    }

    int i;
    char c;
    for (i = 0; i < (length / 2); i++) {
        c = string[i];
        string[i] = string[length - (i + 1)];
        string[length - (i + 1)] = c;
    }
}

main(argc, argv)
int argc;
char* argv[];
{

    FILE *infile;
    char line[MAXLENGTH];

    if (argc != 2) {
        printf("Usage: backward {infile}");
        return;
    }

    int c;
    int lineCount;

    infile = fopen(argv[1], "r");
    lineCount = 0;

    while ((c = fgetc(infile)) != EOF) {
        if (c == '\n') {
            line[lineCount] = '\0';
            reverse(line);
            printf("%s\n", line);
            lineCount = 0;
            continue;
        }

        line[lineCount] = c;
        lineCount++;
    }

    fclose(infile);
}
