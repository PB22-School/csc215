#include "bigint.h"
using namespace std;

bigint::bigint(string str) {

    if (str.length() == 0) {
        return;
    }

    negative = str[0] == '-';

    for (int i = bint.negative; i < str.length(); i++) {
        digits[str.length() - (i + !negative)] = str[i] - '0';
    }

    digitLength = str.length() - negative;

}

void bigint::print() {

    if (negative) {
        putchar('-');
    }

    for (int i = digitLength - 1; i >= 0; i--) {
        printf("%d", digits[i]);
    }

    putchar('\n');
}