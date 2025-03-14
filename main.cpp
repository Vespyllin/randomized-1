#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include <fstream>
#include <cstdint>

#include "common/common.h"
#include "chaining/chaining_hashing.h"
#include "perfect/perfect_hashing.h"
#include "red_black/red_black_tree.h"
#include "benchmarks/benchmarks.h"

int main()
{
    std::ofstream outfilePerfect("results/perfect.csv", std::ios::app);
    std::ofstream outfileChaining("results/chaining.csv", std::ios::app);
    std::ofstream outfileRedBlackTree("results/redblacktree.csv", std::ios::app);

    if (!outfilePerfect.is_open() || !outfileChaining.is_open() || !outfileRedBlackTree.is_open())
    {
        std::cerr << "Failed to open file one of the CSV files.\n";
        return 0;
    }

    outfilePerfect
        << "n" << ","
        << "insertion" << ","
        << "query" << "\n";

    outfileChaining
        << "n" << ","
        << "insertion" << ","
        << "query" << "\n";

    outfileRedBlackTree
        << "n" << ","
        << "insertion" << ","
        << "query" << "\n";

    std::vector<uint64_t> test_sizes = {
        32, 64, 128, 256, 512, 1024,
        2048, 4096, 8192, 16384, 32768,
        65536, 131072, 262144, 524288,
        1048576, 2097152, 4194304,
        8388608, 16777216,
        33554432, 67108864};

    uint64_t iterations = 100;

    for (uint32_t test_size : test_sizes)
    {
        std::cout << "Running benchmarks for attempted n = " << test_size << "...\n";

        for (size_t i = 0; i < iterations; i++)
        {
            std::cout << "    " << "Iteration " << i + 1 << ":\n";

            std::cout << "\tGenerating random keys.\n";
            std::vector<uint32_t> keys = generateKeys(test_size);
            shuffleKeys(keys);
            keys.shrink_to_fit();

            auto n = keys.size();

            PerfectHashTable perfectTable(n);
            ChainingHashTable chainingTable(n);
            RedBlackTree rbTree = RedBlackTree();

            std::cout << "\tTesting perfect hash table.\n";
            auto perfectResult = benchmarkPerfectHashTable(perfectTable, keys);

            std::cout << "\tTesting chaining hash table.\n";
            auto chainingResult = benchmarkChainingHashTable(chainingTable, keys);

            std::cout << "\tTesting red black tree.\n";
            auto redBlackResult = benchmarkRedBlackTree(rbTree, keys);

            outfilePerfect
                << perfectResult[0] << ","
                << perfectResult[1] << ","
                << perfectResult[2] << std::endl;

            outfileChaining
                << chainingResult[0] << ","
                << chainingResult[1] << ","
                << chainingResult[2] << std::endl;

            outfileRedBlackTree
                << redBlackResult[0] << ","
                << redBlackResult[1] << ","
                << redBlackResult[2] << std::endl;
        }
    }

    std::cout << "---------------------------------" << std::endl;

    outfilePerfect.close();
    outfileChaining.close();
    outfileRedBlackTree.close();
    return 0;
}
