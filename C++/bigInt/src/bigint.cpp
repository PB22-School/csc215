#include "bigint.h"
#include <iostream>
using namespace std;

bigint::bigint(bool negative, string digits) {
    this->negative = negative;
    this->digits = digits;
}

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

    int carry = 0;

    int maxLen = max(b2.digits.length(), digits.length());
    string ndigits = "";

    for (int i = 0; i < maxLen; i++) {

        if (i < digits.length()) {
            carry += digits[i];
        }

        if (i < b2.digits.length()) {
            carry += digits[i];
        }

        ndigits += carry % 10;
        carry /= 10;

    }

    return bigint(false, ndigits);
}

bigint bigint::operator+(string str) {
    return *this + bigint(str);
}

bigint bigint::operator+(int x) {
    return *this + bigint(x);
}