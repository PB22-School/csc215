#include <stdio.h>

#define MAX_ARR_SIZE 80
#define MAX_SPACE 3

int getDigits(x)
int x;
{
    int i;
    i = 0;
    while (x > 0) {
        x /= 10;
        i++;
    }

    return i;
}

char* multipleChr(chr, amount)
char chr;
int amount;
{
    char ret[MAX_ARR_SIZE];

    int i;
    for (i = 0; i < amount; i++) {
        ret[i] = chr;
    }

    ret[i] = '\0';

    return ret;
}

void main(argc, argv)
int argc;
char* argv[];
{
    FILE *infile;
    int chr;
    int chrCount;
    char line[MAX_ARR_SIZE];

    if (argc != 2) {
        printf("Usage: chrnums {infile}\n");
        return;
    }

    infile = fopen(argv[1], "r");
    chrCount = 0;
    
    while ((chr = fgetc(infile)) != EOF) {
        if (chr == '\n') {
            line[chrCount] = '\0';
            printf("%d:%s%s\n", chrCount, multipleChr(' ', MAX_SPACE - getDigits(chrCount)), line);
            chrCount = 0;
            continue;
        }

        line[chrCount] = chr;
        chrCount++;
    }

    if (chrCount) {
        printf("%d:%s%s\n", chrCount, multipleChr(' ', MAX_SPACE - getDigits(chrCount)), line);
    }

    fclose(infile);
}