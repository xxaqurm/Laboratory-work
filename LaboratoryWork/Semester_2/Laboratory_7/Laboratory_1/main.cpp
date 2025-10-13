#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;


double findTriangleSide(double x1, double x2, double y1, double y2) {
	/* Функция для нахождения длины стороны треугольника */
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double findTrianglePerimeter(double s1, double s2, double s3) {
	/* Функция для нахождения периметра треугольника */
	return s1 + s2 + s3;
}

double findTriangleArea(double sp, double s1, double s2, double s3) {
	/* Функция для нахождения площади треугольника */
	return sqrt(sp * (sp - s1) * (sp - s2) * (sp - s3));
}

bool isIsoscelesTriangle(double s1, double s2, double s3) {
	/* Функция для проверки треугольника на равнобедренность */
	return (s1 == s2 || s1 == s3 || s2 == s3);
}

int main(void) {
        vector<vector <double>> points(3, vector<double> (2));
        for (int i = 0; i < 3; i++) { // считаем пользовательский ввод
		cout << "Введите координаты точки " << i + 1 << " (x, y): ";
		cin >> points[i][0] >> points[i][1]; 
        }

	if (points[0] == points[1] || points[0] == points[2] || points[1] == points[2]) {
		cout << "Треугольник не может быть задан данными координатами, некоторые точки совпадают." << endl;
		return 1;
	}

	double k = (points[1][1] - points[0][1]) / (points[1][0] - points[0][0]);
        double b = points[0][1] - k * points[0][0];

        if (points[2][1] == k * points[2][0]) {
                cout << "Треугольник не может быть задан данными координатами, точки лежат на одной прямой" << endl;
                return 2;
        }	

	// найдем длины сторон треугольника
        double side1 = findTriangleSide(points[0][0], points[1][0], points[0][1], points[1][1]);
        double side2 = findTriangleSide(points[0][0], points[2][0], points[0][1], points[2][1]);
        double side3 = findTriangleSide(points[1][0], points[2][0], points[1][1], points[2][1]);

	// найдем периметр, площадь, а также определим равнобедренность
        double perimeter = findTrianglePerimeter(side1, side2, side3);
        double semiPerim = perimeter / 2;
        double area = findTriangleArea(semiPerim, side1, side2, side3);

	bool isIsosceles = isIsoscelesTriangle(side1, side2, side3);

        cout << "\nПериметр равен: " << fixed << setprecision(2) << perimeter << endl;
	cout << "Площадь равна: " << fixed << setprecision(2) << area << endl;
        if (isIsosceles) cout << "Также, треугольник является равнобедренным." << endl;
        else cout << "Также, треугольник не является равнобедренным." << endl;
        
	return 0;
}
