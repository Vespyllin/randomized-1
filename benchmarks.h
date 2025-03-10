#ifndef BENCHMARKS_H
#define BENCHMARKS_H

#include <vector>
#include <string>
#include "chaining_hashing.h"
#include "perfect_hashing.h"
#include "red_black_tree.h"

// Function to benchmark hash tables and trees
template <typename HashTable>
void benchmarkHashTable(const std::string& name, HashTable& table, const std::vector<int>& keys);

#endif // BENCHMARKS_H
