// common.h
#ifndef COMMON_H
#define COMMON_H

#include <stdint.h> //defines uint32_t as unsigned 64-bit integer.
#include <random>

uint64_t multiply_shift_uint32(uint32_t x, uint64_t l, uint64_t a);

uint64_t random_uint64();

uint64_t random_uint64(uint32_t min, uint32_t max);

#endif // COMMON_H