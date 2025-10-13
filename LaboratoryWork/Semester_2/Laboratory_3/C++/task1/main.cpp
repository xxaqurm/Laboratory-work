#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

void print_table(vector<pair<double, double>> points) {
    /* Выводит таблицу значений */
    const int cell_width = 5;
    string border = "+" + string(1, '-') + "+";

    for (int i = 0; i < (int)points.size(); i++) {
        border += string(cell_width, '-') + "+";
    }
    
    cout << border << endl;
    
    cout << "|" << setw(1) << "x";
    for (auto [x, y] : points) 
        cout << "|" << setw(cell_width) << fixed << setprecision(1) << x;
    cout << "|" << endl;

    cout << border << endl;

    cout << "|" << setw(1) << "y";
    for (auto [x, y] : points) 
        cout << "|" << setw(cell_width) << fixed << setprecision(1) << y;
    cout << "|" << endl;

    cout << border << endl;
}

int main(void) {
    // зададим значения по умолчанию
    double x_start = -10;
    double x_finish = 8;
    double dx = 0.5;
    bool change = false;
    
    cout << "Значения по умолчанию:\n" << "x начальное: " << x_start << "\nx конечное: " << x_finish << "\ndx: " << dx << endl;
    cout << "Хотите ли вы изменить значения по умолчанию? (1 - да / 0 - нет): ";
    cin >> change;

    if (change) {
        cout << "\nВведите x начальное, x конечное и dx (xs xf dx): ";
        cin >> x_start >> x_finish >> dx;
    }

    vector<pair<double, double>> xy_values;

    for (double x = x_start; x <= x_finish; x += dx) {
        double y = 0;
        if (x >= -10 && x <= -6) {  // окружность
            if (x == -8) {
                y = 0;
            } else {
                y = sqrt(4 - pow((x+8), 2)) - 2;
            }
        } else if (x > -6 && x <= 2) {  // наклонная прямая
            y = 0.5 * x + 1;
        } else if (x > 2 && x <= 6) {  // y = 0
            y = 0;
        } else if (x > 6 && x <= 8) {  // парабола
            y = pow((x - 6), 2);
        } else {
            y = 0;
        }
        xy_values.push_back({x, y});
    }
    print_table(xy_values);

    return 0;
}