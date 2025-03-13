#ifndef CHAINING_HASHING_H
#define CHAINING_HASHING_H

#include <vector>
#include <list>
#include <cstdint>
#include <iostream>

class ChainingHashTable
{
private:
    // Vector of lists for chaining
    std::vector<std::list<uint32_t>> table;
    size_t table_size;

    // Hash function to map keys to table indices
    size_t hash(uint32_t key) const;

public:
    ChainingHashTable(size_t size);

    // Method to insert a key into the hash table
    void insert(uint32_t key);

    // Method to query if a key exists in the hash table
    bool search(uint32_t key) const;

    // Method to print the table (for debugging)
    void printTable() const;

    // Method to resize the table
    void resize(size_t new_size);
};

#endif

