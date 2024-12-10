#include "stdio.h"

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
    printf("\nYou inputted: %s\n", argv[1]);

    reverse(argv[1]);

    printf("\nYour input, reversed: %s\n", argv[1]);
}