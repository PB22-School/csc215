#include "stdio.h"
#define STR_END '\0'
#define TRUE 1
#define FALSE 0

#define ADD 2
#define SUB 3
#define MUL 4
#define EQU 5
#define MMM 6
#define AAA 7
#define IDK 8

char* bigScopeString;

struct bigInt {
    int isNegative;
    int length;
    char* bigNum;
};

int max(x, y)
int x;
int y;
{
    if (y > x) {
        return y;
    }
    
    return x;
}

int min(x, y)
int x;
int y;
{
    if (x > y) {
        return y;
    }

    return x;
}

void invert(bint)
struct bigInt* bint;
{
    bint->isNegative = !bint->isNegative;
}

int toOp(op)
char op;
{
    if (op >= 'A' && op <= 'Z') {
        op += 32;
    }

    switch (op) {
        case '+':
            return ADD;
        case '-':
            return SUB;
        case '*':
            return MUL;
        case '=':
            return EQU;
        case 'm':
            return MMM;
        case 'a':
            return AAA;
        default:
            return IDK;
    }
}

void bifree(bint)
struct bigInt* bint;
{
    free(bint->bigNum);
}

void strtobi(str, bint)
char* str;
struct bigInt* bint;
{
    int i;
    int len;
    int positive;
    len = strlen(str);

    if (str[0] == '-') {
        bint->isNegative = TRUE;
        positive = FALSE;
        len--;
    }
    else {
        bint->isNegative = FALSE;
        positive = TRUE;
    }


    bint->bigNum = alloc(len);

    for (i = 0; i < len; i++) {
        if (!isdigit(str[len - (i + positive)])) {
            bint->bigNum[i] = 0xA;
            continue;
        }
        bint->bigNum[i] = str[len - (i + positive)] - '0';
    }

    bint->length = len;
}

void itobi(x, bint)
int x;
struct bigInt* bint;
{
    int xCopy, len;
    xCopy = x;
    len = 0;

    if (x & 0x8000) {
        /* is negative */
        bint->isNegative = TRUE;
        x = ~x + 1;
    }
    else {
        bint->isNegative = FALSE;
    }

    while (xCopy) {
        xCopy /= 10;
        len++;
    }

    bint->bigNum = alloc(len + 1);
    int i;
    i = 0;

    while (x) {
        bint->bigNum[i] = x % 10;
        x /= 10;
        i++;
    }

    bint->length = len;

}

void bisub(bint1, bint2) 
struct bigInt* bint1;
struct bigInt* bint2;
{
    int i, carry, borrow, negative, len;

    if (bint1->isNegative ^ bint2->isNegative) {
        /* hard to subtract, we'd rather have it be two of the same type */

        /* if the second one is the negative one, we can easily invert it's sign then add. */

        if (bint2->isNegative) {

            /* a - (-b) = a + b*/

            invert(bint2);
            biadd(bint1, bint2);
            return;
        }
        else {
            /* (-a) - b = -(a + b) */

            invert(bint1);
            invert(bint2);
            biadd(bint1, bint2);
            invert(bint1);
            return;
        }
    }

    else {
        
        /* pos(a) - pos(b) is easy (a - b) */
        /* neg(a) - neg(a) = neg(a) + b = -(a - b) */

        if (bint1->isNegative) {
            /* -(a - b) */
            negative = TRUE;
            invert(bint1);
            invert(bint2);
        }
        else {
            /* a - b */
            negative = FALSE;
        }
    }

    carry = FALSE;
    i = 0;
    
    len = max(bint1->length, bint2->length);

    bigScopeString = alloc(len);

    do {
        if (i < bint1->length) {
            borrow = bint1->bigNum[i] - carry;
        }
        if (i < bint2->length) {
            borrow -= bint2->bigNum[i];
            if (borrow < 0 && !carry) {
                borrow = 10 + borrow;
                carry = TRUE;
            }
            else if (borrow >= 0) {
                carry = FALSE;
            }
            else if (carry) {
                bigScopeString[i - 1] = 10 - bigScopeString[i - 1];
                negative = !negative;
                carry = FALSE;
                borrow = ~borrow + 1;
            }
        }

        bigScopeString[i] = borrow;
        i++;
    } while (i < len);

    bifree(bint1);
    bint1->bigNum = bigScopeString;

    bint1->isNegative = negative;
}

/* returns bint1 += bint2 */
void biadd(bint1, bint2)
struct bigInt* bint1;
struct bigInt* bint2;
{
    int i, carry, len, negative;
    char* str;

    if (bint1->isNegative ^ bint2->isNegative) {
        /* this is hard, we want both to be the same sign. */

        /* -a + b = y  */
        /*  a - b = -y */
        if (bint1->isNegative) {
            invert(bint1);
            invert(bint2);

            printf("positive: %d, negative: %d\n", bint1->isNegative, bint2->isNegative);

            bisub(bint1, bint2);
            invert(bint1);
            return;
        }
        else {
            /* a + -b = a - b*/
            /* is a simple subtract */
            invert(bint2);
            bisub(bint1, bint2);
            return;
        }
    }
    else {
        /* a + b or -a + -b */
        if (bint1->isNegative) {
            /* -a + -b = -(a + b) */
            negative = TRUE;
            invert(bint1);
            invert(bint2);
        }
        else {
            /* a + b */
            negative = FALSE;
        }
    }

    carry = 0;
    i = 0;

    len = max(bint1->length, bint2->length);

    str = alloc(len);

    do {
        if (i < bint1->length) {
            carry += bint1->bigNum[i];
        }
        if (i < bint2->length) {
            carry += bint2->bigNum[i];
        }

        str[i] = carry % 10;
        carry /= 10;
        i++;

    } while (carry || (i < len));

    if (carry) {
        bifree(bint1);
        bint1->bigNum = alloc(len + 1);
        bint1->length++;
        bint1->bigNum[len] = carry;
    }
    else if (bint1->length != len) {
        bifree(bint1);
        bint1->bigNum = alloc(len);
    }

    for (i = 0; i < len; i++) {
        bint1->bigNum[i] = str[i];
    }

    bint1->isNegative = negative;

    free(str);
}


void printBint(bint)
struct bigInt* bint;
{
    int i;

    if (bint->isNegative) {
        printf("-");
    }

    for (i = (bint->length - 1); i >= 0; i--) {
        printf("%d", bint->bigNum[i]);   
    }

    printf("\n");
    
}

main(argc, argv)
int argc;
char* argv[];
{
    struct bigInt* bintSum;
    struct bigInt* bintOperand;
    char* strInput;
    int op;

    printf("Enter First Number: ");
    scanf("%s",strInput);
    strtobi(strInput, bintSum);

    while (TRUE) {
        printf("Enter Operand (+, -, *, M, A): ");
        scanf("%c", &op);
        printf("\n\n");

        op = toOp(op);

        if (!(op == MMM || op == AAA || op == EQU)) {
            printf("Enter Operand Number: ");
            scanf("%s\n", strInput);
            printf("\n\n");
            strtobi(strInput, bintOperand);
        }

        if (op == EQU) {
            break;
        }

        switch (op) {
            case ADD:
                biadd(bintSum, bintOperand);
                break;
            case SUB:
                bisub(bintSum, bintOperand);
                break;
            case MUL:
                printf("nuh");
                break;
            case MMM:
                invert(bintSum);
                break;
            case AAA:
                bintSum->isNegative = FALSE;
                break;

        }

        printf("\n--> ");
        printBint(bintSum);
        free(&bintOperand->bigNum);
    }

    printf("\nEquals... ");
    printBint(bintSum);
}