#include "rand.h"

t_number myrand(void) {
    next = next * 1103515245 + 12345;
    return((t_number)(next/65536) % 32768);
}

void mysrand(unsigned int seed) {
    next = seed;
}