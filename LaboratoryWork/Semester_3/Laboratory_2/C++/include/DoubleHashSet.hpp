#pragma once
#include "DynamicArray.hpp"
#include <iostream>
#include <stdexcept>

template <typename T>
class Set {
private:
    enum class State { EMPTY, OCCUPIED, DELETED };
    struct Bucket { T value; State state = State::EMPTY; };

    DynamicArray<Bucket> table;
    size_t numElements = 0;
    double loadFactor = 0.75;

    size_t HashFunction(const T& value, size_t mod) const {
        size_t hash = std::hash<T>{}(value);
        return hash % mod;
    }

    void rehash() {
        DynamicArray<Bucket> oldTable = table;
        table = DynamicArray<Bucket>(oldTable.size() * 2);
        numElements = 0;

        for (size_t i = 0; i < oldTable.size(); i++) {
            if (oldTable[i].state == State::OCCUPIED)
                add(oldTable[i].value);
        }
    }

public:
    Set(size_t initialSize = 8) : table(initialSize), numElements(0) {}

    bool add(const T& value) {
        if (static_cast<double>(numElements) / table.size() > loadFactor)
            rehash();

        size_t idx = HashFunction(value, table.size());
        size_t step = 1 + idx % (table.size() - 1);

        for (size_t i = 0; i < table.size(); i++) {
            if (table[idx].state == State::EMPTY || table[idx].state == State::DELETED) {
                table[idx].value = value;
                table[idx].state = State::OCCUPIED;
                numElements++;
                return true;
            }
            if (table[idx].state == State::OCCUPIED && table[idx].value == value)
                return false;
            idx = (idx + step) % table.size();
        }
        return false;
    }

    bool contains(const T& value) const {
        size_t idx = HashFunction(value, table.size());
        size_t step = 1 + idx % (table.size() - 1);

        for (size_t i = 0; i < table.size(); i++) {
            if (table[idx].state == State::EMPTY) return false;
            if (table[idx].state == State::OCCUPIED && table[idx].value == value) return true;
            idx = (idx + step) % table.size();
        }
        return false;
    }

    bool remove(const T& value) {
        size_t idx = HashFunction(value, table.size());
        size_t step = 1 + idx % (table.size() - 1);

        for (size_t i = 0; i < table.size(); i++) {
            if (table[idx].state == State::EMPTY) return false;
            if (table[idx].state == State::OCCUPIED && table[idx].value == value) {
                table[idx].state = State::DELETED;
                numElements--;
                return true;
            }
            idx = (idx + step) % table.size();
        }
        return false;
    }

    void pop() {
        for (size_t i = 0; i < table.size(); i++) {
            if (table[i].state == State::OCCUPIED) {
                table[i].state = State::DELETED;
                numElements--;
                return;
            }
        }
    }

    size_t size() const { return numElements; }

    bool empty() const { return numElements == 0; }

    const T& operator[](size_t idx) const {
        size_t count = 0;
        for (size_t i = 0; i < table.size(); i++) {
            if (table[i].state == State::OCCUPIED) {
                if (count == idx) return table[i].value;
                count++;
            }
        }
        throw std::out_of_range("Index out of range");
    }

    void getElms(DynamicArray<T>& out) const {
        for (size_t i = 0; i < table.size(); i++) {
            if (table[i].state == State::OCCUPIED) {
                out.push_back(table[i].value);
            }
        }
    }
};