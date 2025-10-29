#include <iostream>
#include <string>
#include <cstdint>
#include "../../include/stack.hpp"

using namespace std;

bool isSpace(char c) {
    return c == ' ';
}

bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

bool isOpeningBracket(char c) {
    return c == '(';
}

bool isClosingBracket(char c) {
    return c == ')';
}

int64_t calculate(int64_t firstOperand, int64_t secondOperand, char op) {
    switch (op) {
        case '+':
            return firstOperand + secondOperand;
        case '-':
            return firstOperand - secondOperand;
        case '*':
            return firstOperand * secondOperand;
    }
    return 0;
}

int64_t getPriority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*') {
        return 2;
    }
    return 0;
}

void arithmeticExpression() {
    cout << "Введите свое арифметическое выражение: ";

    string expression;
    getline(cin, expression);

    Stack<char> operators;
    Stack<int64_t> operands;

    for (int i = 0; i < expression.length();) {
        char currentChar = expression[i];
        
        if (isSpace(currentChar)) {
            i++;
            continue;
        }

        if (isDigit(currentChar)) { 
            int64_t currentNum = 0;
            while (i < expression.length() && isDigit(expression[i])) {
                currentNum = currentNum * 10 + (expression[i] - '0');
                i++;
            }
            operands.Push(currentNum);
            continue;
        }

        if (isOpeningBracket(currentChar)) {
            operators.Push(currentChar);
            i++;
            continue;
        }

        if (isClosingBracket(currentChar)) {
            while (!operators.Empty() && operators.Top() != '(') {
                if (operands.Empty()) {
                    throw runtime_error("[ ERROR ] Missing operand!");
                }

                int64_t secondOperand = operands.Top();
                operands.Pop();
                
                if (operands.Empty()) {
                    throw runtime_error("[ ERROR ] Missing operand!");
                }
                
                int64_t firstOperand = operands.Top();
                operands.Pop();

                char currentOperator = operators.Top();
                operators.Pop();

                operands.Push(calculate(firstOperand, secondOperand, currentOperator));
            }

            if (operators.Empty()) {
                throw runtime_error("[ ERROR ] Opening bracket is missing!");
            }

            operators.Pop();
            i++;
            continue;
        }

        if (currentChar == '+' || currentChar == '-' || currentChar == '*') {
            while (!operators.Empty() && getPriority(operators.Top()) >= getPriority(currentChar)) {
                char op = operators.Top();
                operators.Pop();

                if (operands.Empty()) {
                    throw runtime_error("[ ERROR ] Missing operand!");
                }

                int64_t secondOperand = operands.Top();
                operands.Pop();

                if (operands.Empty()) {
                    throw runtime_error("[ ERROR ] Missing operand!");
                }

                int64_t firstOperand = operands.Top();
                operands.Pop();

                operands.Push(calculate(firstOperand, secondOperand, op));
            }
            operators.Push(currentChar);
            i++;
            continue;
        }

        throw runtime_error("[ ERROR ] Invalid symbol in expression!");
    }

    while (!operators.Empty()) {
        char op = operators.Top();
        operators.Pop();

        if (operands.Empty()) {
            throw runtime_error("[ ERROR ] Missing operand!");
        }

        int64_t secondOperand = operands.Top();
        operands.Pop();

        if (operands.Empty()) {
            throw runtime_error("[ ERROR ] Missing operand!");
        }

        int64_t firstOperand = operands.Top();
        operands.Pop();

        operands.Push(calculate(firstOperand, secondOperand, op));
    }

    if (operands.Empty()) {
        throw runtime_error("[ ERROR ] Expression is empty!");
    }

    cout << "Значение выражения: " << operands.Top() << endl;
}