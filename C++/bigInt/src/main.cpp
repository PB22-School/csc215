#include "bigint.h"

int main() {
    bigint bint("1000");
    bigint bint2(1);

    bint.print();
    bint2.print();

    bint -= bint2;
    bint.print();
}