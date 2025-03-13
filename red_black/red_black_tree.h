#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <set>
#include <stdint.h> //defines uint32_t as unsigned 64-bit integer.

class RedBlackTree
{
private:
    std::set<uint32_t> tree; // Uses C++ STL set (Red-Black Tree)

public:
    // Inserts a key into the Red-Black Tree
    void insert(uint32_t key);

    // Searches for a key in the Red-Black Tree
    bool search(uint32_t key);
};

#endif // RED_BLACK_TREE_H
