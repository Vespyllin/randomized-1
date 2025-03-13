#include "chaining_hashing.h"
#include <iostream>

ChainingHashTable::ChainingHashTable(size_t size)
    : table_size(size), table(size) {}

size_t ChainingHashTable::hash(uint32_t key) const
{
    return key % table_size; // Simple mod-based hash function
}

void ChainingHashTable::insert(uint32_t key)
{
    size_t index = hash(key);
    table[index].push_back(key);
}

bool ChainingHashTable::search(uint32_t key) const
{
    size_t index = hash(key);
    const std::list<uint32_t>& chain = table[index];

    for (uint32_t item : chain)
    {
        if (item == key)
        {
            return true;
        }
    }

    return false;
}

void ChainingHashTable::resize(size_t new_size)
{
    std::vector<std::list<uint32_t>> new_table(new_size);

    for (const auto& chain : table)
    {
        for (uint32_t key : chain)
        {
            size_t new_index = key % new_size;
            new_table[new_index].push_back(key);
        }
    }

    table_size = new_size;
    table = std::move(new_table);
}

void ChainingHashTable::printTable() const
{
    for (size_t i = 0; i < table_size; i++)
    {
        std::cout << "Index " << i << ": ";
        for (uint32_t key : table[i])
        {
            std::cout << key << " -> ";
        }
        std::cout << "nullptr" << std::endl;
    }
}

