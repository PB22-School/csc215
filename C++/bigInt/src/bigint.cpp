#include "bigint.h"
#include <iostream>
using namespace std;

bigint::bigint(string str) {

    if (str.length() == 0) {
        return;
    }

    cout << str << endl;
    cout << str.length() << endl;

    negative = str[0] == '-';

    for (int i = negative; i < str.length(); i++) {
        digits[str.length() - (i + !negative)] = str[i];
        cout << i << " : " << str.length() - (i + !negative) << endl;
        cout << str[i] << " to pos " << str.length() - (i + !negative) << endl;
    }

    cout << endl << str << endl;
    cout << digits << endl;

}

void bigint::print() {

    if (negative) {
        cout << '-';
    }

    for (int i = digits.length() - negative; i >= 0; i--) {
        cout << digits[i];
    }

    cout << endl;
}