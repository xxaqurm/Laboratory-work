#pragma once
#include <vector>
#include <stdexcept>

using namespace std;

class Set {
private:
    enum class State {
        EMPTY,
        OCCUPIED,
        DELETED
    };

    struct Bucket {
        string value;
        State state = State::EMPTY;
    };

    vector<Bucket> table;
    size_t numElements;
    const double loadFactor = 0.75;
    const int key = 31;

    size_t HashFunctionHorner(const string& s, int table_size, const int key) const {
        size_t hash_result = 0;
        for (int i = 0; i != s.length(); i++)
            hash_result = (key * hash_result + s[i]) % table_size;
        hash_result = (hash_result * 2 + 1) % table_size;
        return hash_result;
    }


    size_t HashFunction1(const string& s) const {
        return HashFunctionHorner(s, table.size(), key);
    }

    size_t HashFunction2(const string& s) const {
        return 1 + (HashFunctionHorner(s, table.size(), key) % (table.size() - 1));
    }

    void rehash() {
        vector<Bucket> oldTable = move(table);
        table = vector<Bucket>(oldTable.size() * 2);
        numElements = 0;

        for (const auto& bucket : oldTable) {
            if (bucket.state == State::OCCUPIED)
                add(bucket.value);
        }
    }

public:
    explicit Set(size_t initialSize = 8) : table(initialSize), numElements(0) {}

    bool add(const string& value) {
        if (static_cast<double>(numElements) / table.size() > loadFactor) 
            rehash();
        
        size_t h1 = HashFunction1(value);
        size_t h2 = HashFunction2(value);
        size_t idx = h1;

        for (size_t i = 0; i < table.size(); i++) {
            if (table[idx].state == State::EMPTY || table[idx].state == State::DELETED) {
                table[idx].value = value;
                table[idx].state = State::OCCUPIED;
                numElements++;
                return true;
            }
            if (table[idx].state == State::OCCUPIED && table[idx].value == value)
                return false;  // существует
            idx = (h1 + i * h2) % table.size();
        }
        return false;  // таблица переполнена
    }

    bool contains(const string& value) const {
        size_t h1 = HashFunction1(value);
        size_t h2 = HashFunction2(value);
        size_t idx = h1;

        for (size_t i = 0; i < table.size(); i++) {
            if (table[idx].state == State::EMPTY)
                return false;
            if (table[idx].state == State::OCCUPIED && table[idx].value == value)
                return true;
            idx = (h1 + i * h2) % table.size();
        }
        return false;
    }

    bool remove(const string& value) {
        size_t h1 = HashFunction1(value);
        size_t h2 = HashFunction2(value);
        size_t idx = h1;

        for (size_t i = 0; i < table.size(); i++) {
            if (table[idx].state == State::EMPTY)
                return false;
            if (table[idx].state == State::OCCUPIED && table[idx].value == value) {
                table[idx].state = State::DELETED;
                numElements--;
                return true;
            }
            idx = (h1 + i * h2) % table.size();
        }
        return false;
    }

    void displaySet() const {
        cout << "{ ";
        for (size_t i = 0; i < table.size(); i++)
            if (table[i].state == State::OCCUPIED)
                cout << table[i].value << " ";
        cout << " }" << endl;
    }

    void getElms(vector<string>& elms) {
        for (size_t i = 0; i < table.size(); i++) {
            if (table[i].state == State::OCCUPIED)
                elms.push_back(table[i].value);
        }
    }
};