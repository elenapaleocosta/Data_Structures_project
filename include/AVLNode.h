#ifndef AVL_NODE_H
#define AVL_NODE_H

#include <string>

using namespace std;

// Δομή κόμβου για το AVL δέντρο
struct AVLNode {
    string key; // κλειδί (συμβολοσειρά)
    AVLNode* left; // δείκτης αριστερού παιδιού
    AVLNode* right; // δείκτης δεξιού παιδιού
    int bf; // παράγοντας ισορροπίας: ύψος(αριστερό) - ύψος(δεξί)

    // Κατασκευαστής: αρχικοποιεί το κλειδί και τους δείκτες
    AVLNode(const string& str) : key(str), left(nullptr), right(nullptr), bf(0) {}
};

#endif // AVL_NODE_H
