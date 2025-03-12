
#include <vector>
#include <string>
#include <iostream>
#include <chrono>

// #include "chaining_hashing.h"
#include "../perfect/perfect_hashing.h"
#include "../red_black/red_black_tree.h"
#include "../benchmarks/benchmarks.h"

// Template function to benchmark any hash table or tree
template <typename HashTable>
std::vector<int64_t> benchmarkHashTable(HashTable &table, const std::vector<uint32_t> &keys)
{
    // Measure Insertion Time
    int retries = 0;
    auto start = std::chrono::high_resolution_clock::now();
    if constexpr (std::is_same<HashTable, PerfectHashTable>::value)
    {
        retries = table.insert(keys);
    }
    else
    {
        for (uint32_t key : keys)
        {
            table.insert(key);
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    // Measure Query/Search Time
    start = std::chrono::high_resolution_clock::now();
    for (int key : keys)
    {
        table.search(key);
    }
    stop = std::chrono::high_resolution_clock::now();

    auto query_time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    // // // If it's a chaining hash table, output max chain size
    // // if constexpr (std::is_same<HashTable, ChainingHashTable>::value)
    // // {
    // //     std::cout << "\tMax Chain Size: " << table.getMaxChainSize() << "\n";
    // // }

    return {static_cast<int64_t>(keys.size()), insert_time, query_time, retries};
}