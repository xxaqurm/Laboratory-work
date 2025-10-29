package tasks

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"unicode"
)

// Stack — простая реализация стека
type Stack[T any] struct {
	data []T
}

func (s *Stack[T]) Push(val T) {
	s.data = append(s.data, val)
}

func (s *Stack[T]) Pop() (T, error) {
	if len(s.data) == 0 {
		var zero T
		return zero, errors.New("stack is empty")
	}
	val := s.data[len(s.data)-1]
	s.data = s.data[:len(s.data)-1]
	return val, nil
}

func (s *Stack[T]) Top() (T, error) {
	if len(s.data) == 0 {
		var zero T
		return zero, errors.New("stack is empty")
	}
	return s.data[len(s.data)-1], nil
}

func (s *Stack[T]) Empty() bool {
	return len(s.data) == 0
}

// --- Вспомогательные функции ---

func isDigit(r rune) bool {
	return unicode.IsDigit(r)
}

func isOpeningBracket(r rune) bool {
	return r == '('
}

func isClosingBracket(r rune) bool {
	return r == ')'
}

func getPriority(op rune) int {
	switch op {
	case '+', '-':
		return 1
	case '*':
		return 2
	default:
		return 0
	}
}

func calculate(a, b int64, op rune) int64 {
	switch op {
	case '+':
		return a + b
	case '-':
		return a - b
	case '*':
		return a * b
	default:
		return 0
	}
}

// --- Основная функция вычисления выражения ---

func ArithmeticExpression() {
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Введите свое арифметическое выражение: ")
	expr, _ := reader.ReadString('\n')

	var operators Stack[rune]
	var operands Stack[int64]

	runes := []rune(expr)

	for i := 0; i < len(runes); {
		ch := runes[i]

		if unicode.IsSpace(ch) {
			i++
			continue
		}

		if isDigit(ch) {
			var num int64
			for i < len(runes) && isDigit(runes[i]) {
				num = num*10 + int64(runes[i]-'0')
				i++
			}
			operands.Push(num)
			continue
		}

		if isOpeningBracket(ch) {
			operators.Push(ch)
			i++
			continue
		}

		if isClosingBracket(ch) {
			for !operators.Empty() {
				top, _ := operators.Top()
				if top == '(' {
					break
				}
				operators.Pop()

				b, err2 := operands.Pop()
				a, err1 := operands.Pop()
				if err1 != nil || err2 != nil {
					fmt.Println("[ ERROR ] Missing operand!")
					return
				}

				res := calculate(a, b, top)
				operands.Push(res)
			}

			if operators.Empty() {
				fmt.Println("[ ERROR ] Opening bracket is missing!")
				return
			}
			operators.Pop() // удалить '('
			i++
			continue
		}

		if ch == '+' || ch == '-' || ch == '*' {
			for !operators.Empty() {
				top, _ := operators.Top()
				if getPriority(top) < getPriority(ch) {
					break
				}
				operators.Pop()

				b, err2 := operands.Pop()
				a, err1 := operands.Pop()
				if err1 != nil || err2 != nil {
					fmt.Println("[ ERROR ] Missing operand!")
					return
				}

				operands.Push(calculate(a, b, top))
			}
			operators.Push(ch)
			i++
			continue
		}

		fmt.Println("[ ERROR ] Invalid symbol in expression!")
		return
	}

	for !operators.Empty() {
		op, _ := operators.Pop()
		b, err2 := operands.Pop()
		a, err1 := operands.Pop()
		if err1 != nil || err2 != nil {
			fmt.Println("[ ERROR ] Missing operand!")
			return
		}
		operands.Push(calculate(a, b, op))
	}

	if operands.Empty() {
		fmt.Println("[ ERROR ] Expression is empty!")
		return
	}

	res, _ := operands.Top()
	fmt.Printf("Значение выражения: %d\n", res)
}