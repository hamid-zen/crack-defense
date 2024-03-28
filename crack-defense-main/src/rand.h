#pragma once
#include <cstdint>
using t_number = std::uint16_t;

static unsigned long next = 1;

t_number myrand(void);
void mysrand(unsigned int seed);