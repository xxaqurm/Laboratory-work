#include <iostream>
#include <random>
#include <map>
#include "strategies.h"

using namespace std;

typedef bool (*Strategy)(int, vector<bool>, vector<bool>);
const vector<vector<int>> POINTS = {
    {4, 20}, 
    {0, 24}
};

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> cntRounds(100, 200);
    uniform_int_distribution<> algorithmNum(0, 2);

    map<int, string> algorithmNames = {
        {0, "every23"},
        {1, "grimTrigger"},
        {2, "titForTat"}
    };

    int firstAlgorithm = algorithmNum(gen);
    int secondAlgorithm = algorithmNum(gen);
    while (firstAlgorithm == secondAlgorithm) {
        secondAlgorithm = algorithmNum(gen);
    }

    int rounds = cntRounds(gen);
    
    cout << "Rounds: " << rounds << endl << endl;
    cout << "First algorithm: " << algorithmNames[firstAlgorithm] << endl;
    cout << "Second algorithm: " << algorithmNames[secondAlgorithm] << endl << endl;

    Strategy strategies[] = {
        every23,
        grimTrigger,
        titForTat
    };

    vector<bool> historyFirst, historySecond;

    int pointsFirst = 0;
    int pointsSecond = 0;
    for (int i = 0; i < rounds; i++) {
        bool moveFirst;
        bool moveSecond;

        moveFirst = strategies[firstAlgorithm](i + 1, historyFirst, historySecond);
        moveSecond = strategies[secondAlgorithm](i + 1, historySecond, historyFirst);

        historyFirst.push_back(moveFirst);
        historySecond.push_back(moveSecond);

        pointsFirst += POINTS[moveFirst][moveSecond];
        pointsSecond += POINTS[moveSecond][moveFirst];
    }

    if (pointsFirst > pointsSecond) {
        cout << "First algorithm win!" << endl;
    } else if (pointsFirst < pointsSecond) {
        cout << "Second algorithm wins!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }

    cout << "First algorithm points: " << pointsFirst << endl;
    cout << "Second algorithm points: " << pointsSecond << endl;
}