#include "bigint.h"
#include <iostream>

using namespace std;

string removePadding(string str) {
    for (int i = str.length() - 1; i >= 0; i--) {
        if (i != 0) {
            return str;
        }

        // i == 0

        str.resize(str.length() - 1);
    }

    return str;
}

bigint::bigint(bool negative, string digits) {
    this->negative = negative;
    this->digits = digits;
}

bigint::bigint(string str) {

    if (str.length() == 0) {
        return;
    }

    negative = str[0] == '-';

    for (int i = str.length() - 1; i >= negative; i--) {
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

    // for (int i = 0; i < digits.length() / 2; i++) {
    //     char dig = digits[i];
    //     digits[i] = digits[digits.length() - (i + 1)];
    //     digits[digits.length() - (i + 1)] = dig;
    // }
}

void bigint::print() {

    if (negative) {
        cout << '-';
    }

    for (int i = digits.length() - 1; i >= 0; i--) {
        putchar(digits[i] + '0');
    }

    cout << endl;
}

bigint bigint::operator+(bigint b2) {

    /*
    
    a  +  b = a + b
    a  + -b = a - b
    -a +  b = b - a
    -a + -b = -(a + b)
    
    */

    bool newIsNegative = false;
    
    if (negative) {
        if (b2.negative) {
            // -a + -b = -(a + b)
            newIsNegative = true;
        }
        else {
            // -a + b = b - a
            b2.negative = false;
            negative = false;
            return b2 - *this;
        }
    }
    else {
        if (b2.negative) {
            // a + -b = a - b
            b2.negative = false;
            negative = false;
            return *this - b2;
        }
        else {
            // a + b
            // just do regular addition!
        }
    }

    int carry = 0;

    int maxLen = max(b2.digits.length(), digits.length());
    string ndigits = "";

    for (int i = 0; i < maxLen; i++) {

        if (i < digits.length()) {
            carry += digits[i];
        }

        if (i < b2.digits.length()) {
            carry += b2.digits[i];
        }

        ndigits += carry % 10;
        carry /= 10;

    }

    if (carry) {
        ndigits += carry;
    }

    return bigint(false, ndigits);
}

bigint bigint::operator+(string str) {
    return *this + bigint(str);
}

bigint bigint::operator+(int x) {
    return *this + bigint(x);
}

void bigint::operator+=(bigint b2) {
    *this = *this + b2;
}

void bigint::operator+=(string str) {
    *this = *this + str;
}

void bigint::operator+=(int x) {
    *this = *this + x;
}

void bigint::operator++() {
    *this += 1;
}

bigint bigint::operator-(bigint b2) {

    /*
    
    a  - b  = a - b
    a  - -b = a + b
    -a - b  = -(a + b)
    -a - -b = -a + b = b - a
    
    */

    if (negative) {
        if (b2.negative) {
            // -a - -b = -a + b = b - a
            negative = false;
            b2.negative = false;
            return b2 - *this;
        }
        else {
            // -a - b = -(a + b)
            b2.negative = true;
            return *this + b2;
        }
    }
    else {
        if (b2.negative) {
            // a - -b = a + b
            b2.negative = false;
            return *this + b2;
        }
        else {
            // a - b
            // just do regular subtraction!
        }
    }

    bool takeOneFlag = false;
    int columnSum = 0;

    string ndigits = "";

    for (int i = 0; i < digits.length(); i++) {

        columnSum = -takeOneFlag;
        takeOneFlag = false;

        if (i < digits.length()) {
            columnSum += digits[i];
        }

        if (i < b2.digits.length()) {

            columnSum -= b2.digits[i];

            if (b2.digits[i] > columnSum) {
                takeOneFlag = true;
                columnSum += 10;
            }
            
        }

        ndigits += columnSum;

    }

    ndigits = removePadding(ndigits);

    return bigint(false, ndigits);

}

bigint bigint::operator-(string str) {
    return *this - bigint(str);
}

bigint bigint::operator-(int x) {
    return *this - bigint(x);
}

void bigint::operator-=(bigint b2) {
    *this = *this - b2;
}

void bigint::operator-=(string str) {
    *this = *this - str;
}

void bigint::operator-=(int x) {
    *this = *this - x;
}

void bigint::operator--() {
    *this = *this - 1;
}

bool bigint::operator==(bigint b2) {
    return digits == b2.digits;
}

bool bigint::operator==(string str) {
    return digits == bigint(str).digits;
}

bool bigint::operator==(int x) {
    return digits == bigint(x).digits;
}

bool bigint::operator!=(bigint b2) {
    return !(digits == b2.digits);
}

bool bigint::operator!=(string str) {
    return !(digits == bigint(str).digits);
}

bool bigint::operator!=(int x) {
    return !(digits == bigint(x).digits);
}

bool bigint::operator>(bigint b2) {
    if (!negative && b2.negative) {
        // + > -
        return true;
    }
    
    if (negative && !b2.negative) {
        // - > +
        return false;
    }

    if (digits.length() > b2.digits.length()) {
        return true;
    }
    
    if (digits.length() < b2.digits.length()) {
        return false;
    }

    // digits lengths are equal
    for (int i = 0; i < digits.length(); i++) {

        if (digits[i] > b2.digits[i]) {
            return true;
        }

        if (digits[i] < b2.digits[i]) {
            return false;
        }
    }

    return false;

}

bool bigint::operator>(string str) {
    return *this > bigint(str);
}

bool bigint::operator>(int x) {
    return *this > bigint(x);
}

bool bigint::operator>=(bigint b2) {
    return (*this == b2) || (*this > b2);
}

bool bigint::operator>=(string str) {
    return (*this == bigint(str)) || (*this > bigint(str));
}

bool bigint::operator>=(int x) {
    return (*this == bigint(x)) || (*this > bigint(x));
}

bool bigint::operator<(bigint b2) {
    return !(*this >= b2);
}

bool bigint::operator<(string str) {
    return !(*this >= bigint(str));
}

bool bigint::operator<(int x) {
    return !(*this >= bigint(x));
}

bool bigint::operator<=(bigint b2) {
    return !(*this > b2);
}

bool bigint::operator<=(string str) {
    return !(*this > bigint(str));
}

bool bigint::operator<=(int x) {
    return !(*this > bigint(x));
}

bigint::operator bool() const {
    return digits == "0";
}

bool bigint::operator !() const {
    return !bool(*this);
}