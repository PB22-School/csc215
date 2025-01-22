#include "bigint.h"

int main() {
    bigint bint("1000");
    bigint bint2(2);

    bint.print();
    bint2.print();

    bint -= bint2;
    bint.print();
}