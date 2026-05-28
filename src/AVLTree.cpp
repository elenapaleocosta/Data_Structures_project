#include "../include/AVLNode.h"
#include "../include/AVLTree.h"
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

// Κατασκευαστής
AVLTree::AVLTree() : root(nullptr) {}

// Καταστροφέας
AVLTree::~AVLTree() {
    clear(root);
};

void AVLTree::clear(AVLNode* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

AVLNode* AVLTree::getRoot() const {
    return root;
}

// Εκτυπώνει το δέντρο πλαγιαστά
void AVLTree::printInorder(AVLNode* node, int indent) const {
    if (node == nullptr) return;

    // Πρώτα το δεξί υποδέντρο
    printInorder(node->right, indent + 4);

    for (int i = 0; i < indent; i++) cout << " ";
    cout << node->key << " (bf: " << node->bf << ")\n";

    // Αριστερό υποδέντρο
    printInorder(node->left, indent + 4);
}

void AVLTree::display() const {
    if (root == nullptr) {
        cout << " The tree is empty. \n";
    } else {
        cout << "=== Tree Structure ===\n";
        // Αρχίζει από indent = 0 
        printInorder(root, 0);
    }
}

// Συνάρτηση εισαγωγής στο δέντρο
void AVLTree::insert(const string& key) {
    bool heightIncreased = false; // Flag: Δείχνει αν το δέντρο ψήλωσε
    root = insertHelper(root, key, heightIncreased); // Ξεκινάμε την αναδρομική εισαγωγή από τη ρίζα
}

AVLNode* AVLTree::insertHelper(AVLNode* node, const string& key, bool& heightIncreased) {
    if (node == nullptr) {
        heightIncreased = true; // Νέο φύλλο αυξάνει το ύψος του κλαδιού κατά 1 επίπεδο
        cout<<"-> The insertion was completed successfully."<<endl;
        return new AVLNode(key); // Δημιουργία κόμβου με bf = 0, left = nullptr, right = nullptr
    }

    if (key < node->key) { // Αν η λέξη είναι λεξικογραφικά μικρότερη → αριστερό υποδέντρο
        node->left = insertHelper(node->left, key, heightIncreased);

        if (heightIncreased) {
            node->bf += 1;

            /* Έλεγχος balance μετά την αλλαγή
            Περιπτώσεις:
            bf == 0: Ισορροπία μετά από προηγούμενη ανισορροπία
            bf == 1: Γέρνει προς τα αριστερά
            bf == 2: Αριστερή ανισορροπία */
            if (node->bf == 0) {
                heightIncreased = false; // Το ύψος δεν αλλάζει
            } else if (node->bf == 1) {
                heightIncreased = true;
            } else { // node->bf == 2
                if (node->left->bf >= 0) {
                    node = rotateRight(node);
                } else {
                    node->left = rotateLeft(node->left);
                    node = rotateRight(node);
                }
                heightIncreased = false;
            }
        }
    } else if (key > node->key) { // Αν η λέξη είναι λεξικογραφικά μεγαλύτερη → δεξί υποδέντρο
        node->right = insertHelper(node->right, key, heightIncreased);

        if (heightIncreased) {
            node->bf -= 1;

            /* Έλεγχος balance μετά την αλλαγή
            Περιπτώσεις:
            bf == 0: Ισορροπία
            bf == -1: Γέρνει προς τα δεξιά
            bf == -2: Δεξιά ανισορροπία */
            if (node->bf == 0) {
                heightIncreased = false;
            } else if (node->bf == -1) {
                heightIncreased = true;
            } else {
                if (node->right->bf <= 0) {
                    node = rotateLeft(node);
                } else {
                    node->right = rotateRight(node->right);
                    node = rotateLeft(node);
                }
                heightIncreased = false;
            }
        }
    } else {
        // Η λέξη υπάρχει ήδη
        heightIncreased = false; // Το ύψος δεν αλλάζει
        cout<<"-> The insertion was unsuccessful. The given string already exists."<<endl;
        return node;
    }
    
    return node;
}

AVLNode* AVLTree::rotateRight(AVLNode* parent) {
    AVLNode* leftChild = parent->left;

    // Μετακίνηση pointers
    parent->left = leftChild->right;
    leftChild->right = parent;

    // Ενημέρωση balance factors
    int p_bf = parent->bf;
    int l_bf = leftChild->bf;

    parent->bf = p_bf - 1 - max(0, l_bf);
    leftChild->bf = l_bf - 1 + min(0, parent->bf);

    return leftChild; // Επιστροφή νέας ρίζας υποδέντρου
}

AVLNode* AVLTree::rotateLeft(AVLNode* parent) {
    AVLNode* rightChild = parent->right;

    parent->right = rightChild->left;
    rightChild->left = parent;

    int p_bf = parent->bf;
    int r_bf = rightChild->bf;

    parent->bf = p_bf + 1 - min(0, r_bf);
    rightChild->bf = r_bf + 1 + max(0, parent->bf);

    return rightChild;
}

// Σημείωση: οι συναρτήσεις περιστροφής αλλάζουν τη δομή
// του υποδέντρου και ενημερώνουν τους παράγοντες ισορροπίας.

AVLNode* AVLTree::removeHelper(AVLNode* node, const string& key, bool& heightDecreased, bool showMessage) {
    if (node == nullptr) {
        heightDecreased = false;
        if (showMessage) {
            cout<<"-> The string: "<<key<<" couldn't be found."<<endl;
        }
        return nullptr;
    }

    if (key < node->key) {
        node->left = removeHelper(node->left, key, heightDecreased, showMessage);

        if (heightDecreased) {
            node->bf -= 1;

            if (node->bf == -1) {
                heightDecreased = false;
            } else if (node->bf == 0) {
                heightDecreased = true;
            } else {
                if (node->right->bf <= 0) {
                    node = rotateLeft(node);
                    heightDecreased = (node->bf == 0);
                } else {
                    node->right = rotateRight(node->right);
                    node = rotateLeft(node);
                    heightDecreased = true;
                }
            }
        }
    } else if (key > node->key) {
        node->right = removeHelper(node->right, key, heightDecreased, showMessage);

        if (heightDecreased) {
            node->bf += 1;

            if (node->bf == 1) {
                heightDecreased = false;
            } else if (node->bf == 0) {
                heightDecreased = true;
            } else {
                if (node->left->bf >= 0) {
                    node = rotateRight(node);
                    heightDecreased = (node->bf == 0);
                } else {
                    node->left = rotateLeft(node->left);
                    node = rotateRight(node);
                    heightDecreased = true;
                }
            }
        }
    } else {
        if (node->left == nullptr || node->right == nullptr) {

            // Περίπτωση κόμβου με 0 ή 1 παιδί: απλή αντικατάσταση/διαγραφή
            AVLNode* temp = node->left ? node->left : node->right;

            if (temp == nullptr) {
                // Κόμβος χωρίς παιδιά
                delete node;
                heightDecreased = true;
                if (showMessage) {
                    cout << "-> Deletion of: " << key << " was succesful." << endl;
                }
                return nullptr;
            }

            // Αντικατάσταση με μοναδικό παιδί (μεταφορά του δείκτη)
            AVLNode* temp2 = node;
            node = temp;
            delete temp2;
            heightDecreased = true;

        } else {
            // Περίπτωση κόμβου με 2 παιδιά: βρίσκουμε τον ελάχιστο του δεξιού υποδέντρου
            AVLNode* temp = findMin(node->right);

            node->key = temp->key;
            node->right = removeHelper(node->right, temp->key, heightDecreased, false);

            if (heightDecreased) {
                node->bf += 1;

                if (node->bf == 1) {
                    heightDecreased = false;
                } else if (node->bf == 0) {
                    heightDecreased = true;
                } else {
                    if (node->left->bf >= 0) {
                        node = rotateRight(node);
                        heightDecreased = (node->bf == 0);
                    } else {
                        node->left = rotateLeft(node->left);
                        node = rotateRight(node);
                        heightDecreased = true;
                    }
                }
            }
        }
        if (showMessage) {
            cout << "-> Deletion of: " << key << " was succesful." << endl;
        }
    }

    return node;
}

AVLNode* AVLTree::findMin(AVLNode* node) const {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void AVLTree::remove(const string& key) {
    if (root == nullptr) {
        cout << "-> The tree is empty."<<endl;
        return;
    }

    bool heightDecreased = false;
    root = removeHelper(root, key, heightDecreased, true);
}

// Έλεγχοι δέντρου
int AVLTree::getHeightHelper(AVLNode* node) const{
    if (node == nullptr) return 0;
    return 1 + max(getHeightHelper(node->left) , getHeightHelper(node->right));
}

//Έλεγχος διαφοράς ύψους να ειναι παντου <=1
bool AVLTree::isBalancedHelper(AVLNode* node) const {
    if (node == nullptr) return true;

    int leftHeight = getHeightHelper(node->left);
    int rightHeight = getHeightHelper(node->right);

if (abs(leftHeight - rightHeight)>1) {
    return false;
}

return isBalancedHelper(node->left) && isBalancedHelper(node->right);

}

bool AVLTree::isBalanced() const {
    return isBalancedHelper(root);
}


bool AVLTree::verifyBFHelper(AVLNode* node) const {
    if (node == nullptr){
        return true;
    }

    int leftHeight = getHeightHelper(node->left);
    int rightHeight = getHeightHelper(node->right);
    int BF = leftHeight - rightHeight;

    if (node->bf != BF) {
        return false;
    }

    return verifyBFHelper(node->left) && verifyBFHelper(node->right);
}

bool AVLTree::verifyBF() const {
    return verifyBFHelper(root);
}

void AVLTree::fixTree() {
    root = fixHelper(root);
}

AVLNode* AVLTree::fixHelper(AVLNode* node) {
    if (node==nullptr) {return nullptr;};
    node->left = fixHelper(node->left);
    node->right = fixHelper(node->right);
    int leftHeight = getHeightHelper(node->left);
    int rightHeight = getHeightHelper(node->right);
    int real_bf = leftHeight - rightHeight;
    if (real_bf == 2) { // Αριστερή ανισορροπία
        int left_child_bf = getHeightHelper(node->left->left) - getHeightHelper(node->left->right);
        
        if (left_child_bf >= 0) {
            // Περίπτωση Left-Left (Μονή δεξιά περιστροφή)
            node = rotateRight(node);
        } else {
            // Περίπτωση Left-Right (Διπλή περιστροφή)
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
    } 
    else if (real_bf == -2) { // Δεξιά ανισορροπία
        int right_child_bf = getHeightHelper(node->right->left) - getHeightHelper(node->right->right);
        
        if (right_child_bf <= 0) {
            // Περίπτωση Right-Right (Μονή αριστερή περιστροφή)
            node = rotateLeft(node);
        } else {
            // Περίπτωση Right-Left (Διπλή περιστροφή)
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
    }
    // Ξαναμετράμε τα ύψη γιατί η δομή μπορεί να άλλαξε λόγω των rotate
    leftHeight = getHeightHelper(node->left);
    rightHeight = getHeightHelper(node->right);
    node->bf = leftHeight - rightHeight;
    return node;
}

void AVLTree::wrong_input() {
    cout<<"-> Please insert the right input to continue."<<endl;
}