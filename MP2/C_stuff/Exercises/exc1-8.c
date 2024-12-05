/* Exercise 1-8 */
/* Replace every tab with >, backspace, -, and every backspace with <, backspace, - */

#include <stdio.h>

int main(argc, argv)
int argc;
char* argv[];
{

    FILE *infile, *outfile;

    if (argc < 2) {
        printf("INCORRECT USAGE.\n");
        printf("CORRECT USAGE: exc1-8 <infile> <outfile>\n");
        return;
    }

    infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");
    int c;

    while ((c = fgetc(infile)) != EOF) {
        if (c == '\t') {
            fputc('>', outfile);
            continue;
        }
        
        fputc(c, outfile);
    }

    fclose(infile);
    fclose(outfile);
    return 0;
}