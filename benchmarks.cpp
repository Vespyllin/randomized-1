#include "benchmarks.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Template function to benchmark any hash table or tree
template <typename HashTable>
void benchmarkHashTable(const string& name, HashTable& table, const vector<int>& keys) {
    cout << "Benchmarking: " << name << "\n";

    // Measure Insertion Time
    auto start = high_resolution_clock::now();
    for (int key : keys) {
        table.insert(key);
    }
    auto stop = high_resolution_clock::now();
    auto insert_time = duration_cast<microseconds>(stop - start).count();

    // Measure Query/Search Time
    start = high_resolution_clock::now();
    for (int key : keys) {
        table.search(key);
    }
    stop = high_resolution_clock::now();
    auto query_time = duration_cast<microseconds>(stop - start).count();

    // Output results
    cout << "   Insert Time: " << insert_time << " us\n";
    cout << "   Query Time: " << query_time << " us\n";
    cout << "   Total Time: " << (insert_time + query_time) << " us\n";

    // If it's a chaining hash table, output max chain size
    if constexpr (std::is_same<HashTable, ChainingHashTable>::value) {
        cout << "   Max Chain Size: " << table.getMaxChainSize() << "\n";
    }

    cout << "------------------------------------\n";
}
