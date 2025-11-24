#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    Queue();
    ~Queue();

    void enqueue(const T& value);
    void dequeue();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    bool empty() const;
    int size() const;
    void clear();
};

template<typename T>
Queue<T>::Queue() : head(nullptr), tail(nullptr), size(0) {}

template<typename T>
Queue<T>::~Queue() {
    clear();
}

template<typename T>
void Queue<T>::enqueue(const T& value) {
    Node* newNode = new Node(value);
    if (!tail) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template<typename T>
void Queue<T>::dequeue() {
    if (empty()) throw out_of_range("Queue is empty");
    Node* tmp = head;
    head = head->next;
    delete tmp;
    size--;
    if (!head) tail = nullptr;
}

template<typename T>
T& Queue<T>::front() {
    if (empty()) throw out_of_range("Queue is empty");
    return head->data;
}

template<typename T>
const T& Queue<T>::front() const {
    if (empty()) throw out_of_range("Queue is empty");
    return head->data;
}

template<typename T>
T& Queue<T>::back() {
    if (empty()) throw out_of_range("Queue is empty");
    return tail->data;
}

template<typename T>
const T& Queue<T>::back() const {
    if (empty()) throw out_of_range("Queue is empty");
    return tail->data;
}

template<typename T>
bool Queue<T>::empty() const {
    return head == nullptr;
}

template<typename T>
int Queue<T>::size() const {
    return size;
}

template<typename T>
void Queue<T>::clear() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    head = tail = nullptr;
    size = 0;
}
