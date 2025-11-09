#pragma once
#include "DynamicArray.hpp"
#include <iostream>
#include <limits>

using namespace std;

class LRUCache {
private:
    struct CacheItem {
        int key;
        int value;
        int timestamp;
        bool valid;

        CacheItem();
    };

    int capacity;
    int timer;
    DynamicArray<CacheItem> cache;

    int findIndex(int key) const;
    int findLRUIndex() const;
    int findFreeSlot() const;

public:
    LRUCache(int cap);

    int get(int key);
    void insert(int key, int value);
    bool remove(int key);
    void display() const;
    int getSize() const;
    bool empty() const;
    DynamicArray<int> keys() const;
    DynamicArray<int> values() const;
    ~LRUCache();
};