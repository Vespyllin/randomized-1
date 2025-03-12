#ifndef BENCHMARKS_H
#define BENCHMARKS_H

// Function to benchmark hash tables and trees
template <typename HashTable>
std::vector<int64_t> benchmarkHashTable(HashTable &table, const std::vector<uint32_t> &keys);

#include "benchmarks.tpp"

#endif // BENCHMARKS_H
