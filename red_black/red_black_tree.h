#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <set>

class RedBlackTree {
private:
    std::set<int64_t> tree;  // Uses C++ STL set (Red-Black Tree) with 64-bit integers

public:
    // Inserts a key into the Red-Black Tree
    void insert(int64_t key);

    // Searches for a key in the Red-Black Tree
    bool search(int64_t key);
};

#endif // RED_BLACK_TREE_H
