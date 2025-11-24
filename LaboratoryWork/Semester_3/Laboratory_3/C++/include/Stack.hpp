#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t size;

public:
    Stack();
    ~Stack();

    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;
    bool empty() const;
    int size() const;
    void clear();
};

template<typename T>
Stack<T>::Stack() : head(nullptr), size(0) {}

template<typename T>
Stack<T>::~Stack() {
    clear();
}

template<typename T>
void Stack<T>::push(const T& value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    size++;
}

template<typename T>
void Stack<T>::pop() {
    if (empty()) throw out_of_range("Stack is empty");
    Node* tmp = head;
    head = head->next;
    delete tmp;
    size--;
}

template<typename T>
T& Stack<T>::top() {
    if (empty()) throw out_of_range("Stack is empty");
    return head->data;
}

template<typename T>
const T& Stack<T>::top() const {
    if (empty()) throw out_of_range("Stack is empty");
    return head->data;
}

template<typename T>
bool Stack<T>::empty() const {
    return head == nullptr;
}

template<typename T>
int Stack<T>::size() const {
    return size;
}

template<typename T>
void Stack<T>::clear() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    size = 0;
}
