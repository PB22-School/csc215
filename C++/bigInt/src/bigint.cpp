#include "bigint.h"
#include <iostream>
using namespace std;

bigint::bigint(string str) {

    if (str.length() == 0) {
        return;
    }

    negative = str[0] == '-';

    for (int i = negative; i < str.length(); i++) {
        digits += str[i] - '0';
    }

}

bigint::bigint(int x) {
    negative = x < 0;

    int i = 0;

    while (x) {
        digits += x % 10;
        x /= 10;
    }

    for (int i = 0; i < digits.length() / 2; i++) {
        char dig = digits[i];
        digits[i] = digits[digits.length() - (i + 1)];
        digits[digits.length() - (i + 1)] = dig;
    }
}

void bigint::print() {

    if (negative) {
        cout << '-';
    }

    for (int i = 0; i < digits.length(); i++) {
        putchar(digits[i] + '0');
    }

    cout << endl;
}

bigint bigint::operator+(bigint b2) {
    
}

bigint bigint::operator+(string str) {

}

bigint bigint::operator+(int x) {

}