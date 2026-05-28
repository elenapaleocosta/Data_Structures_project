#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H
#include "AVLNode.h"
#include <string>
#include <vector>

using namespace std;

// Συγκρίνει δύο συμβολοσειρές ξεκινώντας από το δείκτη matched_prefix_len
inline int compareFromIndex(const string& str1, const string& str2, int matched_prefix_len) {
    int len1 = str1.length();
    int len2 = str2.length();
    int i = matched_prefix_len;
    while (i<len1 && i<len2) {
        if (str1[i]!=str2[i]) {
            return str1[i] - str2[i];
        };  
        i++;
    };
    return (len1 - len2);
};

// Βελτιστοποιημένη δυαδική αναζήτηση χρησιμοποιώντας γνωστό κοινό πρόθεμα
inline AVLNode* optimizedSearch(AVLNode* node,const string& target,int matched_len) {
    if (node==nullptr) { 
        return nullptr;
    };
    int result = compareFromIndex(target,node->key,matched_len);
    if (result == 0) {
        return node;
    };
    int new_matched = matched_len;
    int target_len = target.length();
    int node_len = node->key.length();
    while (new_matched < target_len && new_matched < node_len && target[new_matched] == node->key[new_matched] ) {
        new_matched++;
    };
    if (result < 0) {
        return optimizedSearch(node->left, target, new_matched);
    }
    else {
        return optimizedSearch(node->right, target, new_matched);
    };
};

// Βρίσκει έναν κόμβο που ταιριάζει με το πρόθεμα (αν υπάρχει)
inline AVLNode* findPrefixRoot(AVLNode* node, const string& prefix) {
    if (node == nullptr) {return nullptr;};
    if (node->key.rfind(prefix,0) == 0) {return node;};
    if (prefix < node->key)  {
        return findPrefixRoot(node->left, prefix);
    }
    else {
        return findPrefixRoot(node->right, prefix);
    }
};

// Συλλέγει (in-order) όλα τα κλειδιά που ξεκινούν με το δοθέν πρόθεμα
inline void collectPrefixMatches(AVLNode* node, const string& prefix, vector<string>& results) {
    if (node == nullptr) return;
    if (prefix < node->key || node->key.rfind(prefix,0) == 0) {
        collectPrefixMatches(node->left,prefix,results);
    };
    if (node->key.rfind(prefix,0) == 0) {
        results.push_back(node->key);
    };
    if (prefix > node->key || node->key.rfind(prefix,0) == 0) {
        collectPrefixMatches(node->right,prefix,results);
    };
};

#endif      