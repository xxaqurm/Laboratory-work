#include <random>
#include <vector>
#include <locale>
#include <iostream>
#include "programs.h"

using namespace std;

vector<double> genDoubleVector() {
    /* Генерирует массив со случайными дробными значениями [-100, 100]*/
    knuth_b gen;
    gen.seed();

    uniform_int_distribution<int> distInt(10, 1000);
    uniform_real_distribution<double> distDouble(-100.0, 100.0);

    vector<double> arr(10);
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = distDouble(gen);
    }

    return arr;
}

vector<int> genIntVector() {
    /* Генерирует массив со случайными целыми значениями [-1000, 1000] */
    knuth_b gen;
    gen.seed();

    uniform_int_distribution<int> lengthArr(10, 1000);
    uniform_int_distribution<int> elmsVal(-1000, 1000);

    vector<int> arr(lengthArr(gen));
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = elmsVal(gen);
    }

    return arr;
}

pair<double, double> processPosNeg(vector<double> arr) {  // {sum, mult}
    /* Вычисляет произведение отрицательных и сумму положительных
     элементов до максимального элемента данного массива*/
    double maxElement = arr[0];
    for (auto elm : arr) {
        if (elm > maxElement) {
            maxElement = elm;
        }
    }
    cout << "Максимальный элемент массива: " << maxElement << endl;

    double sumPositive = 0;
    double multNegative = 1;

    for (auto elm : arr) {
        if (elm == maxElement) {
            break;
        }
        if (elm > 0) {
            sumPositive += elm;
        } else if (elm < 0) {
            multNegative *= elm;
        }
    }
    return {sumPositive, multNegative};
}

void swapCase(string& str) {
    /* Изменяет регистры строки на противоположный */
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = 'a' + (str[i] - 'A');
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = 'A' + (str[i] - 'a');
        }
    }
}

int countGreaterThanNeighbors(vector<double> arr) {
    /* Подсчитывает количество элементов, которые больше соседнего */
    int count = 0;
    for (int i = 1; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
            count++;
        }
    }
    return count;
}

void reverseArray(vector<int>& arr) {
    /* Переворачивает массив */
    int n = arr.size();
    for (int i = 0; i < n / 2; i++) {
        swap(arr[i], arr[n - i - 1]);
    }
}

vector<int> extractDigits(int num) {
    /* Переводт число в массив */
    num = abs(num);
    vector<int> digits;
    while (num != 0) {
        digits.push_back(num % 10);
        num /= 10;
    }

    return digits;
}

void arrayMixing(vector<int>& arr) {
    /* Перемешивает цифры чисел массива */
    knuth_b gen;
    gen.seed();


    for (int i = 0; i < arr.size(); i++) {
        vector<int> digits = extractDigits(arr[i]);
        int sign = arr[i] > 0 ? 1 : -1;

        uniform_int_distribution<int> index(0, digits.size() - 1);
        uniform_int_distribution<int> cycles(7, 30);
        for (int i = 0; i < cycles(gen); i++) {
            int index1 = index(gen);
            int index2 = index(gen);
            swap(digits[index1], digits[index2]);
        }
        
        int newNum = 0;
        for (auto& elm : digits) {
            newNum = newNum * 10 + elm;
        }
        newNum *= sign;
        arr[i] = newNum;
    }
}