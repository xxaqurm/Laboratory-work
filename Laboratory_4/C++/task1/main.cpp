#include <iostream>
#include <cmath>
#include <iomanip>
#include "utils.h"

using namespace std;

int main() {
    cout << "Метод хорд:" << endl;
    double x_max = 2;
    double x_min = -2;

    double b = x_max;
    double a = b - 0.3;
    double eps = pow(10, -4);
    
    while (a >= x_min) {
        if (f(a) * f(b) < 0) {  // интервал с корнем
            chord_method(a, b, eps);
        }
        b = a;
        a -= 0.3;
    }

    cout << "\nМетод Ньютона:" << endl;
    b = x_max;
    a = b - 0.3;
    while (a >= x_min) {
        if (f(a) * f(b) < 0) {
            double initialGuess = findInitialGuess(a, b);
            newton_method(initialGuess, eps);
        }
        b = a;
        a -= 0.3;
    }

    cout << "\nМетод простых итераций:" << endl;
    double x0 = 1.5;
    simpleIteration(x0, eps, true);

    x0 = 0.5;
    simpleIteration(x0, eps, false);
}