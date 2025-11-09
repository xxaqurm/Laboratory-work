#include <iostream>
#include <string>
#include "../../include/ChainedHash.hpp"
#include "../../include/OpenAddressingHash.hpp"

using namespace std;

void intWithHashs() {
    int method;
    cout << "Выберите режим (1 - метод цепочек, 2 - метод открытой адресации): ";
    cin >> method;

    if (method == 1) {
        HashTable hsh;
        while (true) {
            string cmd;
            int key;
            string value;
            cout << "Введите команду (INSERT key value | SEARCH key value | REMOVE key value | DISPLAY): ";
            cin >> cmd;

            if (cmd == "INSERT") {
                cin >> key >> value;
                hsh.insert(key, value);
            } else if (cmd == "SEARCH") {
                cin >> key >> value;
                cout << hsh.search(key);
            } else if (cmd == "REMOVE") {
                cin >> key >> value;
                if (hsh.remove(key)) {
                    cout << "Элемент удален" << endl;
                } else {
                    cout << "Элемент для удаления не найден" << endl;
                }
            } else if (cmd == "DISPLAY") {
                hsh.display();
            } else {
                throw invalid_argument("[ ERROR ] Unknown command");
            }
        }
    } else if (method == 2) {
        OpenHash hsm;
        while (true) {
            string cmd;
            int key;
            string value;
            cout << "Введите команду (INSERT key value | SEARCH key value | REMOVE key value | DISPLAY): ";
            cin >> cmd;

            if (cmd == "INSERT") {
                cin >> key >> value;
                hsm.insert(key, value);
            } else if (cmd == "SEARCH") {
                cin >> key >> value;
                if (hsm.find(key, value)) {
                    cout << "Элемент присутствует!" << endl;
                } else {
                    cout << "Элемент отсутствует!" << endl;
                }
            } else if (cmd == "REMOVE") {
                cin >> key >> value;
                hsm.remove(key);
            } else if (cmd == "DISPLAY") {
                hsm.display();
            }
        }
    } else {
        throw invalid_argument("[ ERROR ] Unknown method");
    }
}