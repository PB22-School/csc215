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
        digits[i] = x % 10;
        x /= 10;
    }
}

void bigint::print() {

    if (negative) {
        cout << '-';
    }

    for (int i = 0; i < digits.length(); i++) {
        cout << digits[i] + '0';
    }

    cout << endl;
}