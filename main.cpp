#include <iostream>
#include <vector>
#include <stdint.h> //defines uint32_t as unsigned 64-bit integer.
#include <cmath>

#include "common.h"

class Dictionary
{
private:
    std::vector<uint32_t> hashTable;       // Array to store entries
    uint32_t m;                            // Size of the array
    uint32_t l;                            // Number of bits required for hash
    uint32_t a;                            // Random seed
    const uint32_t EMPTY_VAL = UINT32_MAX; // Number used to indicate the empty value in a vector

    // Initialize the dictionary
    void initialize(const std::vector<uint32_t> &keys)
    {
        int n = keys.size();

        bool collision = true;
        while (collision)
        {
            a = random_uint32() | 1;
            collision = false;
            hashTable.assign(m, EMPTY_VAL); // Reset hashTable

            // Check for collisions
            for (int i = 0; i < n && !collision; ++i)
            {
                for (int j = i + 1; j < n && !collision; ++j)
                {
                    if (multiply_shift_uint32(keys[i], l, a) == multiply_shift_uint32(keys[j], l, a))
                    {
                        std::cout << "Collision with seed " << a << " at indices " << i << " and " << j << ", value " << keys[i] << ". Retrying." << std::endl;
                        collision = true;
                    }
                }
            }
        };

        // Insert keys into the dictionary
        for (int i = 0; i < n; ++i)
            hashTable[multiply_shift_uint32(keys[i], l, a)] = keys[i];
    }

public:
    Dictionary(const std::vector<uint32_t> &keys)
    {
        auto n = keys.size();
        m = 2 * n * n;                                 // Multiply shift is 2-universal, hence m must be 2n^2
        l = std::log2(m);                              // Bits required to represent m
        std::vector<uint32_t> hashTable(m, EMPTY_VAL); // Set UINT32_MAX as the "unassigned" value

        initialize(keys);
    }

    // Check if a key exists in the dictionary
    bool check_inclusion(int key)
    {
        return (hashTable[multiply_shift_uint32(key, l, a)] == key);
    }
};

template <typename T>
bool find(const std::vector<T> &vec, const T &value)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == value)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    std::cout << "Creating key vector." << std::endl;

    const size_t key_space_size = std::pow(2, 14);
    std::vector<u_int32_t> keys = {};
    for (size_t i = 0; i < key_space_size; i++)
    {
        keys.push_back(random_uint32(0, UINT32_MAX - 1));
    }

    std::cout << "Creating bad key vector." << std::endl;

    std::vector<u_int32_t> bad_keys = {};
    for (size_t i = 0; i < key_space_size; i++)
    {
        auto x = random_uint32(0, UINT32_MAX - 1);
        if (find(keys, x))
        {
            --i;
            continue;
        }
        bad_keys.push_back(x);
    }

    keys.shrink_to_fit();
    bad_keys.shrink_to_fit();
    std::cout << "Initializing dictionary." << std::endl;
    auto dict = Dictionary(keys);

    int bad = 0;
    std::cout << "Testing dictionary." << std::endl;
    for (uint32_t i = 0; i < key_space_size; i++)
    {
        bool bad_hit = dict.check_inclusion(bad_keys[i]);
        bool good_hit = dict.check_inclusion(keys[i]);

        if (bad_hit || !good_hit)
            bad++;
    }

    std::cout << "Bad hits:" << bad << "/" << keys.size() + bad_keys.size() << std::endl;

    return 0;
}
