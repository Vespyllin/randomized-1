#ifndef PERFECTHASHTABLE_H
#define PERFECTHASHTABLE_H

#include <stdint.h> //defines uint32_t as unsigned 64-bit integer.

class PerfectHashTable
{
private:
    std::vector<uint32_t> hashTable;       // Array to store entries
    uint32_t m;                            // Size of the array
    uint32_t l;                            // Number of bits required for hash
    uint32_t a;                            // Random seed
    const uint32_t EMPTY_VAL = UINT32_MAX; // Number used to indicate the empty value in a vector

public:
    PerfectHashTable(uint32_t n);

    void insert(const std::vector<uint32_t> &keys);

    bool search(uint32_t key);
};

#endif // PERFECTHASHTABLE_H