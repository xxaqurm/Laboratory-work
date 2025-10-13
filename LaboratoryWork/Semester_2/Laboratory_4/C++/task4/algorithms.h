#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <string>
#include <map>

using namespace std;

string bordaMethod(map<string, int> candidates, map<string, vector<string>> voters);
string condorcetMethod(map<string, int> candidates, map<string, vector<string>> voters);

#endif