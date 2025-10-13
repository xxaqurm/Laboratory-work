#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;


double f(double x) {
    return x * x - 3 * sin(x);
}

double df(double x) {
    return 2 * x - 3 * cos(x);
}

double ddf(double x) {
    return 2 + 3 * sin(x);
}

double find_min_abs_derivative(double a, double b) {
    double m = fabs(df(a));
    for (double x = a; x <= b; x += 1e-4) {
        double val = fabs(df(x));
        if (val < m) m = val;
    }
    return m;
}

double find_max_abs_derivative(double a, double b) {
    double M = fabs(df(a));
    for (double x = a; x <= b; x += 1e-4) {
        double val = fabs(df(x));
        if (val > M) M = val;
    }
    return M;
}

void chord_method(double a, double b, double eps) {
    cout << "N\tx_prev\tx_next\t|x_next - x_prev|" << endl;
    double x_prev, x_next;
    
    double x = (a + b) / 2;
    if (ddf(x) * f(a) > 0) {
        x_prev = b;
        int iters = 0;
        while (true) {
            x_next = x_prev - (f(x_prev) * (x_prev - a)) / (f(x_prev) - f(a));
            
            double M = find_max_abs_derivative(a, b);
            double m = find_min_abs_derivative(a, b);
            cout << fixed << setprecision(4) << ++iters << "\t" << x_prev << "\t" << x_next << "\t" << fabs(x_next - x_prev) << endl;
            if (((M - m) / m) * fabs(x_next - x_prev) <= eps) {
                return;
            }
            x_prev = x_next;
        }
    } else {
        x_prev = a;
        int iters = 0;
        while (true) {
            x_next = x_prev - (f(x_prev) * (b - x_prev)) / (f(b) - f(x_prev));

            double M = find_max_abs_derivative(a, b);
            double m = find_min_abs_derivative(a, b);
            cout << fixed << setprecision(4) << ++iters << "\t" << x_prev << "\t" << x_next << "\t" << fabs(x_next - x_prev) << endl;
            if (((M - m) / m) * fabs(x_next - x_prev) <= eps) {
                return;
            }
            x_prev = x_next;
        }
    }
}

double findInitialGuess(double a, double b) {
    for (double x = a; x <= b; x += pow(10, -4)) {
        if (f(x) * ddf(x) > 0) {
            return x;
        }
    }
}

void newton_method(double x, double eps) {
    cout << "N\tx_prev\tx_next\t|x_next - x_prev|" << endl;
    double x_prev;
    int iters = 0;
    do {
        x_prev = x;
        x = x_prev - f(x_prev) / df(x_prev);
        cout << fixed << setprecision(4) << ++iters << "\t" << x_prev << "\t" << x << "\t" << fabs(x - x_prev) << endl;
        if (fabs(x - x_prev) < eps) {
            return;
        }
    } while (fabs(x - x_prev) >= eps);
}

double phiPositive(double x) {
    return sqrt(3 * sin(x));
}

double phiNegative(double x) {
    return asin(pow(x, 2) / 3);
}

void simpleIteration(double x0, double eps, bool positive) {
    cout << "N\tx_prev\tx_next\t|x_next - x_prev|" << endl;
    
    double x = x0;
    double x_prev;

    int iters = 0;
    if (positive) {
        do {
            x_prev = x;
            x = phiPositive(x_prev);
            cout << fixed << setprecision(4) << ++iters << "\t" << x_prev << "\t" << x << "\t" << fabs(x - x_prev) << endl;
        } while (fabs(x - x_prev) > eps);
    } else {
        do {
            x_prev = x;
            x = phiNegative(x_prev);
            cout << fixed << setprecision(4) << ++iters << "\t" << x_prev << "\t" << x << "\t" << fabs(x - x_prev) << endl;
    } while (fabs(x - x_prev) > eps);
    }
    
}