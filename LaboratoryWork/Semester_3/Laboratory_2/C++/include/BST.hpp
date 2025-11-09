#pragma once
#include <iostream>
#include <cmath>

using namespace std;

struct BSTNode {
    int val;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int val_);
    BSTNode();
};

class BST {
public:
    BSTNode* root;

    BST();
    
    BSTNode* insert(BSTNode* root, int val);
    int checkBalance(BSTNode* root, bool& isBalanced);
};