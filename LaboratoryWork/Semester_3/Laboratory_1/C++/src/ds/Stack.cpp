#include "Stack.hpp"
using namespace std;

void Stack::Init() {
    head = nullptr;
}

void Stack::Push(string obj) {
    StackNode* newNode = new StackNode{obj, head};
    head = newNode;
}

string Stack::Pop() {
    if (!head) {
        cerr << "Pop: stack is empty!" << endl;
        return "";
    }

    StackNode* removedNode = head;
    string removedValue = head->data;

    head = head->next;
    delete removedNode;
    return removedValue;
}

void Stack::Print() {
    StackNode* currentNode = head;
    while (currentNode) {
        cout << currentNode->data << " ";
        currentNode = currentNode->next;
    }
    cout << endl;
}

int Stack::GetSize() {
    StackNode* currentNode = head;
    int currentSize = 0;
    while (currentNode) {
        currentNode = currentNode->next;
        currentSize++;
    }
    return currentSize;
}

string Stack::GetElm(int pos) {
    StackNode* currentNode = head;
    int currentPos = 0;
    while (currentNode) {
        if (currentPos == pos) {
            return currentNode->data;
        }
        currentNode = currentNode->next;
        currentPos++;
    }
    throw invalid_argument("GetElm: invalid position!");
}

void Stack::Destroy() {
    StackNode* currentNode = head;
    while (currentNode) {
        StackNode* deletedNode = currentNode;
        currentNode = currentNode->next;
        delete deletedNode;
    }
    head = nullptr;
}

Stack::~Stack() {
    Destroy();
}