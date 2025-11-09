#include <iostream>
#include <fstream>

#include "include/menu.hpp"
#include "include/ArithmeticExpression.hpp"
#include "include/SetPartition.hpp"
#include "include/InteractionWithDoubleHashSet.hpp"
#include "include/Subarrays.hpp"
#include "include/AVLBalance.hpp"
#include "include/InteractionWithHashs.hpp"
#include "include/InteractionWithLRUHash.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    system("clear");
    try {
        int choice = -1;
        if (argc == 5) {
            choice = 2;
        } else {
            startMenu();
            cin >> choice;
        }

        switch (static_cast<MenuOptions>(choice)) {
            case MenuOptions::Exit:
                system("clear");
                return 0;
            case MenuOptions::ArithmeticExpression:
                cin.clear();
                cin.ignore();
                arithmeticExpression();
                break;
            case MenuOptions::InteractionWithSet:
                interactionWithSet(argc, argv);
                break;
            case MenuOptions::SetPartition:
                setPartition();
                break;
            case MenuOptions::Subarrays:
                subarrays();
                break;
            case MenuOptions::CheckBalance:
                AVLBalance();
                break;
            case MenuOptions::ConvolutionMethod:
                intWithHashs();
                break;
            case MenuOptions::LRUCache:
                interactionWithLRU();
                break;
            default:
                system("clear");
                cout << "Неверный выбор. Попробуйте снова" << endl;
                break;
        }
    } catch (exception& e) {
        cout << e.what() << endl;
    }
}