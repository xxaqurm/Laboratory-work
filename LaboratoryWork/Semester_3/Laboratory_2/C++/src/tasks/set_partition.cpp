#include <iostream>
#include <vector>

using namespace std;

bool allUsed(const vector<bool>& used) {
    for (bool u : used)
        if (!u) return false;
    return true;
}

bool findCombinations(vector<int>& s, vector<vector<int>>& result, vector<bool>& used, int target, vector<int>& currentSubset, int current_sum, int start) {
    if (allUsed(used)) {
        if (currentSubset.empty())
            return true;
        else
            return false;
    }

    for (int i = start; i < s.size(); i++) {
        if (!used[i] && current_sum + s[i] <= target) {
            used[i] = true;
            currentSubset.push_back(s[i]);

            if (current_sum + s[i] == target) {
                result.push_back(currentSubset);
                vector<int> newSubset;
                if (findCombinations(s, result, used, target, newSubset, 0, 0))
                    return true;
                result.pop_back();
            } else {
                if (findCombinations(s, result, used, target, currentSubset, current_sum + s[i], i + 1))
                    return true;
            }

            currentSubset.pop_back();
            used[i] = false;
        }
    }

    return false;
}

void setPartition() {
    int n;
    cout << "Введите длину множества: ";
    cin >> n;

    cout << "Введите элементы множества: ";
    vector<int> s(n);
    for (int i = 0; i < n; i++)
        cin >> s[i];

    int total_sum = 0;
    for (int x : s)
        total_sum += x;

    vector<vector<int>> result;

    for (int k = 2; k <= n; k++) {
        if (total_sum % k != 0)
            continue;

        int target = total_sum / k;  // сумма каждого подмножества
        vector<bool> used(n, false);
        result.clear();
        vector<int> currentSubset;

        if (findCombinations(s, result, used, target, currentSubset, 0, 0)) {
            cout << "Разделение найдено (сумма подмножеств = " << target << "):\n";
            for (auto& subset : result) {
                cout << "{ ";
                for (int num : subset)
                    cout << num << " ";
                cout << "}\n";
            }
        }
    }

    //cout << "Не удалось найти такие подмножества" << endl;
}
//  4 10 5 1 3 7