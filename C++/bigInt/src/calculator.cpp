#include "bigint.h"
#include <iostream>
using namespace std;

enum op_codes {

    BAD_OPCODE,

    ADD,
    SUBTRACT,

    BOOLEAN_OPERATIONS,

    EQUAL,
    NOT_EQUAL,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_OR_EQUAL,
    LESS_THAN_OR_EQUAL

};

int toOpcode(string str) {

    if (str == "+") {
        return ADD;
    }
    else if (str == "-") {
        return SUBTRACT;
    }
    else if (str == "=") {
        return EQUAL;
    }
    else if (str == "!=") {
        return NOT_EQUAL;
    }
    else if (str == ">") {
        return GREATER_THAN;
    }
    else if (str == ">=") {
        return GREATER_THAN_OR_EQUAL;
    }
    else if (str == "<") {
        return LESS_THAN;
    }
    else if (str == "<=") {
        return LESS_THAN_OR_EQUAL;
    }

    return BAD_OPCODE;
}


int main() {
    bigint mem;
    string in;
    int opcode;

    cout << "Enter Number: ";
    cin >> in;

    bigint accumulator(in);
    
    while (true) {
        cout << "Type Operation: ";
        cin >> in;

        opcode = toOpcode(in);

        switch (opcode) {
            case ADD:
                accumulator += 
                break;
        }

    }
}