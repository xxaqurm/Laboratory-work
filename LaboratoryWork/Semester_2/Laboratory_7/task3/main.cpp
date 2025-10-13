/* Вариант 1 */
#include <iostream>

using namespace std;
using ll = long long;

void findExpression(int pos, ll current, ll prev, string expr, int target) {
    /* Рекурсивно находит решения для заданного m */
    if (pos == 10) {
        if (current == target) {
            cout << expr << " = " << target << endl;
        }
        return;
    }

    string numStr = "";
    for (int i = pos; i <= 9; i++) {
        numStr += to_string(i);
        ll num = stoll(numStr);
        
        if (pos == 1) {
            findExpression(i + 1, num, num, numStr, target);
        } else {
            findExpression(i + 1, current + num, num, expr + "+" + numStr, target);
            findExpression(i + 1, current - num, -num, expr + "-" + numStr, target);
        }
    }
}

int main() {
    int m;
    cout << "Введите свое m: ";
    cin >> m;

    findExpression(1, 0, 0, "", m);
}