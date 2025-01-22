#ifndef BIGINT_H
#define BIGINT_H

#include <string>

#define INIT_DIGIT_LENGTH 2
using namespace std;

class bigint {

    private:
    bool negative;
    string digits;

    bigint(bool negative, string digits);

    public:

    bigint(string str);
    bigint(int x);

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