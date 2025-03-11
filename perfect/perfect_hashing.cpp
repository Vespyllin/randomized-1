#include <vector>
#include <stdint.h>
#include <cmath>
#include <iostream>

#include "perfect_hashing.h"
#include "../common/common.h"

PerfectHashTable::PerfectHashTable(uint64_t n)
{
    m = n * n;        // Multiply shift is 2-universal, hence m must be 2 n^2 !! Circumvented for now
    l = std::log2(m); // Bits required to represent m
}

// Initialize the dictionary
void PerfectHashTable::insert(const std::vector<uint32_t> &keys)
{
    auto n = keys.size();

    bool collision = true;
    while (collision)
    {
        collision = false;
        a = random_uint64() | 1;
        hashTable.assign(m, EMPTY_VAL); // Reset hashTable

        // Check for collisions
        for (int i = 0; i < n && !collision; ++i)
        {
            for (int j = i + 1; j < n && !collision; ++j)
            {
                auto ki = multiply_shift_uint32(keys[i], l, a);
                auto kj = multiply_shift_uint32(keys[j], l, a);

                if (keys[i] != keys[j] && ki == kj)
                {
                    collision = true;
                }
            }
        }
    };

    // Insert keys into the dictionary
    for (int i = 0; i < n; ++i)
        hashTable[multiply_shift_uint32(keys[i], l, a)] = keys[i];
}

// Check if a key exists in the dictionary
bool PerfectHashTable::search(uint32_t key)
{
    return (hashTable[multiply_shift_uint32(key, l, a)] == key);
}
