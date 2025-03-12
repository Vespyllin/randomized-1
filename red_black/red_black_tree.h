#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <set>

class RedBlackTree {
private:
    std::set<int> tree;  // Uses C++ STL set (Red-Black Tree)

public:
    // Inserts a key into the Red-Black Tree
    void insert(int key);

    // Searches for a key in the Red-Black Tree
    bool search(int key);
};

#endif // RED_BLACK_TREE_H
