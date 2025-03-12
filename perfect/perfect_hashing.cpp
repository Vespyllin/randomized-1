#include <vector>
#include <stdint.h>
#include <cmath>
#include <iostream>

#include "perfect_hashing.h"
#include "../common/common.h"

PerfectHashTable::PerfectHashTable(uint32_t n)
{
    m = 2 * n * n;    // Multiply shift is 2-universal, hence m must be 2n^2
    l = std::log2(m); // Bits required to represent m
}

// Initialize the dictionary
int PerfectHashTable::insert(const std::vector<uint32_t> &keys)
{
    auto n = keys.size();

    int collisions = 0;
    bool collision = true;
    while (collision)
    {
        collision = false;
        a = random_uint32() | 1;
        hashTable.assign(m, EMPTY_VAL); // Reset hashTable

        // Check for collisions
        for (int i = 0; i < n && !collision; ++i)
        {
            for (int j = i + 1; j < n && !collision; ++j)
            {
                if (keys[i] != keys[j] && multiply_shift_uint32(keys[i], l, a) == multiply_shift_uint32(keys[j], l, a))
                {
                    // std::cout << "C" << keys[i] << ":" << keys[j] << " - " << multiply_shift_uint32(keys[i], l, a) << " : " << multiply_shift_uint32(keys[j], l, a) << " " << EMPTY_VAL << std::endl;
                    collision = true;
                    collisions++;
                }
            }
        }
    };

    // Insert keys into the dictionary
    for (int i = 0; i < n; ++i)
        hashTable[multiply_shift_uint32(keys[i], l, a)] = keys[i];

    return collisions;
}

// Check if a key exists in the dictionary
bool PerfectHashTable::search(uint32_t key)
{
    return (hashTable[multiply_shift_uint32(key, l, a)] == key);
}
