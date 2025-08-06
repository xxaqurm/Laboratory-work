#ifndef UTILS_H
#define UTILS_H

using namespace std;

double chord_method(double a, double b, double eps);
double f(double x);
void newton_method(double x, double eps);
double findInitialGuess(double a, double b);
void simpleIteration(double x0, double eps, bool positive);

#endif