#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "chaining_hashing.h"
#include "perfect_hashing.h"
#include "red_black_tree.h"
#include "benchmarks.h"

using namespace std;

// Function to generate structured keys {i² mod n}
vector<int> generateKeys(int n) {
    vector<int> keys;
    for (int i = 0; i < n; i++) {
        keys.push_back((i * i) % n);
    }
    return keys;
}

// Function to shuffle keys before insertion
void shuffleKeys(vector<int>& keys) {
    random_device rd;
    mt19937 g(rd());  // Mersenne Twister for randomness
    shuffle(keys.begin(), keys.end(), g);
}

int main() {
    vector<int> test_sizes = {32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};

    for (int n : test_sizes) {
        cout << "\nRunning benchmarks for n = " << n << "...\n";

        // Generate and shuffle keys
        vector<int> keys = generateKeys(n);
        shuffleKeys(keys);

        // Initialize Data Structures
        ChainingHashTable chainingTable(n);
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
