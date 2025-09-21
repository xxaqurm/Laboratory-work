#include <iostream>
#include <cmath>

using namespace std;


bool is_prime(int a) {
    /* Проверяет, является ли число простым. */
    if (a < 2) return false;

    for (int i = 2; i <= (int)sqrt(a); i++) {
        if (a % i == 0) return false;
    }

    return true;
}


int calculateNthNum(int a) {
    /* Ищет N-й член последовательности. */
    int deviation = 1;
    int left_val = a;
    int right_val = a;
    
    while (true) {
        if (is_prime(left_val)) return a - left_val;
        else if (is_prime(right_val)) return a - right_val;
        left_val = a - deviation;   // ищем простое число слева от N
        right_val = a + deviation;  // ищем простое число справа от N
        deviation++;
    }
}


int main(void) {
    int n, Nth;
    cout << "Введите свое N: ";
    cin >> n;

    Nth = calculateNthNum(n);
    cout << "Найден N-й член ряда: " << Nth << endl;
}
