#include "common.h"
#include <set>
#include <vector>
#include <algorithm>
#include <random>

// 32-bit 2-Universal Multiply-Shift
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

// Function to generate structured keys {i² mod n}
std::vector<uint32_t> generateKeys(uint32_t n)
{
    std::set<uint32_t> keys;
    for (uint32_t i = 0; i < n; i++)
    {
        uint32_t x = (i * i) % n;
        if (x != UINT32_MAX)
            keys.insert(x);
    }

    // Return vector of unique keys
    std::vector<uint32_t> keyVector(keys.begin(), keys.end());
    return keyVector;
}

// Function to shuffle keys before insertion
void shuffleKeys(std::vector<uint32_t> &keys)
{
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(keys.begin(), keys.end(), g);
}
