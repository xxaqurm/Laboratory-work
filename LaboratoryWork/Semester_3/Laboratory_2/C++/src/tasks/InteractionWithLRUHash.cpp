#include "../../include/LRUHash.hpp"

using namespace std;

void interactionWithLRU() {
    int cap, Q;
    
    cout << "Размер кэша (cap) и количество запросов (Q)" << endl;
    cout << "cap: ";
    cin >> cap;
    cout << "Q: ";
    cin >> Q;

    LRUCache cache(cap);
    for (int i = 0; i < Q; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "SET") {
            int key, value;
            cin >> key >> value;
            cache.insert(key, value);
        } else if (cmd == "GET") {
            int key;
            cin >> key;
            cout << cache.get(key) << endl;
        } else {
            throw invalid_argument("[ ERROR ] Unknown command");
        }
    }
}