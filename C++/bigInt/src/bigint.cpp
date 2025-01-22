#include "bigint.h"
#include <iostream>
using namespace std;

bigint::bigint(string str) {

    if (str.length() == 0) {
        return;
    }

    cout << str << endl;

    negative = str[0] == '-';

    for (int i = negative; i < str.length(); i++) {
        digits[str.length() - (i + !negative)] = str[i] - '0';
        print();
    }

    digitLength = str.length() - negative;

}

void bigint::print() {

    if (negative) {
        cout << '-';
    }

    for (int i = digitLength - negative; i >= 0; i--) {
        cout << digits[i] + '0';
    }

    cout << endl;
}