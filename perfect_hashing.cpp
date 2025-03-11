#include <vector>
#include <stdint.h>
#include <cmath>
#include <iostream>

#include "common.h"

class PerfectHashTable
{
private:
    std::vector<uint32_t> hashTable;       // Array to store entries
    uint32_t m;                            // Size of the array
    uint32_t l;                            // Number of bits required for hash
    uint32_t a;                            // Random seed
    const uint32_t EMPTY_VAL = UINT32_MAX; // Number used to indicate the empty value in a vector

public:
    PerfectHashTable(const std::vector<uint32_t> &keys)
    {
        auto n = keys.size();
        m = 2 * n * n;                                 // Multiply shift is 2-universal, hence m must be 2n^2
        l = std::log2(m);                              // Bits required to represent m
        std::vector<uint32_t> hashTable(m, EMPTY_VAL); // Set UINT32_MAX as the "unassigned" value
    }

    // Initialize the dictionary
    void initialize(const std::vector<uint32_t> &keys)
    {
        int n = keys.size();

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
                    if (multiply_shift_uint32(keys[i], l, a) == multiply_shift_uint32(keys[j], l, a))
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
    bool search(int key)
    {
        return (hashTable[multiply_shift_uint32(key, l, a)] == key);
    }
};