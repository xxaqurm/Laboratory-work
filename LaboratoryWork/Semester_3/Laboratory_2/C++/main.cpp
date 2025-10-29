#include <iostream>
#include <fstream>

#include "./include/menu.hpp"
#include "./include/arithmetic_expression.hpp"
#include "./include/interaction_with_set.hpp"
#include "./include/set_partition.hpp"
#include "./include/subarrays.hpp"
#include "./include/AVL_balance.hpp"
#include "./include/LRU.hpp"
#include "./include/interaction_with_LRU.hpp"
#include "./include/interaction_with_convolution_hash.hpp"
#include "./include/convolution_hash.hpp"
#include "./include/openHash.hpp"

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
                intWithConvHash();
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