#include <iostream>
#include <vector>
#include <map>
#include "algorithms.h"

using namespace std;

int main() {
    int n = 0;
    int k = 0;

    while (true) {
        cout << "Введите количество кандидатов и избирателей (n, k): ";
        cin >> n >> k;
        if (n > 0 && k >= 0) {
            break;
        }
        cout << "Количество кандидатов и избирателей должно быть больше 0." << endl;
    }

    map<string, int> candidates;
    cout << "Введите имена кандидатов: ";
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        candidates[name] = 0;
    }

    map<string, vector<string>> voters;
    cout << "Ввеедите имена изберателей и их голоса (имя голос1 голос2 ...): " << endl;
    for (int i = 0; i < k; i++) {
        cout << "Избиратель " << i + 1 << ": ";

        string name;
        string vote;
        vector<string> votes;
        cin >> name;
        
        for (int i = 0; i < n; i++) {
            while (true) {
                cin >> vote;
                if (candidates.find(vote) != candidates.end()) {
                    votes.push_back(vote);
                    break;
                } else {
                    cout << "Кандидат " << vote << " не найден. Попробуйте снова." << endl;
                }
            }
        }
        voters[name] = votes;
    }

    string winnerBord = bordaMethod(candidates, voters);
    if (winnerBord == "NONE") {
        cout << "Победитель по методу Борда не выявлен." << endl;
    } else {
        cout << "Победитель по методу Борда: " << winnerBord << endl;
    }

    string winnerCondorcet = condorcetMethod(candidates, voters);
    if (winnerCondorcet == "NONE") {
        cout << "Победитель по методу Кондорсе не выявлен." << endl;
    } else {
        cout << "Победитель по методу Конкордета: " << winnerCondorcet << endl;
    }

    if (winnerBord != winnerCondorcet) {
        cout << "\nПобедители по разным алгоритмам различаются." << endl;
    }
}