#ifndef AVL_NODE_H
#define AVL_NODE_H

#include <string>

using namespace std;

struct AVLNode {
    string key; //συμβολοσειρά προσ αποθήκευση
    AVLNode* left; //Δείκτης αριστερού παιδιού
    AVLNode* right; //Δείκτης δεξιού παιδιού
    int bf; //Balance Factor = height(left) - height(right)

    //Constructor αρχικοποίησης κόμβου
    AVLNode(const string& str) : key(str), left(nullptr), right(nullptr), bf(0) {}
};

#endif // AVL_NODE_H