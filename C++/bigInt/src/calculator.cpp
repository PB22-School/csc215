#include "bigint.h"
#include <iostream>
using namespace std;

enum op_codes {
    ADD,
    ADD_MEM,
    SUBTRACT,
    SUBTRACT_MEM,

    EQUAL_MEM,
    NOT_EQUAL_MEM,

    GREATER_THAN_MEM,
    GREATER_THAN_EQUAL_MEM,

    LESS_THAN_MEM,
    LESS_THAN_EQUAL_MEM

};


int main() {
    bigint mem;
    char in;
    int opcode;
    
    while (true) {
        cin >> in;

    }
}