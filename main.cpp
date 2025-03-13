#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include <fstream>
#include <cstdint>

#include "chaining/chaining_hashing.h"
#include "perfect/perfect_hashing.h"
#include "red_black/red_black_tree.h"
#include "benchmarks/benchmarks.h"

// Function to generate structured keys {i² mod n}
std::vector<uint32_t> generateKeys(uint32_t n)
{
    std::set<uint32_t> keys;
    for (uint32_t i = 0; i < n; i++)
    {
        keys.insert((i * i) % n);
    }

    // Return vector of unique keys
    std::vector<uint32_t> keyVector(keys.begin(), keys.end());
    return keyVector;
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
    std::vector<uint32_t> test_sizes = {32000, 65536};

    std::vector<std::vector<int64_t>> results;
    std::ofstream outfile("perfect.csv");
    if (!outfile.is_open())
    {
        std::cerr << "Failed to open file for writing.\n";
        return 0;
    }

    for (uint32_t n : test_sizes)
    {
        std::cout << "Running benchmarks for attempted n = " << n << "...\n";

        for (size_t i = 0; i < 100; i++)
        {
            // Generate and shuffle keys
            std::vector<uint32_t> keys = generateKeys(n);
            shuffleKeys(keys);
            keys.shrink_to_fit();

            // Uncomment the following to benchmark Hashing with chaining:

            //ChainingHashTable chainingTable(n);
            // Benchmark the ChainingHashTable
            // auto x = benchmarkHashTable(chainingTable, keys);
            // results.push_back(x);
            
            PerfectHashTable perfectTable(keys.size());
            auto x = benchmarkHashTable(perfectTable, keys);
            results.push_back(x);
        }
    }

    std::cout << "Writing data...\n";
    outfile
        << "n" << ","
        << "insertion" << ","
        << "query" << ","
        << "retries" << "\n";

    for (auto result : results)
    {
        outfile
            << result[0] << ","
            << result[1] << ","
            << result[2] << ","
            << result[3] << "\n";
    }

    outfile.close();
    return 0;
}
