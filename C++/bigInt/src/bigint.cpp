#include "bigint.h"
#include <iostream>
using namespace std;

bigint::bigint(string str) {

    if (str.length() == 0) {
        return;
    }

    printf("inputted: %s", str.c_str());

    negative = str[0] == '-';

    for (int i = negative; i < str.length(); i++) {
        digits[str.length() - (i + !negative)] = str[i] - '0';
        print();
    }

}

void bigint::print() {

    if (negative) {
        cout << '-';
    }

    for (int i = digits.length() - negative; i >= 0; i--) {
        cout << digits[i] + '0';
    }

    cout << endl;
}