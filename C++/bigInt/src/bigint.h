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

    // ADDITION OPERATORS:

    bigint operator+(bigint b2);
    bigint operator+(string str);
    bigint operator+(int x);

    void operator+=(bigint b2);
    void operator+=(string str);
    void operator+=(int x);

    void operator++();

    // SUBTRACTION OPERATORS:
    
    bigint operator-(bigint b2);
    bigint operator-(string str);
    bigint operator-(int x);

    void operator-=(bigint b2);
    void operator-=(string str);
    void operator-=(int x);

    void operator--();

    // BOOLEAN LOGIC OPERATORS:

    bool operator==(bigint b2);
    bool operator==(string str);
    bool operator==(int x);

    bool operator!=(bigint b2);
    bool operator!=(string str);
    bool operator!=(int x);

    bool operator>(bigint b2);
    bool operator>(string str);
    bool operator>(int x);

    bool operator>=(bigint b2);
    bool operator>=(string str);
    bool operator>=(int x);

    bool operator<(bigint b2);
    bool operator<(string str);
    bool operator<(int x);

    bool operator<=(bigint b2);
    bool operator<=(string str);
    bool operator<=(int x);

    operator bool() const;
    bool operator !() const;

};

#endif // BIGINT_H