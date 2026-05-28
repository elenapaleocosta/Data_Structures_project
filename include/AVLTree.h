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

        // Δεξιά/αριστερή περιστροφή για επανισορρόπηση υποδέντρων
        AVLNode* rotateRight(AVLNode* parent);
        AVLNode* rotateLeft(AVLNode* parent);

        // insertHelper: εισαγωγή με ενημέρωση παράγοντα ύψους
        // heightIn: γίνεται true αν το ύψος του υποδέντρου αυξήθηκε
        AVLNode* insertHelper(AVLNode* node, const string& key, bool& heightIn);
    
        // removeHelper: διαγραφή με ενημέρωση παράγοντα ύψους
        // heightDe: γίνεται true αν το ύψος του υποδέντρου μειώθηκε
        // showMessage: αν πρέπει να εμφανιστεί μήνυμα επιτυχίας/άρνησης
        AVLNode* removeHelper(AVLNode* node, const string& key, bool& heightDe, bool showMessage);

        //Απελευθέρωση μνήμης όλων των κόμβων
        void clear(AVLNode* node);
        
        //εκτύπωση δεντρου στην κονσόλα
        void printInorder(AVLNode* node, int indent) const;

        int getHeightHelper(AVLNode* node) const;
        bool isBalancedHelper(AVLNode* node) const;
        bool verifyBFHelper(AVLNode* node) const;
        AVLNode* fixHelper(AVLNode* node);
    
    public:
        AVLTree(); // Κατασκευαστής
        ~AVLTree(); // Καταστροφέας
        
        AVLNode* getRoot() const;

        //εισαγωγή νέας συμβολοσειράς στο δέντρο
        void insert(const string& key);
        //διαγραφή συμβολοσειράς απο το δέντρο
        void remove(const string& key);

        //εκτύπωση δέντρου
        void display() const; 

        bool isBalanced() const;
        bool verifyBF() const;
        void fixTree();
        void wrong_input();
};

#endif //AVL_TREE_H