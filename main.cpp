#include <iostream>
#include <vector>
#include <stdint.h> //defines uint32_t as unsigned 64-bit integer.
#include <cmath>

#include "common.h"

class Dictionary
{
private:
    std::vector<uint32_t> hashTable; // Array to store entries
    uint32_t m;                      // Size of the array
    uint32_t l;                      // # of bits required for hash
    uint32_t a;                      // Random seed

public:
    Dictionary(const std::vector<int> &keys)
    {
        auto n = keys.size();
        m = 2 * n * n;                                  // Multiply shift is 2-universal, hence m must be 2n^2
        l = std::log2(m);                               // Bits required to represent m
        std::vector<uint32_t> hashTable(m, UINT32_MAX); // Set UINT32_MAX as the "unassigned" value
    }

    // Initialize the dictionary
    void initialize(const std::vector<int> &keys)
    {
        int n = keys.size();
        a = random_uint32();

        bool collision = true;
        while (collision)
        {
            collision = false;
            hashTable.assign(m, -1); // Reset hashTable

            // Check for collisions
            for (int i = 0; i < n && !collision; ++i)
            {
                for (int j = i + 1; j < n && !collision; ++j)
                {
                    if (multiply_hash_uint32(keys[i], l, a) == multiply_hash_uint32(keys[j], l, a))
                    {
                        collision = true;
                    }
                }
            }
        };

        // Insert keys into the dictionary
        for (int i = 0; i < n; ++i)
            hashTable[multiply_hash_uint32(keys[i], l, a)] = keys[i];
    }

    // Check if a key exists in the dictionary
    bool check_inclusion(int key)
    {
        return (hashTable[multiply_hash_uint32(key, l, a)] == key);
    }
};

int main()
{
    // auto x = Dictionary(4);
    std::cout << "Hello world" << std::endl;
    return 0;
}
