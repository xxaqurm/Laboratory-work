#include "../../include/SetPartition.hpp"

bool allUsed(const DynamicArray<bool>& used) {
    for (size_t i = 0; i < used.size(); i++) {
        if (!used[i]) {
            return false;
        }
    }
    return true;
}

bool findCombinations(DynamicArray<int>& s, DynamicArray<DynamicArray<int>>& result, DynamicArray<bool>& used, int target, DynamicArray<int>& currentSubset, int current_sum, int start) {
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
                DynamicArray<int> newSubset;
                if (findCombinations(s, result, used, target, newSubset, 0, 0))
                    return true;
                result.pop();
            } else {
                if (findCombinations(s, result, used, target, currentSubset, current_sum + s[i], i + 1))
                    return true;
            }

            currentSubset.pop();
            used[i] = false;
        }
    }

    return false;
}

void setPartition() {
    int sz;
    cout << "Введите длину множества: ";
    cin >> sz;

    cout << "Введите элементы множества: ";
    DynamicArray<int> s(sz);
    for (size_t i = 0; i < sz; i++) {
        cin >> s[i];
    }

    int total_sum = 0;
    for (size_t i = 0; i < sz; i++) {
        total_sum += s[i];
    }

    DynamicArray<DynamicArray<int>> result;
    bool combinationExists = false;
    for (size_t k = 2; k <= sz; k++) {
        if (total_sum % k != 0) {
            continue;
        }

        int target = total_sum / k;
        DynamicArray<bool> used(sz, false);
        result.clear();
        DynamicArray<int> currentSubset;

        if (findCombinations(s, result, used, target, currentSubset, 0, 0)) {
            cout << "Разделение найдено (сумма подмножеств = " << target << "):\n";
            for (size_t i = 0; i < result.size(); i++) {
                cout << "{ ";
                for (size_t j = 0; j < result[i].size(); j++) {
                    cout << result[i][j] << " ";
                }
                cout << "}\n";
                combinationExists = true;
            }
        }
        
        if (!combinationExists) {
            cout << "Комбинации не найдены" << endl;
        }
    }
}