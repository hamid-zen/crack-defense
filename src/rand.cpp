#include "rand.h"
#include <iostream>
static std::uint32_t next= 2;

t_number myrand(void) {
    next = next * 1103515245 + 12345;
    return ((t_number)(next/65536) % 32768);
}

void mysrand(t_number seed) {
    next = seed;
}

std::uint32_t seed() {
    return next;
}
