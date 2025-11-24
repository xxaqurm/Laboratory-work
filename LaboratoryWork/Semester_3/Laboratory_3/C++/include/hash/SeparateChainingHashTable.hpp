#pragma once
#include <iostream>
#include <stdexcept>
#include "../ds/Array.hpp"

using namespace std;

template<typename Key, typename Value>
class SeparateChainingHashMap {
private:
    struct Node {
        Key key;
        Value value;
        Node* next;
        Node(const Key& k, const Value& v) : key(k), value(v), next(nullptr) {}
    };

    Array<Node*> table;
    size_t capacity;
    size_t currentSize = 0;

    size_t hash(const Key& key) const;

public:
    SeparateChainingHashMap(size_t initialCapacity = 11);
    ~SeparateChainingHashMap();

    void insert(const Key& key, const Value& value);
    bool contains(const Key& key) const;
    bool remove(const Key& key);
    Value get(const Key& key) const;
    void display() const;
    size_t size() const { return currentSize; }
};

template<typename Key, typename Value>
SeparateChainingHashMap<Key, Value>::SeparateChainingHashMap(size_t initialCapacity) : capacity(initialCapacity), table(initialCapacity) {
    for (size_t i = 0; i < capacity; ++i) table[i] = nullptr;
}

template<typename Key, typename Value>
SeparateChainingHashMap<Key, Value>::~SeparateChainingHashMap() {
    for (size_t i = 0; i < capacity; ++i) {
        Node* current = table[i];
        while (current) {
            Node* tmp = current;
            current = current->next;
            delete tmp;
        }
    }
}

template<typename Key, typename Value>
size_t SeparateChainingHashMap<Key, Value>::hash(const Key& key) const {
    return static_cast<size_t>(key) % capacity;
}

template<typename Key, typename Value>
void SeparateChainingHashMap<Key, Value>::insert(const Key& key, const Value& value) {
    size_t idx = hash(key);
    Node* current = table[idx];
    while (current) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    Node* newNode = new Node(key, value);
    newNode->next = table[idx];
    table[idx] = newNode;
    currentSize++;
}

template<typename Key, typename Value>
bool SeparateChainingHashMap<Key, Value>::contains(const Key& key) const {
    size_t idx = hash(key);
    Node* current = table[idx];
    while (current) {
        if (current->key == key) return true;
        current = current->next;
    }
    return false;
}

template<typename Key, typename Value>
bool SeparateChainingHashMap<Key, Value>::remove(const Key& key) {
    size_t idx = hash(key);
    Node* current = table[idx];
    Node* prev = nullptr;
    while (current) {
        if (current->key == key) {
            if (prev) prev->next = current->next;
            else table[idx] = current->next;
            delete current;
            currentSize--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

template<typename Key, typename Value>
Value SeparateChainingHashMap<Key, Value>::get(const Key& key) const {
    size_t idx = hash(key);
    Node* current = table[idx];
    while (current) {
        if (current->key == key) return current->value;
        current = current->next;
    }
    throw out_of_range("Key not found");
}

template<typename Key, typename Value>
void SeparateChainingHashMap<Key, Value>::display() const {
    for (size_t i = 0; i < capacity; ++i) {
        cout << i << ": ";
        Node* current = table[i];
        while (current) {
            cout << "(" << current->key << ", " << current->value << ") -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
}
