#include "chaining_hashing.h"
#include <iostream>
#include <fstream>

ChainingHashTable::ChainingHashTable(size_t size)
    : table_size(size), table(size), largest_list_size(0) {}

size_t ChainingHashTable::hash(uint32_t key) const
{
     // Defeat the "flickering" of 4.4 
     // const uint32_t A = 0x9E3779B9;
     // uint32_t h = key;
    // h = h * A;
    // h = (h >> 16) ^ h;
    // h = h * A;
    // h = (h >> 16) ^ h;
    
    return key % table_size; // Simple mod-based hash function
}

void ChainingHashTable::insert(uint32_t key)
{
    size_t index = hash(key);
    table[index].push_back(key);
    largest_list_size = std::max(largest_list_size, table[index].size());
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

size_t ChainingHashTable::getLargestListSize() const
{
    return largest_list_size;
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

void ChainingHashTable::recordLargestListSizeData(const std::vector<uint32_t>& keys, const std::vector<uint64_t>& test_sizes, const std::string& filename)
{
    std::ofstream outfileChainingSize(filename);
    
    if (!outfileChainingSize.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    
    outfileChainingSize << "n,LargestListSize\n";  
    
    for (size_t table_size : test_sizes) {
        ChainingHashTable table(table_size);  
        
        for (size_t i = 0; i < table_size; ++i) {
            uint32_t key = keys[i % keys.size()];  
            table.insert(key);
            outfileChainingSize << (i + 1) << "," << table.getLargestListSize() << "\n"; 
        }
    }
    
    outfileChainingSize.close();
}




