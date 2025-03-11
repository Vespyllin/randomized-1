#ifndef PERFECTHASHTABLE_H
#define PERFECTHASHTABLE_H

class PerfectHashTable
{
private:
    std::vector<uint32_t> hashTable;       // Array to store entries
    uint32_t m;                            // Size of the array
    uint32_t l;                            // Number of bits required for hash
    uint32_t a;                            // Random seed
    const uint32_t EMPTY_VAL = UINT32_MAX; // Number used to indicate the empty value in a vector

public:
    // Constructor
    PerfectHashTable(const std::vector<uint32_t> &keys);

    // Initialize the hash table
    void initialize(const std::vector<uint32_t> &keys);

    // Check if a key exists in the hash table
    bool search(int key);
};

#endif // PERFECTHASHTABLE_H