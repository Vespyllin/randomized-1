#ifndef BENCHMARKS_H
#define BENCHMARKS_H

#include "../perfect/perfect_hashing.h"
#include "../chaining/chaining_hashing.h"
#include "../red_black/red_black_tree.h"

// Function to benchmark hash tables and trees
std::vector<int64_t> benchmarkPerfectHashTable(PerfectHashTable &table, const std::vector<uint32_t> &keys);
std::vector<int64_t> benchmarkChainingHashTable(ChainingHashTable &table, const std::vector<uint32_t> &keys);
std::vector<int64_t> benchmarkRedBlackTree(RedBlackTree &rbTree, const std::vector<uint32_t> &keys);

#endif // BENCHMARKS_H
