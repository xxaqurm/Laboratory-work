#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

vector<double> coffee(double Tk, double Tsr, double r, const vector<double> timeSteps) {
    /* Моделирует остывание кофе */
    vector<double> temperatures;
    for (double t : timeSteps) {
        double T = Tsr + (Tk - Tsr) * exp(-r * t);
        temperatures.push_back(T);
    }
    return temperatures;
}

void printResults(const vector<double>& timeSteps, const vector<double>& temperatures) {
    /* Выводит таблицу результатов */
    cout << "Результаты моделирования остывания кофе:\n";
    cout << "----------------------------------------\n";
    cout << "|  Время (мин)  |  Температура (°C)  |\n";
    cout << "----------------------------------------\n";
    
    for (size_t i = 0; i < timeSteps.size(); i++) {
        cout << "|" << setw(10) << timeSteps[i] << setw(7) << " |"
             << setw(14) << fixed << setprecision(2) << temperatures[i] << setw(8) << " |\n";
    }
    cout << "----------------------------------------\n";
}

int main() {
    int num_meas = 0;
    double r = 0;
    double Tk = 0;
    double Tsr = 0;
    
    cout << "Моделирование остывания кофе\n----------------------------\n";
    cout << "Введите начальную температуру кофе (в градусах цельсия): ";
    cin >> Tk;
    
    cout << "Введите температуру окружающей среды (в градусах цельсия): ";
    cin >> Tsr;
    
    cout << "Введите коэффициент охлаждения (0 < r < 1): ";
    cin >> r;
    
    cout << "Введите количество измерений: ";
    cin >> num_meas;
    
    vector<double> timeSteps(num_meas);
    cout << "Введите моменты времени для измерений (в минутах):\n";
    for (int i = 0; i < num_meas; i++) {
        cout << "Измерение " << i + 1 << ": ";
        cin >> timeSteps[i];
    }
    
    vector<double> temperatures = coffee(Tk, Tsr, r, timeSteps);
    printResults(timeSteps, temperatures);
}