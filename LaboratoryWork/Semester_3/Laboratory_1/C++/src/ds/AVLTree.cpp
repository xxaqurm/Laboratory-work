#include "AVLTree.hpp"
using namespace std;

AVLNode::AVLNode(int k) {
    key = k;
    left = nullptr;
    right = nullptr;
    p = nullptr;
    height = 1;
}

AVLNode* AVLTree::Find(AVLNode* root, int k) {
    if (!root) return nullptr;

    if (k == root->key) return root;
    else if (k < root->key) return Find(root->left, k);
    else return Find(root->right, k);
}

AVLNode* AVLTree::Push(AVLNode* root, int k) {
    if (!root) return new AVLNode(k);

    if (k < root->key) root->left = Push(root->left, k);
    else if (k > root->key) root->right = Push(root->right, k);
    else return root;

    root->height = 1 + max(GetHeight(root->left), GetHeight(root->right));
    int balance = GetBalance(root);

    // Left Left
    if (balance > 1 && k < root->left->key) return RightRotate(root);
    // Right Right
    if (balance < -1 && k > root->right->key) return LeftRotate(root);
    // Left Right
    if (balance > 1 && k > root->left->key) {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }
    // Right Left
    if (balance < -1 && k < root->right->key) {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root;
}

AVLNode* AVLTree::DelElm(AVLNode* root, int k) {
    if (!root) return root;

    if (k < root->key) root->left = DelElm(root->left, k);
    else if (k > root->key) root->right = DelElm(root->right, k);
    else {
        if (!root->left || !root->right) {
            AVLNode* childNode = root->left ? root->left : root->right;

            if (!childNode) {
                childNode = root;
                root = nullptr;
            } else {
                *root = *childNode;
            }
            delete childNode;
        } else {
            AVLNode* temp = GetMinValueNode(root->right);
            root->key = temp->key;
            root->right = DelElm(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + max(GetHeight(root->left), GetHeight(root->right));
    int balance = GetBalance(root);

    // Left Left
    if (balance > 1 && GetBalance(root->left) >= 0) return RightRotate(root);
    // Left Right
    if (balance > 1 && GetBalance(root->left) < 0) {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }
    // Right Right
    if (balance < -1 && GetBalance(root->right) <= 0) return LeftRotate(root);
    // Right Left
    if (balance < -1 && GetBalance(root->right) > 0) {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root;
}

void AVLTree::BFS(AVLNode* root) {
    if (!root) {
        return;
    }

    queue<AVLNode*> q;
    q.push(root);

    while (!q.empty()) {
        AVLNode* current = q.front();
        q.pop();
        cout << current->key << " ";
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    cout << endl;
}

void AVLTree::DFS(AVLNode* root) {
    if (!root) {
        return;
    }

    DFS(root->left);
    cout << root->key << " ";
    DFS(root->right);
}

void AVLTree::Destroy(AVLNode* root) {
    if (!root) return;
    Destroy(root->left);
    Destroy(root->right);
    delete root;
}

AVLNode* AVLTree::GetMinValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left) current = current->left;
    return current;
}

int AVLTree::GetHeight(AVLNode* n) {
    if (!n) return 0;
    return n->height;
}

int AVLTree::GetBalance(AVLNode* n) {
    if (!n) return 0;
    return GetHeight(n->left) - GetHeight(n->right);
}

AVLNode* AVLTree::RightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;
    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;

    return x;
}

AVLNode* AVLTree::LeftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;
    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;

    return y;
}

void AVLTree::GetElms(AVLNode* root, vector<string>& elements) {
    if (!root) return;

    GetElms(root->left, elements);
    elements.push_back(to_string(root->key));
    GetElms(root->right, elements);
}

int AVLTree::GetSize(AVLNode* root) {
    if (!root) {
        return 0;
    }
    return 1 + GetSize(root->left) + GetSize(root->right);
}