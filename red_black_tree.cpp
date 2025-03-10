#include "red_black_tree.h"

// Inserts a key into the Red-Black Tree
void RedBlackTree::insert(int key) {
    tree.insert(key);
}

// Searches for a key in the Red-Black Tree
bool RedBlackTree::search(int key) {
    return tree.find(key) != tree.end();
}
