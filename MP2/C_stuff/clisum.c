#include <stdio.h>

int main(argc, argv)
int argc;
char *argv[];

{
    int sum;
    int i;
    int chr;

    sum = 0;

    if (argc == 1) {
        printf("NO INPUTS??\n");
        return;
    }

    for (i = 1; i < argc; i++) {

        if (atoi(argv[i]) == 0 && argv[i] != '0') {
            printf("%s IS NOT A NUMBER!\n", argv[i]);
            continue;
        }

        sum += atoi(argv[i]);
    }

    printf("YOUR SUM IS: %d\n", sum);
}