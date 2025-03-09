#include "common.h"

// 32-bit Multiply-Shift
uint32_t multiply_shift_uint32(uint32_t x, uint32_t l, uint32_t a)
{
    return (a * x) >> (32 - l);
}

uint32_t random_uint32()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis(0, UINT32_MAX);
    return dis(gen);
}

uint32_t random_uint32(uint32_t min, uint32_t max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis(min, max);
    return dis(gen);
}
