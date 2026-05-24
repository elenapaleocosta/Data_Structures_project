#include "../include/SearchEngine.h"
#include "../include/AVLTree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    AVLTree* tree = new AVLTree();
    bool exit = true;
    while (exit) {
        cout<<"        AVL TREE - BASIC OPERATIONS      "<<endl;
        cout<<"========================================="<<endl;
        cout<<"  1. Insert new string"<<endl;
        cout<<"  2. Delete string"<<endl;
        cout<<"  3. Smart search (string optimized)"<<endl;
        cout<<"  4. Search with prefix"<<endl;
        cout<<"  5. Display and Validate"<<endl;
        cout<<"  0. Exit"<<endl;
        cout<<"========================================="<<endl;
        int choice;
        cout<<"-> Please choose an option from the menu above: "<<endl;
        cin>>choice;
        cin.ignore();
        string input_string;
        switch (choice) {
            case 1: {
                cout<<"-> Please type the string you want to insert: "<<endl;
                getline(cin,input_string);
                tree->insert(input_string);
                break;
            };
            case 2: {
                cout<<"-> Please type the string you want to delete: "<<endl;
                getline(cin,input_string);
                tree->remove(input_string);
                break;
            };
            case 3: {
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
                tree->display();

                cout<<"\n=== AVL Structural Validation ===\n";

                if (tree->isBalanced()) {
                    cout << "Tree height properties are perfectly balanced (diff<= 1). \n";
                } else {
                    cout << "error: Tree is Not balanced!\n";
                }

                //Ελεγχος balance factor

                if (tree->verifyBF()){
                    cout << "All stored Balance Factors and mathematically verified.\n";
                } else {
                    cout << "error: Discrepancy found is Balance Factors.\n";
                }
                cout << "=========================\n\n";
                break;
            }

            case 0: {
                exit = false;
                cout<<"-> Programm Terminated."<<endl;
                break;
            };
        };
    };
    delete tree;
    return 0;
}