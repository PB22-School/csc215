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

int toOpcode(string str) {

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

                break;
        }

    }
}