#include "AVLTree.h"
#include <iostream>

using namespace std;

int main() {
    AVLTree tree;
    tree.insert ("banana");
    tree.insert ("lol");
    tree.insert ("coffee");
    tree.insert ("hello");

    tree.display();

    return 0;
}