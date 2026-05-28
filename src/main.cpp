#include "../include/AVLTree.h"
#include "../include/SearchEngine.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // Δημιουργία AVL δέντρου
    AVLTree* tree = new AVLTree();
    // Σημαία βρόχου μενού
    bool exit = true;
    while (exit) {
        // Εμφάνιση κύριου μενού επιλογών
        cout<<"        AVL TREE - BASIC OPERATIONS      "<<endl;
        cout<<"========================================="<<endl;
        cout<<"  1. Insert new string"<<endl;
        cout<<"  2. Delete string"<<endl;
        cout<<"  3. Smart search (string optimized)"<<endl;
        cout<<"  4. Search with prefix"<<endl;
        cout<<"  5. Display and Validate"<<endl;
        cout<<"  0. Exit"<<endl;
        cout<<"========================================="<<endl;
        cout<<"-> Please choose an option from the menu above: "<<endl;
        int choice;
        cin>>choice;
        while (choice < 0 || choice > 5) {
            tree->wrong_input();
            cin>>choice;
        };
        cin.ignore();
        string input_string;
        // Επεξεργασία επιλογής χρήστη
        switch (choice) {
            case 1: {
                // Εισαγωγή νέας συμβολοσειράς στο δέντρο
                cout<<"-> Please type the string you want to insert: "<<endl;
                getline(cin,input_string);
                tree->insert(input_string);
                break;
            };
            case 2: {
                // Διαγραφή συμβολοσειράς
                cout<<"-> Please type the string you want to delete: "<<endl;
                getline(cin,input_string);
                tree->remove(input_string);
                break;
            };
            case 3: {
                // Έξυπνη αναζήτηση (βασισμένη σε κοινό πρόθεμα)
                cout<<"-> Please type the string you want to search: "<<endl;
                getline(cin,input_string);
                AVLNode* result = optimizedSearch(tree->getRoot(),input_string,0); 
                if (result == nullptr) {
                    cout<<"-> The string: "<<input_string<<" couldn't be found."<<endl;
                } else {
                    cout<<"-> The string: "<<input_string<<" was found."<<endl;
                };
                break;
            };
            case 4: {
                // Αναζήτηση λέξεων με δοθέν πρόθεμα
                cout<<"-> Please type the prefix you want to find words related to it: "<<endl;
                getline(cin,input_string);
                AVLNode* prefixRoot = findPrefixRoot(tree->getRoot(), input_string);
                if (prefixRoot == nullptr) {
                    cout<<"-> No words were found with prefix: "<<input_string<<". Search was unsuccesful."<<endl;
                } else {
                    vector<string> matches;
                    collectPrefixMatches(prefixRoot,input_string,matches);
                    int size = matches.size();
                    if (size==0) {
                        cout<<"-> No words were found with prefix: "<<input_string<<endl;
                    } else {
                        cout<<"-> Found: "<<size<<" match(es) with prefix: "<<input_string<<endl;
                        int i = 0;
                        while (i<size) {
                            cout<<i+1<<". "<<matches[i]<<endl;
                            i ++;
                        };
                    };
                };
                break;
            };
            case 5: {
                // Εμφάνιση δομής και έλεγχοι ισορροπίας
                tree->display();
                if (tree->isBalanced()) {cout<<"-> The tree is perfectly balanced."<<endl;}
                else {
                    cout<<"-> The tree is not balanced. Would you like to rebalance it? [yes/no]"<<endl;
                    string rebal_ans;
                    cin>>rebal_ans;
                    while (rebal_ans!="yes" && rebal_ans!="no") {
                        tree->wrong_input();
                        cin>>rebal_ans;
                    };
                    cin.ignore();
                    if (rebal_ans == "yes") {
                        // Διόρθωση/επανισορρόπηση δέντρου
                        tree->fixTree();
                        cout<<"-> Tree was rebalanced succesfully."<<endl;
                        cout<<"-> New rebalanced version of the Tree Structure shown below:"<<endl;
                        tree->display();
                    } 
                    else {
                        cout<<"Rebalancing canceled by user."<<endl;
                    };
                };
                break;
            };
            case 0: {
                // Έξοδος προγράμματος
                exit = false;
                cout<<"-> Programm Terminated."<<endl;
                break;
            };
        };
    };
    delete tree;
    return 0;
}