/* Exercise 1-9 */
/* How would you test this program? */

/*
    I would test this program by giving it different files
    which contain different amounts of words.
    I'd make sure my program has at least one word seperated by:
    a newline, a space, and a tab.

    Some obvious boundaries are that the number of words is
    stored in an int which only has 2^16 values, meaning it will wrap around at 2^16 + 1.

    Another thing is that a lot of symbols would be counted as a 'word'
    for example, "#%!#$#%" would be a word.
    So would "12345678".
*/

#include "stdio.h"

#define YES 1
#define NO  0

main(argc, argv)
int argc;
char* argv[];
{
    FILE *infile;
    int c, nl, nw, nc, inword;

    if (argc != 2) {
        printf("Incorrect usage.\nDo exc1-8 {infile}. ");
    }

    infile = fopen(argv[1], "r");

    inword = NO;
    nl = nw = nc = 0;
    while ((c = fgetc(infile)) != EOF) {
        ++nc;

        if (c == '\n') {
            ++nl;
        }
        if (c == ' ' || c == '\n' || c == '\t') {
            inword = NO;
        }
        else if (inword == NO) {
            inword = YES;
            ++nw;
        }
    }

    printf("%d %d %d\n", nl, nw, nc);
}