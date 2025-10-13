#pragma once
#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    AVLNode* p;
    int height;

    AVLNode(int k);
};

struct AVLTree {
public:
    AVLNode* root;

    AVLTree() : root(nullptr) {}

    AVLNode* Find(AVLNode* root, int k);
    AVLNode* Push(AVLNode* root, int k);
    AVLNode* DelElm(AVLNode* root, int k);
    void DFS(AVLNode* root);
    void BFS(AVLNode* root);
    int GetSize(AVLNode* root);
    void GetElms(AVLNode* root, vector<string>& elements);
    void Destroy(AVLNode* root);

private:
    AVLNode* GetMinValueNode(AVLNode* node);
    int GetHeight(AVLNode* n);
    int GetBalance(AVLNode* n);
    AVLNode* RightRotate(AVLNode* y);
    AVLNode* LeftRotate(AVLNode* x);
};