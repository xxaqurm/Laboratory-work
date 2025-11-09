#include "../../include/LRUHash.hpp"

LRUCache::CacheItem::CacheItem() : key(-1), value(-1), timestamp(-1), valid(false) {}

LRUCache::LRUCache(int cap) : capacity(cap), timer(0), cache(cap) {}

int LRUCache::findIndex(int key) const {
    for (size_t i = 0; i < cache.size(); i++) {
        if (cache[i].valid && cache[i].key == key)
            return i;
    }
    return -1;
}

int LRUCache::findLRUIndex() const {
    int oldestTime = numeric_limits<int>::max();
    int oldestIndex = -1;

    for (size_t i = 0; i < cache.size(); i++) {
        if (cache[i].valid && cache[i].timestamp < oldestTime) {
            oldestTime = cache[i].timestamp;
            oldestIndex = i;
        }
    }
    return oldestIndex;
}

int LRUCache::findFreeSlot() const {
    for (size_t i = 0; i < cache.size(); i++) {
        if (!cache[i].valid)
            return i;
    }
    return -1;
}

int LRUCache::get(int key) {
    int index = findIndex(key);
    if (index == -1) return -1;

    cache[index].timestamp = ++timer;
    return cache[index].value;
}

void LRUCache::insert(int key, int value) {
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
        int lruIndex = findLRUIndex();
        if (lruIndex != -1) {
            cache[lruIndex].key = key;
            cache[lruIndex].value = value;
            cache[lruIndex].timestamp = ++timer;
            cache[lruIndex].valid = true;
        }
    }
}

bool LRUCache::remove(int key) {
    int index = findIndex(key);
    if (index == -1) return false;

    cache[index].valid = false;
    return true;
}

void LRUCache::display() const {
    cout << "LRUCache (capacity: " << capacity << ", size: " << getSize() << "):" << endl;
    for (size_t i = 0; i < cache.size(); i++) {
        if (cache[i].valid) {
            cout << "  [" << cache[i].key << " -> " << cache[i].value
                 << ", ts: " << cache[i].timestamp << "]" << endl;
        }
    }
}

int LRUCache::getSize() const {
    int count = 0;
    for (size_t i = 0; i < cache.size(); i++)
        if (cache[i].valid) count++;
    return count;
}

bool LRUCache::empty() const {
    return getSize() == 0;
}

DynamicArray<int> LRUCache::keys() const {
    DynamicArray<int> result;
    for (size_t i = 0; i < cache.size(); i++) {
        if (cache[i].valid)
            result.push_back(cache[i].key);
    }
    return result;
}

DynamicArray<int> LRUCache::values() const {
    DynamicArray<int> result;
    for (size_t i = 0; i < cache.size(); i++) {
        if (cache[i].valid)
            result.push_back(cache[i].value);
    }
    return result;
}

LRUCache::~LRUCache() {
    for (size_t i = 0; i < cache.size(); i++)
        cache[i].valid = false;
    timer = 0;
}