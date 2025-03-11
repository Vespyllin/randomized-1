#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <random>
#include <cmath>
#include "chaining_hashing.h"
#include "perfect_hashing.h"
#include "red_black_tree.h"
#include "benchmarks.h"

using namespace std;

// Function to compute the next power of 2
int64_t nextPowerOf2(int64_t num) {
    if (num <= 0) return 1;
    int64_t power = 1;
    while (power < num) {
        power *= 2;
    }
    return power;
}

// Function to generate distinct keys {i²} (no mod operation)
vector<int64_t> generateKeys(int n) {
    set<int64_t> unique_keys;
    for (int i = 0; i < n; i++) {
        unique_keys.insert(static_cast<int64_t>(i) * i);
    }
    return vector<int64_t>(unique_keys.begin(), unique_keys.end());  // Store only distinct keys
}

// Function to shuffle keys before insertion
void shuffleKeys(vector<int64_t>& keys) {
    random_device rd;
    mt19937 g(rd());  // Mersenne Twister for randomness
    shuffle(keys.begin(), keys.end(), g);
}

int main() {
    vector<int> test_sizes = {32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};

    for (int n : test_sizes) {
        cout << "\nRunning benchmarks for n = " << n << "...\n";

        // Generate and shuffle distinct keys
        vector<int64_t> keys = generateKeys(n);
        shuffleKeys(keys);

        // Compute the actual number of distinct keys (m)
        int64_t m = keys.size();
        m = nextPowerOf2(m);  // Round up to the next power of 2 if needed

        cout << "   Distinct Keys: " << keys.size() << ", Using m = " << m << "\n";

        // Initialize Data Structures with m instead of n
        ChainingHashTable chainingTable(m);
        PerfectHashTable perfectTable(keys);
        RedBlackTree rbTree;

        // Run Benchmarks
        benchmarkHashTable("Chaining Hashing", chainingTable, keys);
        benchmarkHashTable("Perfect Hashing", perfectTable, keys);
        benchmarkHashTable("Red-Black Tree", rbTree, keys);
        
        // Output max chain size for chaining hashing
        cout << "Max Chain Size (Chaining Hashing): " << chainingTable.getMaxChainSize() << "\n";
    }

    return 0;
}
