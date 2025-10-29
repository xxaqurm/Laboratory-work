#pragma once
#include <iostream>
#include <cmath>

using namespace std;

struct BSTNode {
    int val;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int val_) : val(val_), left(nullptr), right(nullptr) {};
    BSTNode() : left(nullptr), right(nullptr) {}
};

class BST {
public:
    BSTNode* root;

    BST() : root(nullptr) {}

    BSTNode* insert(BSTNode* root, int val) {
        if (!root)
            return new BSTNode(val);
        if (val < root->val)
            root->left = insert(root->left, val);
        else if (val > root->val)
            root->right = insert(root->right, val);
        return root;
    }

    int checkBalance(BSTNode* root, bool& isBalanced) {
        if (!root)
            return 0;
        
        int left_height = checkBalance(root->left, isBalanced);
        int right_height = checkBalance(root->right, isBalanced);

        if (abs(left_height - right_height) > 1)
            isBalanced = false;
        
        return max(left_height, right_height) + 1; 
    }
};