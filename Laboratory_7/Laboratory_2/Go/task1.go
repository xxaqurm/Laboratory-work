package main

import (
	"fmt"
	"math"
)


func is_prime(a int) bool {
	/* Проверяет, является ли число простым. */
	if (a < 2) {
		return false
	}

	for i := 2; i <= int(math.Sqrt(float64(a))); i++ {
		if a % i == 0 {
			return false
		}
	}

	return true
}


func calculateNthNum (a int) int {
	/* Ищет N-й член последовательности. */
	deviation := 1
	left_val := a
	right_val := a

	for {
		if is_prime(left_val) {
			return a - left_val 
		} else if is_prime(right_val) {
			return a - right_val
		}
		left_val = a - deviation   // ищем простое число слева от N
		right_val = a + deviation  // ищем простое число справа от N
		deviation++
	}
}


func task1() {
	var n, Nth int

	fmt.Print("Введите свое N: ")
	fmt.Scan(&n)

	Nth = calculateNthNum(n)
	fmt.Println("Найдет N-й член ряда: ", Nth)
}