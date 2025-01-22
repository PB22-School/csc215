#include "bigint.h"
#include <iostream>
using namespace std;

enum op_codes {

    BAD_OPCODE,
    EXIT,

    ADD,
    SUBTRACT,
    MULTIPLY,

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
    else if (str == "*") {
        return MULTIPLY;
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
    string opCodeIn;
    string numIn;
    int opcode;
    bool result = false;

    cout << "Enter Number: ";
    cin >> numIn;

    bigint accumulator(numIn);
    
    while (true) {
        cout << "Type Operation: ";
        cin >> opCodeIn;

        opcode = toOpcode(opCodeIn);

        if (opcode == BAD_OPCODE) {
            cout << "BAD OPCODE!! '" << opCodeIn << "' IS NOT! A VALID OPCODE." << endl;
            continue;
        }
        else if (opcode == EXIT) {
            break;
        }
 
        cout << "Type New Number: ";
        cin >> numIn;

        other = bigint(numIn);

        cout << endl;

        accumulator.inLinePrint();

        cout << " " << opCodeIn << " " << numIn << " = ";

        switch (opcode) {
            case ADD:
                accumulator += other;
                break;
            case SUBTRACT:
                accumulator -= other;
                break;
            case MULTIPLY:
                accumulator *= other;
                break;
            case EQUAL:
                result = accumulator == other;
                break;
            case NOT_EQUAL:
                result = accumulator != other;
                break;
            case GREATER_THAN:
                result = accumulator > other;
                break;
            case GREATER_THAN_OR_EQUAL:
                result = accumulator >= other;
                break;
            case LESS_THAN:
                result = accumulator < other;
                break;
            case LESS_THAN_OR_EQUAL:
                result = accumulator <= other;
        }

        if (opcode > BOOLEAN_OPERATIONS) {
            if (result) {
                cout << "TRUE";
            }
            else {
                cout << "FALSE";
            }
        }
        else {
            accumulator.inLinePrint();
        }

        cout << "!!\n\n";

    }

    cout << endl << "EXITING." << endl;
}