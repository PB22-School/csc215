#include "bigint.h"
#include <iostream>
using namespace std;

enum op_codes {

    BAD_OPCODE,
    EXIT,

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

    if (str == "exit") {
        return EXIT;
    }
    else if (str == "+") {
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
    bigint other;
    string in;
    int opcode;

    cout << "Enter Number: ";
    cin >> in;

    bigint accumulator(in);
    
    while (true) {
        cout << "Type Operation: ";
        cin >> in;

        opcode = toOpcode(in);

        if (opcode == BAD_OPCODE) {
            cout << "BAD OPCODE!! " << in << " IS NOT! A VALID OPCODE." << endl;
            continue;
        }

        cout << "Type New Number: ";
        cin >> in;

        other = bigint(in);

        accumulator.inLinePrint();

        switch (opcode) {
            case ADD:
                accumulator += other;
                break;
            case SUBTRACT:
                accumulator -= other;
                break;
            
        }

    }
}