#pragma once
#include <iostream>
#include <stdexcept>
#include "../ds/Array.hpp"

using namespace std;

template<typename Key>
class DoubleHashingSet {
private:
    enum class SlotStatus {
        EMPTY,
        OCCUPIED,
        DELETED
    };

    struct Slot {
        Key key;
        SlotStatus status = SlotStatus::EMPTY;
    };

    Array<Slot> table;
    size_t currentSize = 0;
    size_t capacity;

    size_t hash1(const Key& key) const;
    size_t hash2(const Key& key) const;
    size_t probe(const Key& key, size_t i) const;
    void resize(size_t newCapacity);

public:
    DoubleHashingSet(size_t initialCapacity = 11);
    void insert(const Key& key);
    bool contains(const Key& key) const;
    bool remove(const Key& key);
    void display() const;
};

template<typename Key>
DoubleHashingSet<Key>::DoubleHashingSet(size_t initialCapacity) : capacity(initialCapacity), table(initialCapacity) {}

template<typename Key>
size_t DoubleHashingSet<Key>::hash1(const Key& key) const {
    return static_cast<size_t>(key) % capacity;
}

template<typename Key>
size_t DoubleHashingSet<Key>::hash2(const Key& key) const {
    return 1 + (static_cast<size_t>(key) % (capacity - 1));
}

template<typename Key>
size_t DoubleHashingSet<Key>::probe(const Key& key, size_t i) const {
    return (hash1(key) + i * hash2(key)) % capacity;
}

template<typename Key>
void DoubleHashingSet<Key>::resize(size_t newCapacity) {
    Array<Slot> oldTable = table;
    table = Array<Slot>(newCapacity);
    capacity = newCapacity;
    currentSize = 0;

    for (size_t i = 0; i < oldTable.size(); ++i) {
        if (oldTable[i].status == SlotStatus::OCCUPIED) {
            insert(oldTable[i].key);
        }
    }
}

template<typename Key>
void DoubleHashingSet<Key>::insert(const Key& key) {
    if (currentSize * 2 >= capacity) resize(capacity * 2 + 1);

    size_t i = 0;
    size_t idx;
    do {
        idx = probe(key, i);
        if (table[idx].status != SlotStatus::OCCUPIED) {
            table[idx].key = key;
            table[idx].status = SlotStatus::OCCUPIED;
            currentSize++;
            return;
        } else if (table[idx].status == SlotStatus::OCCUPIED && table[idx].key == key) {
            return;
        }
        ++i;
    } while (i < capacity);

    throw overflow_error("Set is full");
}

template<typename Key>
bool DoubleHashingSet<Key>::contains(const Key& key) const {
    size_t i = 0;
    size_t idx;
    do {
        idx = probe(key, i);
        if (table[idx].status == SlotStatus::EMPTY) return false;
        if (table[idx].status == SlotStatus::OCCUPIED && table[idx].key == key) return true;
        ++i;
    } while (i < capacity);

    return false;
}

template<typename Key>
bool DoubleHashingSet<Key>::remove(const Key& key) {
    size_t i = 0;
    size_t idx;
    do {
        idx = probe(key, i);
        if (table[idx].status == SlotStatus::EMPTY) return false;
        if (table[idx].status == SlotStatus::OCCUPIED && table[idx].key == key) {
            table[idx].status = SlotStatus::DELETED;
            currentSize--;
            return true;
        }
        ++i;
    } while (i < capacity);

    return false;
}

template<typename Key>
void DoubleHashingSet<Key>::display() const {
    for (size_t i = 0; i < capacity; ++i) {
        cout << i << ": ";
        if (table[i].status == SlotStatus::OCCUPIED) {
            cout << table[i].key;
        } else if (table[i].status == SlotStatus::DELETED) {
            cout << "DELETED";
        } else {
            cout << "EMPTY";
        }
        cout << endl;
    }
}
