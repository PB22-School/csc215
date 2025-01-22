#ifndef BIGINT_H
#define BIGINT_H

#include <string>

#define INIT_DIGIT_LENGTH 2
using namespace std;

template <typename T>

class bigint {

    private:
    bool negative;
    string digits;

    bigint(bool negative, string digits);

    public:

    bigint(string str);
    bigint(int x);

    void print();

    // ADDITION OPERATORS:

    bigint operator+(bigint b2);
    bigint operator+(T t);

    void operator+=(bigint b2);
    void operator+=(T t);

    void operator++();

    // SUBTRACTION OPERATORS:
    
    bigint operator-(bigint b2);
    bigint operator-(T t);

    void operator-=(bigint b2);
    void operator-=(T t);

    void operator--();

    // BOOLEAN LOGIC OPERATORS:

    bool operator>(bigint b2);
    bool operator<(bigint b2);
    bool operator>=(bigint b2);
    bool operator<=(bigint b2);

};

#endif // BIGINT_H