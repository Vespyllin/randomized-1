#include "common.h"

// 32-bit Multiply-Shift
uint64_t multiply_shift_uint32(uint32_t x, uint64_t l, uint64_t a)
{
    return (a * x) >> (64 - l);
}

uint64_t random_uint64()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(0, UINT64_MAX);
    return dis(gen);
}

uint64_t random_uint64(uint32_t min, uint32_t max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(min, max);
    return dis(gen);
}