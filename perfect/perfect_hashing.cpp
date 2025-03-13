#include <vector>
#include <stdint.h>
#include <cmath>
#include <iostream>

#include "perfect_hashing.h"
#include "../common/common.h"

void printVector(const std::vector<uint32_t> &vec)
{
    for (const auto &element : vec)
    {
        if (element == UINT32_MAX)
            std::cout << "_" << ", ";
        else
            std::cout << element << ", ";
    }
    std::cout << std::endl;
}

PerfectHashTable::PerfectHashTable(uint32_t n)
{
    m = 4 * n;        // Size of hash-table (multiple shift is ~2-universal so the required 2cn = 4n)
    l = std::log2(m); // Bits required to represent m
}

// Initialize the dictionary
void PerfectHashTable::insert(const std::vector<uint32_t> &keys)
{
    auto n = keys.size();

    // Compute adequate first-level level hash function
    while (true)
    {
        entries.assign(m, {});
        a = random_uint32() | 1;

        // Count collisions
        for (int i = 0; i < n; i++)
            entries[multiply_shift_uint32(keys[i], l, a)].push_back(keys[i]);

        // Check square of sums
        uint64_t sum = 0;
        for (int i = 0; i < m; ++i)
            sum += entries[i].size() * entries[i].size();

        // Pick a new hash function if the sum exceeds 2n
        if (sum <= 2 * n)
            break;
    }

    entries.reserve(m);
    hashes.reserve(m);
    // Convert buckets to hash tables
    for (int bucket = 0; bucket < m; bucket++)
    {
        auto bucketSize = entries[bucket].size();

        std::vector<uint32_t> entryTable(bucketSize * bucketSize, EMPTY_VAL);

        uint32_t bucketl = std::log2(bucketSize * bucketSize); // Bits required to represent an adequate hash for bucket
        uint32_t bucketa = 0;

        if (bucketSize > 1)
        {
            bool collision = true;
            while (collision)
            {
                collision = false;
                bucketa = random_uint32() | 1;

                for (int i = 0; i < bucketSize && !collision; ++i)
                    for (int j = 0; j < i && !collision; ++j)
                        if (multiply_shift_uint32(entries[bucket][i], bucketl, bucketa) == multiply_shift_uint32(entries[bucket][j], bucketl, bucketa))
                            collision = true;
            }
        }

        // Insert keys into the bucket
        for (size_t i = 0; i < bucketSize; i++)
        {
            auto hash = bucketa == 0 ? 0 : multiply_shift_uint32(entries[bucket][i], bucketl, bucketa);
            entryTable[hash] = entries[bucket][i];
        }

        // Store hash coefficient and convert old bucket to hashed bucket
        entries[bucket] = entryTable;
        hashes[bucket] = bucketa;
    }
}

// Check if a key exists in the dictionary
bool PerfectHashTable::search(uint32_t key)
{
    auto bucketHash = multiply_shift_uint32(key, l, a);

    if (bucketHash > entries.size())
        return false;

    auto bucket = entries[bucketHash];
    auto bucketSize = bucket.size();

    if (bucketSize == 0)
        return false;

    auto bucketHashCoefficient = hashes[bucketHash];

    auto entryHash = bucketHashCoefficient == 0 ? 0 : multiply_shift_uint32(key, std::log2(bucketSize), bucketHashCoefficient);

    if (entryHash > entries[bucketHash].size())
        return false;

    return (entries[bucketHash][entryHash] == key);
}
