#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <utility>

using namespace std;

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    vector<list<pair<int, string>>> table;

    int foldingHash(int key) const {
        int sum = 0;
        int temp = key;
        while (temp > 0) {//подтвердить что наим
            sum += temp % 100;
            temp /= 100;
        }
        cout << sum % TABLE_SIZE << endl;
        return sum % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    void insert(int key, string value) { // перезапись ключ
        int index = foldingHash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].push_back({key, value});
    }

    string search(int key) const { // по ключу
        int index = foldingHash(key);
        for (const auto& [currentKey, currentValue] : table[index]) {
            if (currentKey == key) 
                return currentValue;
        }
        return "";
    }

    bool remove(int key) { // по ключу
        int index = foldingHash(key);
        auto& bucket = table[index];

        for (auto it = bucket.begin(); it != bucket.end(); it++) {
            if (it->first == key) {
                bucket.erase(it);
                return true;
            }
        }
        return false;
    }
    
    void display() const {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (!table[i].empty()) {
                cout << i << ": ";
                for (const auto& [currentKey, currentValue] : table[i]) {
                    cout << "[" << currentKey << " -> " << currentValue << "] ";
                }
                cout << endl;
            }
        }
    }
};