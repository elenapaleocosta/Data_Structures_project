#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "AVLNode.h" //εισαγωγή δομής κόμβου (key, left, right, bf)
#include <string>
#include <iostream>
using namespace std;

class AVLTree{
    private:
    //ορισμός δείκτη ρίζας δέντρου 
    AVLNode* root;

    AVLNode* findMin(AVLNode* node) const;

    AVLNode* rotateRight(AVLNode* parent);
    AVLNode* rotateLeft(AVLNode* parent);

    //heightIn = ενημερώνει το δέντρο αν το υποδέντρο ψήλωσε 
    AVLNode* insertHelper(AVLNode* node, const string& key, bool& heightIn);
 
    //heightDe = ενημερώνει το δέντρο αν το υποδέντρο κόντυνε
    AVLNode* removeHelper(AVLNode* node, const string& key, bool& heightDe);

    //Απελευθέρωση μνήμης όλων των κόμβων
    void clear(AVLNode* node);
    
    //εκτύπωση δεντρου στην κονσόλα
    void printInorder(AVLNode* node, int indent) const;

    public:
    AVLTree(); //Constructor
    ~AVLTree(); //Destructor
    
    AVLNode* getRoot() const;

    //εισαγωγή νέας συμβολοσειράς στο δέντρο
    void insert(const string& key);
    //διαγραφή συμβολοσειράς απο το δέντρο
    void remove(const string& key);

    //εκτύπωση δέντρου
    void display() const; 
};

#endif //AVL_TREE_H