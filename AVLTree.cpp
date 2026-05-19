#include "AVLTree.h"
#include <iostream>
#include <algorithm>
using namespace std; 

//Constructor
AVLTree::AVLTree() : root(nullptr){}

//Destructor 
AVLTree::~AVLTree() {
    clear(root);
}

void AVLTree::clear(AVLNode* node){
    if (node != nullptr) {
        clear (node->left);
        clear (node->right);
        delete node;
    }

}

AVLNode* AVLTree::getRoot() const {
    return root;
}

//Εκτυπώνει το δέντρο πλαγιαστά
void AVLTree::printInorder(AVLNode* node, int indent){ 
    if (node == nullptr) return;

    //Πρώτα το δεξί υποδέντρο
    printInorder(node->right, indent + 4);

    for (int i = 0; i < indent; i++) cout << " ";
    cout << node->key << " (bf: "<< node->bf << ")\n";

    //Αριστερο υποδέντρο
    printInorder(node->left , indent + 4);
 }

 void AVLTree::display() const {
    if (root == nullptr) {
        cout << "   Το δέντρο είναι άδειο. \n";
    } else {
        cout << " === Δομή Δέντρου ===\n";
        //Αρχίζει απο indent = 0 
        printInorder(root, 0);
    }

}

    //συναρτηση εισαγωγής στο δέντρο
    void AVLTree::insert(const string& key){
        bool heightIncreased = false; //flag: δείχνει αν το δεντρο ψήλωσε 
        root = insertHelper(root, key, heightIncreased); //ξεκιναμε την αναδρομική εισαγωγή από την ρίζα
    }

    AVLNode* AVLTree::insertHelper(AVLNode*, const string& key, bool& heightIncreased){
        if (node == nullptr) {
            heightIncreased = true;  //νεο φύλλο αυξανει το υψος του κλαδιου κατα 1 επιπεδο
            return new AVLNode(key); //Δημιουργία προσωρινής μνήμης με bf=0 left=nullptr, right=nullptr
        }

        if (key < node->key) { //αν η λεξη ειναι λεξοκογραφικά μικρότερη -> αριστερο φύλλο
            node-> left = insertHelper(node->left, key, heightIncreased);

                //έλεγχος εάν έγινε η εισαγωγή πιο κάτω και α΄θξησε το ύψος του αριστερού κλαδιού 
                if (heightIncreased){
                    node->bf +=1; 

                    //έλεγχος current κατάστασης μεταβλητης balance μετα τισ αλλαγές
                    /*περιπτώσεις:
                    bf==0: ήταν πριν -1 με βαροσ στα δεξια΄και τώρα ισορροπησε
                    bf==1: ήταν ισορροπημένος και τώρα γέρνει προσ τα αριστερά
                    bf==2: το αριστερό κλαδί είναι δύο επιπεδα πιο κατω απτο αριστερό*/
                    if (node->bf == 0){
                        heightInscrease = false; //Το συνολικό ύψος δεν άλλαξε
                    } else if (node->bf == 1){
                        heightInscrease = true; //Το συνολικό ύψος αυξηθηκε -> ψήλωσε
                    } else if (node->bf == 2){ //ανισορροπια κόμβου
                        //αρχικοποιήση "αναζήτησης" για να δουμε απο ποια πλευρά χρειάζεται να το ισορροπήσουμε
                        if (node->left->bf >= 0){ //αν το παιδί έχει bf>=0 κανουμε μονό rotation δεξιά
                            node = rotateRight(node);
                        } else { //αν το παιδί εχει bf<0 κανουμε διπλό rotation αριστερη-δεξιά
                            node->left = rotateLeft(node->left); //περιστροφή στο παιδί
                            node = rotateRight(node); //περιστροφή στον πατέρα
                        }
                        
                        //πλέον το δέντρο ειναι ισορροπημένο και επανήλθε στο αρχικό του ύψος 
                        heightInscrease = false;
                    }
                }
            } else if (key > node->key){ //αν η λεξη ειναι λεξοκογραφικά μεγαλύτερη -> δεξί φύλλο
                node->right = inserHelper(node->right, key, heightIncreased);
            
                //ελεγχος εάν η εισαγωγή άλλαξε το ύψος του δέντρου
                if(heightIncreased) { //αφου ψήλωσε το δεξί κλαδί το bf μειώνεται κατα 1
                    node -> bf -=1
                    //έλεγχος current κατάστασης μεταβλητης balance μετα τισ αλλαγές
                    /*περιπτώσεις:
                    bf==0: ήταν πριν -1 με βαροσ στα δεξια΄και τώρα ισορροπησε
                    bf==1: ήταν ισορροπημένος και τώρα γέρνει προσ τα αριστερά
                    bf==2: το αριστερό κλαδί είναι δύο επιπεδα πιο κατω απτο αριστερό*/
                    if (node->bf == 0){
                        heightInscrease = false; //Το συνολικό ύψος δεν άλλαξε
                    } else if (node->bf == -1){
                        heightInscrease = true; //Το συνολικό ύψος άλλαξε
                    } else if (node->bf == -2){
                        if (node->right->bf <= 0){ //αν το δεξί παιδί έχει bf<=0 κανουμε μονό rotation αριστερα 
                            node = rotateLeft(node);
                        } else{ //αν το δεξί παιδί έχει bf>0 κανουμε διπλό rotation δεξια-αριστερή
                            node->right = rotateRight(node->right); // περιστροφή στο παιδί
                            node = rotateLeft(node); //περιστροφή στον πατέρα
                        }

                        //η περιστροφή ισορροπησε το ύψος άρα τελειώνει η διαδικασια διάδοσης
                        heightInscrease = false;
                    }
                   
                }
            } else { //3η περίπτωση: η λέξη υάρχει ήδη
                //δεν εισάγουμε τίποτα άρα το ύψος δεν άλλαξε
                heightIncreased = false;\
                return node; //επιστρέφουμε τον κόμβο όπως είναι
            }
            
        //επιστροφή ενημερωμένου δείκτη
        return node;
        }

    AVLNode* AVLTree::rotateRight(AVLNode* parent){
        AVLNode* leftChild = parent->left;

        //μετακίνηση pointers
        parent->left = leftChild->right;
        leftChild->right = parent;

        //ενημέρωση ύψους των Balance factors
        int p_bf = parent->bf;
        int l_bf = leftChild->bf;

        parent->bf = p_bf - 1 - max(0, l_bf);
        leftChild->bf = l_bf -1 +min(0, parent->bf);

        return leftChild; //Επιστρέφουμε την ρίζα του υποδέντρου
    }
    
    void AVLTree::remove(const string& key){}
