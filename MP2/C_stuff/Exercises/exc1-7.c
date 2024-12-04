/* Exercise 1-8 */
/* Write a program to copy its input to its output, replaccing each string of one or more blanks by a single blank. */

#include <stdio.h>

void main(argc, argv)
int argc;
char* argv[];
{

    FILE *infile, *outfile;

    if (argc < 2) {
        printf("USE MORE INPUTS!!\n");
        printf("USAGE: exc1-7 <infile> <outfile>\n");
    }

    int c, lastWasSpace;
    
    c = 0, lastWasSpace = 0;

    infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");

    while ((c = fgetc(infile)) != EOF) {
        if (c == ' ' && lastWasSpace) {
            continue;
        }
        else if (c == ' ') {
            lastWasSpace = 1;
        }
        else {
            lastWasSpace = 0;
        }

        fputc(c, outfile);
    }

    fclose(infile);
    fclose(outfile);
    return;

}