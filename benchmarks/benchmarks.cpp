
#include <vector>
#include <string>
#include <iostream>
#include <chrono>

#include "benchmarks.h"

std::vector<int64_t> benchmarkPerfectHashTable(PerfectHashTable &table, const std::vector<uint32_t> &keys)
{
    // Measure Insertion Time
    auto start = std::chrono::high_resolution_clock::now();
    table.insert(keys);

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

    return {static_cast<int64_t>(keys.size()), insert_time, query_time};
}

std::vector<int64_t> benchmarkChainingHashTable(ChainingHashTable &table, const std::vector<uint32_t> &keys)
{
    // Measure Insertion Time
    auto start = std::chrono::high_resolution_clock::now();
    for (uint32_t key : keys)
    {
        table.insert(key);
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

    return {static_cast<int64_t>(keys.size()), insert_time, query_time};
}

std::vector<int64_t> benchmarkRedBlackTree(RedBlackTree &rbTree, const std::vector<uint32_t> &keys)
{
    // Measure Insertion Time
    auto start = std::chrono::high_resolution_clock::now();
    for (uint32_t key : keys)
    {
        rbTree.insert(key);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    // Measure Query/Search Time
    start = std::chrono::high_resolution_clock::now();
    for (int key : keys)
    {
        rbTree.search(key);
    }
    stop = std::chrono::high_resolution_clock::now();

    auto query_time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    return {static_cast<int64_t>(keys.size()), insert_time, query_time};
}