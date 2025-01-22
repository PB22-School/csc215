#include "bigint.h"
using namespace std;

bigint::bigint() {}

bigint bigint::from_str(string str) {

    bigint bint;

    if (str.length() == 0) {
        return bint;
    }

    bint.negative = str[0] == '-';

    for (int i = bint.negative; i < str.length(); i++) {
        bint.digits[str.length() - (i + !bint.negative)] = str[i] - '0';
    }
    bint.print();

    bint.digitLength = str.length() - bint.negative;

    return bint;

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