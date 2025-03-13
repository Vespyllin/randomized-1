// common.h
#ifndef COMMON_H
#define COMMON_H

#include <stdint.h> //defines uint32_t as unsigned 64-bit integer.
#include <vector>

uint32_t multiply_shift_uint32(uint32_t x, uint32_t l, uint32_t a);

uint32_t random_uint32();

uint32_t random_uint32(uint32_t min, uint32_t max);

std::vector<uint32_t> generateKeys(uint32_t n);

void shuffleKeys(std::vector<uint32_t> &keys);

#endif // COMMON_H