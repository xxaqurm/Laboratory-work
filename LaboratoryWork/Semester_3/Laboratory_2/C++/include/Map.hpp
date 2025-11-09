#pragma once
#include <iostream>
#include <stdexcept>
#include "DynamicArray.hpp"

template <typename K, typename V>
class Map {
private:
    struct Bucket {
        K key;
        V value;
        bool occupied = false;
    };

    DynamicArray<Bucket> table;

public:
    Map() : table(10) {}

    V& operator[](const K& key_) {
        for (size_t i = 0; i < table.size(); i++) {
            if (table[i].occupied && table[i].key == key_)
                return table[i].value;
        }

        for (size_t i = 0; i < table.size(); i++) {
            if (!table[i].occupied) {
                table[i].key = key_;
                table[i].value = V();
                table[i].occupied = true;
                return table[i].value;
            }
        }

        size_t oldSize = table.size();
        table.push_back(Bucket{});
        table[oldSize].key = key_;
        table[oldSize].value = V();
        table[oldSize].occupied = true;
        return table[oldSize].value;
    }

    bool contains(const K& key_) const {
        for (size_t i = 0; i < table.size(); i++)
            if (table[i].occupied && table[i].key == key_)
                return true;
        return false;
    }

    size_t size() const {
        size_t count = 0;
        for (size_t i = 0; i < table.size(); i++)
            if (table[i].occupied)
                count++;
        return count;
    }

    DynamicArray<K> keys() const {
        DynamicArray<K> keysArray;
        for (size_t i = 0; i < table.size(); i++) {
            if (table[i].occupied) {
                keysArray.push_back(table[i].key);
            }
        }
        return keysArray;
    }
};