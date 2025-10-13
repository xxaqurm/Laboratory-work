#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using ll = long long;

double compute_series_sum(int a, int b, int iters=1000) {
    /*Находит сумму 1000 итераций*/
    double sum = 0;
    for (int n = 1; n <= iters; n++) {
        sum += pow(n, a) / pow(b, n);
    }
    return sum;
}

vector<double> is_rational(double x, double eps) {  // numerator , denominator , state
    /*Проверяет число на рациональность*/
    double denominator = 1;
    double numerator = 1;
    double difference = abs(x - (numerator / denominator));
    int iter = 0;

    while (iter != 100) {
        if (numerator / denominator < x) {
            numerator++;
        } else {
            denominator++;
        }
        difference = abs(x - (numerator / denominator));
        iter++;
        if (difference < eps) {
            return {numerator, denominator, 1};
        }
    }
    return {numerator, denominator, 0};
}

int main() {
    int a = 1;
    int b = 1;
    cout << "Введите свои a и b: ";
    cin >> a >> b;

    if (b == 1) {
        cout << "Infinity" << endl;
    } else {
        double total = compute_series_sum(a, b);
        double eps = pow(10, -10);

        vector<double> result = is_rational(total, eps);

        if (!result[2]) {
            cout << "Irrational" << endl;
        } else {
            cout << result[0] << " / " << result[1] << endl;
        }
    }
}