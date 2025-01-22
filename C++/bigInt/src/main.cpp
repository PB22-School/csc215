#include "bigint.h"

int main() {
    bigint bint("2025");
    bigint bint2(2025);

    bint.print();
    bint2.print();

    bint += bint2;
    bint.print();
}