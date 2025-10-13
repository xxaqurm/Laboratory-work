#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "algorithms.h"

using namespace std;

string bordaMethod(map<string, int> candidates, map<string, vector<string>> voters) {
    /* Реализация метода Борда */
    for (auto& voter : voters) {
        vector<string> votes = voter.second;
        for (int i = 0; i < votes.size(); i++) {
            candidates[votes[i]] += votes.size() - i - 1;
        }
    }

    int maxScore = 0;
    string winner;
    for (auto& candidate : candidates) {
        if (candidate.second > maxScore) {
            maxScore = candidate.second;
            winner = candidate.first;
        }
    }

    int cnt = 0;
    for (auto& candidate : candidates) {
        if (candidate.second == maxScore) {
            cnt++;
        }
    }

    if (cnt > 1) {
        return "NONE";
    }

    return winner;
}

int findIdx(vector<string> votes, string candidate) {
    for (int i = 0; i < votes.size(); i++) {
        if (votes[i] == candidate) {
            return i;
        }
    }
    return votes.size() - 1;
}

string condorcetMethod(map<string, int> candidates, map<string, vector<string>> voters) {
    for (const auto& candidateA : candidates) {
        string currentCandidate = candidateA.first;
        bool isCondorcetWinner = true;

        for (const auto& candidateB : candidates) {
            if (currentCandidate == candidateB.first) {
                continue;
            }

            int wins = 0;
            int losses = 0;

            for (const auto& voter : voters) {
                const vector<string> preferences = voter.second;
                
                size_t posA = findIdx(preferences, currentCandidate);
                size_t posB = findIdx(preferences, candidateB.first);
                
                if (posA < posB) {
                    wins++;
                } else {
                    losses++;
                }
            }

            if (wins <= losses) {
                isCondorcetWinner = false;
                break;
            }
        }

        // Если кандидат побеждает всех, возвращаем его как победителя
        if (isCondorcetWinner) {
            return currentCandidate;
        }
    }

    return "Нет победителя";
}
