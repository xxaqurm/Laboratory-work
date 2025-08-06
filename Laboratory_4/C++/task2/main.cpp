#include <iostream>
#include <algorithm>
#include <vector>
#include "programs.h"

using namespace std;

int main() {
    cout << "Сгенерированный массив с случайными дробными числами: " << endl;
    vector<double> doubleArr = genDoubleVector();
    for (auto& elm : doubleArr) {
        cout << elm << " ";
    }
    cout << "\n\n";

    pair<double, double> result = processPosNeg(doubleArr);
    cout << "Найдем сумму положительных и произведение отрицательных элементов массива, расположенных до максимального элемента." << endl;
    cout << "Сумма положительных элементов: " << result.first << endl;
    cout << "Произведение отрицательных элементов: " << result.second << endl << endl;

    cout << "Введите строку для изменения регистра: ";
    string str;
    getline(cin, str);
    swapCase(str);
    cout << "Строка с измененным регистром: " << str << endl << endl;

    cout << "Количество элементов, которые больше соседнего: ";
    cout << countGreaterThanNeighbors(doubleArr) << endl;

    cout << "\nСгенерированный массив с случайными целыми числами: " << endl;
    int sum = 0;
    vector<int> intArr = genIntVector();
    for (auto& elm : intArr) {
        sum += elm;
        cout << elm << " ";
    }
    cout << endl << endl;
    cout << "Сумма элементов этого массива: " << sum << endl << endl;

    arrayMixing(intArr);
    cout << "Перемешанный массив: " << endl;
    for (auto& elm : intArr) {
        cout << elm << " ";
    }
    cout << endl << endl;

    sort(intArr.begin(), intArr.end());
    int sumSorted = 0;
    cout << "Отсортированный массив: " << endl;
    for (auto& elm : intArr) {
        sumSorted += elm;
        cout << elm << " ";
    }
    cout << endl << endl;

    cout << "Сумма измененного массива: " << sumSorted << endl;
    cout << "Сумма исходного массива: " << sum << endl;
    cout << "Разница между суммами: " << sumSorted - sum << endl;
}