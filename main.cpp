#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// #include "chaining_hashing.h"
#include "perfect/perfect_hashing.h"
#include "red_black/red_black_tree.h"
#include "benchmarks/benchmarks.h"

// Function to generate structured keys {i² mod n}
std::vector<uint32_t> generateKeys(uint32_t n)
{
    std::vector<uint32_t> keys;
    for (uint32_t i = 0; i < n; i++)
    {
        keys.push_back((i * i) % n);
    }
    return keys;
}

// Function to shuffle keys before insertion
void shuffleKeys(std::vector<uint32_t> &keys)
{
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(keys.begin(), keys.end(), g);
}

int main()
{
    std::vector<uint32_t> test_sizes = {65536};

    for (uint32_t n : test_sizes)
    {
        std::cout << "Running benchmarks for n = " << n << "...\n";

        // Generate and shuffle keys
        std::vector<uint32_t> keys = generateKeys(n);
        shuffleKeys(keys);

        // Initialize Data Structures
        // ChainingHashTable chainingTable(n);
        PerfectHashTable perfectTable(n);
        // RedBlackTree rbTree;

        // Run Benchmarks
        // benchmarkHashTable("Chaining Hashing", chainingTable, keys);
        benchmarkHashTable("Perfect Hashing", perfectTable, keys);
        // benchmarkHashTable("Red-Black Tree", rbTree, keys);

        // Output max chain size for chaining hashing
        // std::cout << "Max Chain Size (Chaining Hashing): " << chainingTable.getMaxChainSize() << "\n";
    }

    return 0;
}
