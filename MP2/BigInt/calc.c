
#define ADD 1
#define SUB 2
#define MUL 3
#define M   4
#define A   5
#define EQU 6
#define END '\0'

char toLower(chr)
char chr;
{
    if (chr >= 'a' && chr <= 'z') {
        return chr;
    }

    else {
        return chr + 32;
    }
}

int getCode(str)
char** str;
{
    if (str[0] == '+') {
        return ADD;
    }
    else if (str[0] == '-') {
        return SUB;
    }
    else if (str[0] == '*') {
        return MUL;
    }
    else if (str[0] == '=') {
        return EQU;
    }
    else if (toLower(str[0]) == 'm') {
        return M;
    }
    else if (toLower(str[0]) == 'a') {
        return A;
    }
    
    int len;
    len = 0;
    while (str[len] != END) {
        str[len] = toLower(str[len]);
        len++;
    }

    if (len > 3) {

        /* no static arrays 😢 */
        if (str[0] == 'a' && str[1] == 'd' && str[2] == 'd') {
            return ADD;
        }
        else if (str[0] == 's' && str[1] == 'u' && str[2] == 'b') {
            return SUB;
        }
        else if (len > 5) {
            if (str[0] == 't' && str[1] == 'i' && str[2] == 'm' && str[3] == 'e' && str[4] == 's') {
                return MUL;
            }
            else if (len > 6) {
                if (str[0] == 'e' && str[1] == 'q' && str[2] == 'u' && str[3] == 'a' && str[4] == 'l' && str[5] == 's') {
                    return EQU;
                }
            }
        }
    }

    return 0;
}



main()
{
    int num, input, op, isNegative;
    char** strInput;
    op = '$';

    printf("Enter Value: ");
    scanf("%d", &input);

    num = input;

    while (1) {
        printf("\n--> %d\n", num);
        printf("Enter Operation ( +, -, *, =, M, A ): ");
        scanf("%s", strInput);

        op = getCode(strInput);

        if (op == ADD || op == SUB || op == MUL) {
            printf("Enter Number: ");
            scanf("%d", &input);
        }

        switch (op) {
            case ADD:
                num += input;
                break;
            case SUB:
                num -= input;
                break;
            case MUL:
                num *= input;
                break;
            case M:
                num = ~num + 1;
                break;
            case A:
                isNegative = (num & 0x8000) >> 15;

                if (isNegative) {
                    num = ~num + 1;
                }

                break;
            case EQU:
                printf("\nEquals...\n--> %d!", num);
                return;
            default:
                printf("\nError: \"%s\" Not Recognized.\n", strInput);
                continue;

        }

    }
}