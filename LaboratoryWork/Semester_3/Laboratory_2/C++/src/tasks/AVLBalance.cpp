#include "../../include/AVLBalance.hpp"

using namespace std;

void AVLBalance() {
    cout << "Введите элементы: ";

    BST tree;
    int currentElm;
    cin >> currentElm;
    while (currentElm != 0) {
        tree.root = tree.insert(tree.root, currentElm);
        cin >> currentElm;
    }

    bool isBalanced = true;
    tree.checkBalance(tree.root, isBalanced);
    
    cout << (isBalanced ? "YES" : "NO") << endl;
}