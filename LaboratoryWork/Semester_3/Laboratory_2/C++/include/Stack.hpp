#pragma once
#include <stdexcept>

using namespace std;

template <typename T>
class StackNode {
public:
    T key;
    StackNode* next;

    StackNode(T value) : key(value), next(nullptr) {}
};

template <typename T>
class Stack {
private:
    StackNode<T>* head;

public:
    Stack() : head(nullptr) {}
    ~Stack() {
        while (head) {
            Pop();
        }
    }

    void Push(T data) {
        StackNode<T>* newNode = new StackNode<T>(data);
        newNode->next = head;
        head = newNode;
    }

    void Pop() {
        if (!head) {
            throw runtime_error("[ ERROR ] Stack is empty!");
        }
        StackNode<T>* deletedNode = head;
        head = head->next;
        delete deletedNode;
    }

    T Top() const {
        if (!head) {
            throw runtime_error("[ ERROR ] Stack is empty!");
        }
        return head->key;
    }

    bool Empty() const {
        return head == nullptr;
    }

    void Print() const {
        StackNode<T>* currentNode = head;
        while (currentNode) {
            cout << currentNode->key << " ";
            currentNode = currentNode->next;
        }
        cout << endl;
    }
};