#pragma once
#include <iostream>
#include <string>

using namespace std;

enum class State {
    EMPTY,
    OCCUPIED,
    DELETED
};

class OpenHash {
private:
    struct Entry {
        int key;
        string value;
        State state;
        Entry() : state(State::EMPTY) {}
    };

    Entry* table;
    int capacity;
    int size;

    int hash(int key) const {
        unsigned long h = 0;
        for (char c : to_string(key))
            h = h * 131 + c;
        return h % capacity;
    }

public:
    OpenHash(int cap = 16) {
        capacity = cap;
        size = 0;
        table = new Entry[capacity];
    }

    ~OpenHash() {
        delete[] table;
    }

    void insert(int key, const string& value) {
        int idx = hash(key);
        int start = idx;

        do {
            if (table[idx].state == State::EMPTY || table[idx].state == State::DELETED) {
                table[idx].key = key;
                table[idx].value = value;
                table[idx].state = State::OCCUPIED;
                size++;
                return;
            } else if (table[idx].state == State::OCCUPIED && table[idx].key == key) {
                table[idx].value = value; // обновляем значение
                return;
            }
            idx = (idx + 1) % capacity;
        } while (idx != start);

        cout << "Таблица переполнена!" << endl;
    }

    bool find(int key, string& outValue) const {
        int idx = hash(key);
        int start = idx;

        do {
            if (table[idx].state == State::EMPTY)
                return false;
            if (table[idx].state == State::OCCUPIED && table[idx].key == key) {
                outValue = table[idx].value;
                return true;
            }
            idx = (idx + 1) % capacity;
        } while (idx != start);

        return false;
    }

    bool remove(int key) {
        int idx = hash(key);
        int start = idx;

        do {
            if (table[idx].state == State::EMPTY)
                return false;
            if (table[idx].state == State::OCCUPIED && table[idx].key == key) {
                table[idx].state = State::DELETED;
                size--;
                return true;
            }
            idx = (idx + 1) % capacity;
        } while (idx != start);

        return false;
    }

    void display() const {
        for (int i = 0; i < capacity; ++i)
            if (table[i].state == State::OCCUPIED)
                cout << i << ": (" << table[i].key << " -> " << table[i].value << ")\n";
    }
};