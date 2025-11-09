#include "../../include/ChainedHash.hpp"

HashTable::HashTable() : table(TABLE_SIZE) {
    for (size_t i = 0; i < table.size(); i++)
        table[i] = DynamicArray<pair<int, string>>();
}

int HashTable::foldingHash(int key) const {
    int sum = 0;
    int temp = key;
    while (temp > 0) {
        sum += temp % 100;
        temp /= 100;
    }
    return sum % TABLE_SIZE;
}

void HashTable::insert(int key, const string& value) {
    int index = foldingHash(key);
    DynamicArray<pair<int, string>>& bucket = table[index];

    for (size_t i = 0; i < bucket.size(); i++) {
        if (bucket[i].first == key) {
            bucket[i].second = value;
            return;
        }
    }
    bucket.push_back({key, value});
}

string HashTable::search(int key) const {
    int index = foldingHash(key);
    const DynamicArray<pair<int, string>>& bucket = table[index];

    for (size_t i = 0; i < bucket.size(); i++) {
        if (bucket[i].first == key)
            return bucket[i].second;
    }
    return "";
}

bool HashTable::remove(int key) {
    int index = foldingHash(key);
    DynamicArray<pair<int, string>>& bucket = table[index];

    for (size_t i = 0; i < bucket.size(); i++) {
        if (bucket[i].first == key) {
            bucket.DelElm(i);
            return true;
        }
    }
    return false;
}

void HashTable::display() const {
    for (size_t i = 0; i < table.size(); i++) {
        const DynamicArray<pair<int, string>>& bucket = table[i];
        if (bucket.size() > 0) {
            cout << i << ": ";
            for (size_t j = 0; j < bucket.size(); j++) {
                cout << "[" << bucket[j].first << " -> " << bucket[j].second << "] ";
            }
            cout << endl;
        }
    }
}