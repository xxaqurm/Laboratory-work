#include "../../include/OpenAddressingHash.hpp"

int OpenHash::hash(int key) const {
    unsigned long h = 0;
    for (char c : to_string(key))
        h = h * 131 + c;
    return h % capacity;
}

OpenHash::OpenHash(int cap) {
    capacity = cap;
    size = 0;
    table = new Entry[capacity];
}

OpenHash::~OpenHash() {
    delete[] table;
}

void OpenHash::insert(int key, const string& value) {
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

bool OpenHash::find(int key, string& outValue) const {
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

bool OpenHash::remove(int key) {
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

void OpenHash::display() const {
    for (int i = 0; i < capacity; ++i)
        if (table[i].state == State::OCCUPIED)
            cout << i << ": (" << table[i].key << " -> " << table[i].value << ")\n";
}