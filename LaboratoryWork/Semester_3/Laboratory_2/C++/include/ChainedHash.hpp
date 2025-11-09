#pragma once
#include <iostream>
#include "DynamicArray.hpp"

using namespace std;

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    DynamicArray<DynamicArray<pair<int, string>>> table;

    int foldingHash(int key) const;

public:
    HashTable();

    void insert(int key, const string& value);
    string search(int key) const;
    bool remove(int key);
    void display() const;
};