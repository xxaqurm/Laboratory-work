#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cout << "Введите П и В: ";
    cin >> n >> m;

    cout << "Введите " << n << " целых чисел: ";
    vector<int> a(n);
    for (int &x : a) cin >> x;

    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + a[i];
    }

    vector<int> dp(n + 1, 0);

    for (int i = n - 1; i >= 0; i--) {
        int best = -1000000000;
        for (int k = 1; k <= m && i + k <= n; k++) {
            int sum = prefix[i + k] - prefix[i];
            best = max(best, sum - dp[i + k]);
        }
        dp[i] = best;
    }

    if (dp[0] > 0) {
        cout << "Победил Паша!" << endl;
    } else if (dp[0] < 0) {
        cout << "Победила Вика!" << endl;
    } else {
        cout << "Ничья!" << endl;
    }
}
