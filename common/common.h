// common.h
#ifndef COMMON_H
#define COMMON_H

#include <stdint.h> //defines uint32_t as unsigned 64-bit integer.
#include <random>

uint32_t multiply_shift_uint32(uint32_t x, uint32_t l, uint32_t a);

uint32_t random_uint32();

uint32_t random_uint32(uint32_t min, uint32_t max);

#endif // COMMON_H