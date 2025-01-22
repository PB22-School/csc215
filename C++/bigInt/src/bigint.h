#ifndef BIGINT_H
#define BIGINT_H

#include <string>

#define INIT_DIGIT_LENGTH 2
using namespace std;

class bigint {

    private:
    bool negative;
    char digits[INIT_DIGIT_LENGTH];
    unsigned digitLength;

    bigint();

    public:

    static bigint from_str(string str);
    static bigint from_int(int x);

    void print();

    bigint operator+(bigint b2);
    bigint operator+(string str);
    bigint operator+(int x);

    bigint operator+=(bigint b2);
    bigint operator+=(string str);
    bigint operator+=(int x);

    bigint operator++();
    
    bigint operator-(bigint b2);
    bigint operator-(string str);
    bigint operator-(int x);

    bigint operator-=(bigint b2);
    bigint operator-=(string str);
    bigint operator-=(int x);

    bigint operator--();

};

#endif // BIGINT_H