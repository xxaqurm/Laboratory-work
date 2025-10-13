package main

import (
	"fmt"
	"math"
)


func is_number(a int) bool {
	/* Проверяет, что это число, а не цифра. */
	return (a / 10 != 0)
}


func cnt_odd_digits(a int) int {
	/* Считает количество нечетных цифр в числе. */
	res := 0
	a = int(math.Abs(float64(a)))

	for a > 0 {
		res += a % 2
		a /= 10
	}
	return res
}


func task3() {
	var n int
	fmt.Print("Введите количество чисел: ")
	fmt.Scan(&n)

	for i := 0; i < n; i++ {
		var num int
		fmt.Print("Введите ", i + 1, " число: ")
		fmt.Scan(&num)

		cnt_odd := 0
		if is_number(num) {
			cnt_odd = cnt_odd_digits(num)
		} else {
			fmt.Println(num, " - это не цифра!")
		}

		fmt.Println("Количество нечетных цифр: ", cnt_odd)
	}
}