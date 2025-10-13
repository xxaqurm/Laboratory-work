#ifndef PROGRAMS_H
#define PROGRAMS_H

#include <vector>

using namespace std;

vector<double> genDoubleVector(void);
pair<double, double> processPosNeg(vector<double> arr);
void swapCase(string& str);
int countGreaterThanNeighbors(vector<double> arr);
vector<int> genIntVector(void);
void arrayMixing(vector<int>& arr);

#endif