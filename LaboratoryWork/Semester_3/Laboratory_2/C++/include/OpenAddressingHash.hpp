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

    int hash(int key) const;

public:
    OpenHash(int cap = 16);
    ~OpenHash();

    void insert(int key, const string& value);
    string find(int key) const;
    bool remove(int key);
    void display() const;
};