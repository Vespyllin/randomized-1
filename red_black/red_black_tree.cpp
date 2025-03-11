#include "red_black_tree.h"
#include <cstdint>  

// Inserts a key into the Red-Black Tree
void RedBlackTree::insert(int64_t key) {
    tree.insert(key);
}

// Searches for a key in the Red-Black Tree
bool RedBlackTree::search(int64_t key) {
    return tree.find(key) != tree.end();
}
