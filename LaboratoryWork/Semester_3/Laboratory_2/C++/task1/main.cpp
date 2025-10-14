#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

bool isDigit(char sym) {
    return (sym >= '0' && sym <= '9');
}

bool isOperator(char sym) {
    return (sym == '+' || sym == '-' || sym == '*');
}

long performOp(long num1, long num2, char op) {
    switch(op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
    }
}

long evaluateExpression(const string expression) {
    stack<long> nums;
    stack<char> ops;

    for (size_t i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') {
            continue;
        } else if (expression[i] == '(') {
            ops.push(expression[i]);
        } else if (isDigit((expression[i]))) {
            long currentNum = 0;
            while (i < expression.length() && isDigit(expression[i])) {
                currentNum *= 10;
                currentNum += expression[i] - '0';
                i++;
            }
            nums.push(currentNum);
            i--;
        } else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                long num1 = nums.top();
                nums.pop();
                long num2 = nums.top();
                nums.pop();
                char op = ops.top();
                ops.pop();
                nums.push(performOp(num1, num2, op));
            }
        }
    }
}

int main() {
    string expression;
    cout << "Enter your expression: ";
    getline(cin, expression);
    

    try {
        long res = evaluateExpression(expression);
        cout << "Result: " << res << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}