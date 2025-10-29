#pragma once
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class LRUCache {
private:
    struct CacheItem {
        int key;
        int value;
        int timestamp;
        bool valid;  // state

        CacheItem() : key(-1), value(-1), timestamp(-1), valid(false) {}
    };

    int capacity;
    int timer;
    vector<CacheItem> cache;

    int findIndex(int key) const {
        for (int i = 0; i < cache.size(); i++) {
            if (cache[i].valid && cache[i].key == key) {
                return i;
            }
        }
        return -1;
    }

    int findLRUIndex() const {  // min timestamp
        int oldestTime = numeric_limits<int>::max();
        int oldestIndex = -1;

        for (int i = 0; i < cache.size(); i++) {
            if (cache[i].valid && cache[i].timestamp < oldestTime) {
                oldestTime = cache[i].timestamp;
                oldestIndex = i;
            }
        }
        return oldestIndex;
    }

    int findFreeSlot() const {
        for (int i = 0; i < cache.size(); i++) {
            if (!cache[i].valid) {
                return i;
            }
        }
        return -1;
    }

public:
    LRUCache(int cap) : capacity(cap), timer(0) {
        cache.resize(capacity);
    }

    int get(int key) {
        int index = findIndex(key);
        if (index == -1) {
            return -1;
        }

        cache[index].timestamp = ++timer;
        return cache[index].value;
    }

    void insert(int key, int value) {
        int index = findIndex(key);
        
        if (index != -1) {
            cache[index].value = value;
            cache[index].timestamp = ++timer;
            return;
        }

        int freeSlot = findFreeSlot();
        
        if (freeSlot != -1) {
            cache[freeSlot].key = key;
            cache[freeSlot].value = value;
            cache[freeSlot].timestamp = ++timer;
            cache[freeSlot].valid = true;
        } else {
            int lruIndex = findLRUIndex();  // min time
            if (lruIndex != -1) {
                cache[lruIndex].key = key;
                cache[lruIndex].value = value;
                cache[lruIndex].timestamp = ++timer;
                cache[lruIndex].valid = true;
            }
        }
    }

    bool remove(int key) {
        int index = findIndex(key);
        if (index == -1) {
            return false;
        }
        cache[index].valid = false;
        return true;
    }

    void display() const {
        cout << "LRUCache (capacity: " << capacity << ", size: " << getSize() << "):" << endl;
        for (int i = 0; i < cache.size(); i++) {
            if (cache[i].valid) {
                cout << "  [" << cache[i].key << " -> " << cache[i].value 
                     << ", ts: " << cache[i].timestamp << "]" << endl;
            }
        }
    }

    int getSize() const {
        int count = 0;
        for (const auto& item : cache) {
            if (item.valid) count++;
        }
        return count;
    }

    bool empty() const {
        return getSize() == 0;
    }

    vector<int> keys() const {
        vector<int> result;
        for (const auto& item : cache) {
            if (item.valid) {
                result.push_back(item.key);
            }
        }
        return result;
    }

    vector<int> values() const {
        vector<int> result;
        for (const auto& item : cache) {
            if (item.valid) {
                result.push_back(item.value);
            }
        }
        return result;
    }

    ~LRUCache() {
        for (auto& item : cache) {
            item.valid = false;
        }
        timer = 0;
    }
};