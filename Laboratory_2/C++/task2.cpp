#include <iostream>
#include <string>
#include <vector>

using namespace std;


void print_bottles(string bottle, int count) {
    /* Выводит бутылки на экран. */
    for (int i = 0; i < count; i++) {
        if (i % 3 == 0) cout << endl;
        cout << bottle << " ";
    }
}


pair<int, int> drink_simulation(int n, int m) {
    /* Показывает все шаги питья. */
    int full = n;
    int empty = 0;
    int total_drunk = 0;
    int iterations = 0;

    string full_bottle  = "●";
    string empty_bottle = "○";

    // Выведем дано
    cout << "Дано";
    print_bottles(full_bottle, full);
    cout << endl << endl;
    
    while (true) {
        // Шаг 1: выпить все полные бутылки
        if (full > 0) {
            total_drunk += full;
            empty += full;
            full = 0;
            iterations++;

            // Выведем все выпитые бутылки
            cout << iterations << " шаг";
            print_bottles(empty_bottle, empty);
            cout << endl << endl;

            if (empty < m) break;  // условие завершения
            
            // Шаг 2: обмен пустых бутылок на полные
            full = empty / m;
            empty = empty % m;
            iterations++;

            // Выведем бутылки после обмена 
            cout << iterations << " шаг";
            print_bottles(full_bottle, full);
            print_bottles(empty_bottle, empty);
            cout << endl << endl;
        }
    }

    return {total_drunk, iterations};
}


int main(void) {
    int n, m;
    cout << "Введите количество полных бутылок и количество бутылок, которых достаточно для обмена: ";
    cin >> n >> m;

    cout << "Input: " << n << " " << m << endl;

    pair<int, int> result = drink_simulation(n, m);

    int total = result.first;
    int iters = result.second;

    cout << "Output (total, iters): " << total << " " << iters << endl;
}