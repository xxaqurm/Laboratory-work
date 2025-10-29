#include "../../include/menu.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

void startMenu() {
    cout << "Список программ:" << endl;
    cout << "0. Exit" << endl;
    cout << "1. Arighmteic expression" << endl;
    cout << "2. Interactions with set (для использования перезапустите программу и используйте следующий шаблон: ./main --file somethingFile.txt --query \"COMMAND StructName Data\")" << endl;
    cout << "3. Set partition" << endl;
    cout << "4. Subarrays" << endl;
    cout << "5. Check AVL-tree balance" << endl;
    cout << "6. Convolution method" << endl;
    cout << "7. LRU cach" << endl;
    cout << "Выберите программу: ";
}