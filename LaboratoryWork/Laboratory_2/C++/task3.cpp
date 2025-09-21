#include <iostream>
#include <cmath>

using namespace std;


bool is_number(int a) {
    /* Проверяет, что это число, а не цифра. */
    return (a / 10 != 0);
}


int cnt_odd_digits(int a) {
    /* Считает количество нечетных цифр в числе. */
    int res = 0;
    a = abs(a);

    while (a > 0) {
        res += (a % 2);
        a /= 10;
    }
    return res;
}


int main(void) {
    int n;
    cout << "Введите количество чисел: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int num;
        cout << "Введите " << i + 1 << " число: ";
        cin >> num;

        int cnt_odd = 0;
        if (is_number(num)) {
            cnt_odd = cnt_odd_digits(num);
        } else {
            cout << num << " - это цифра!" << endl;
        }

        cout << "Количество нечетных цифр: " << cnt_odd << endl;
    }
}