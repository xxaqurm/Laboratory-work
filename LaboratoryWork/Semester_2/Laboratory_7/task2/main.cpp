/* Вариатн 7 */
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

int my_factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

void generate_permutations(vector<int>& nums, int start, vector<vector<int>>& result) {
    if (start == nums.size()) {
        result.push_back(nums);
        return;
    }
    for (int i = start; i < nums.size(); ++i) {
        swap(nums[start], nums[i]);
        generate_permutations(nums, start + 1, result);
        swap(nums[start], nums[i]);
    }
}

vector<vector<int>> get_permutations(int n, vector<int> nums) {
    vector<vector<int>> result;
    generate_permutations(nums, 0, result);
    sort(result.begin(), result.end());
    return result;
}

int main() {
    cin.exceptions(ios::failbit);

    int n = 0, k = 0;

    while (true) {
        cout << "Введите свои n, k: ";        
        try {
            cin >> n >> k;
            if (n < 0 || k < 0 || k > my_factorial(n)) {
                throw invalid_argument("n и k должны быть неотрицательными, а k не может превышать n!");
            }
            break;
        } catch (ios::failure& e) {
            cout << "Ошибка ввода: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (invalid_argument& e) {
            cout << "Ошибка: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    vector<int> nums;
    for (int i = 0; i < n; i++) {
        nums.push_back(i + 1);
    }

    vector<int> result;
    vector<vector<int>> permutations;

    permutations = get_permutations(k, nums);

    cout << "Your permutation: " << endl;
    for (auto& num : permutations[k - 1]) {
        cout << num << " ";
    }
    cout << "\n\n";

    cout << "All permutations: " << endl;
    for (auto& perm : permutations) {
        for (auto& num : perm) {
            cout << num << " ";
        }
        cout << endl;
    }
}
