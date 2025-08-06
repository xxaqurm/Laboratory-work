#ifndef UTILS
#define UTILS

#include <vector>

using namespace std;
using ull = unsigned long long;

vector<int> eratosthenesSieve(int limit = 500);
vector<pair<int, int>> factorize(ull num);
int modPow(ull a, ull exp, ull m);
int sizeNum(ull n);
void printTable(set<tuple<pair<ull, int>, bool>> data);

#endif