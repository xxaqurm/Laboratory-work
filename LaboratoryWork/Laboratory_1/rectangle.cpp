#include <iostream>
#include <locale>
#include <cmath>

using namespace std;
 

double perimetr(double a, double b){
    return 2 * (a + b);
}

double ploshad(double a, double b){
    return a * b;
}

double diagonal(double a, double b){
    return sqrt(a*a + b*b);
}

int main(){
    double a, b;
    cout << "Введите стороны прямоугольника через пробел:" << endl;
    cin >> a >> b; 
    if (a <= 0 || b <= 0){
        cout << "Содержится отрицательное число/числа или сторона/стороны равны 0" << endl;
    }
    else {
        cout << "Периметр = " << perimetr(a, b) << " Площадь = " << ploshad(a, b) << " Диагональ = " << diagonal(a, b) << endl;
    }
    return 0;
}

