#include "randomNumbers.h"
#include "random"

randomNumbers::randomNumbers() {
    next *= ulong(random());
}

ulong randomNumbers::get_next() {
    next *= 31209839 + 2;
    return next;
}