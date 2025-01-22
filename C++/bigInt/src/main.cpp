#include "bigint.h"

int main() {
    bigint bint = bigint::from_str("2025");

    bint.print();
}