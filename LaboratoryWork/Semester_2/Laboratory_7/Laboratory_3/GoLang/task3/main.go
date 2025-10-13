package main

import (
	"fmt"
	"math"
)

// computeSeriesSum вычисляет сумму ряда с заданными a и b
func computeSeriesSum(a, b int, iters int) float64 {
	sum := 0.0
	for n := 1; n <= iters; n++ {
		sum += math.Pow(float64(n), float64(a)) / math.Pow(float64(b), float64(n))
	}
	return sum
}

// isRational проверяет, является ли число рациональным в пределах точности eps
// Возвращает числитель, знаменатель и булев флаг (true, если рационально)
func isRational(x, eps float64) (numerator, denominator float64, rational bool) {
	numerator = 1
	denominator = 1
	iter := 0

	for iter < 100 {
		approx := numerator / denominator
		diff := math.Abs(x - approx)
		if diff < eps {
			return numerator, denominator, true
		}
		if approx < x {
			numerator++
		} else {
			denominator++
		}
		iter++
	}
	return numerator, denominator, false
}

func main() {
	var a, b int
	fmt.Print("Введите свои a и b: ")
	fmt.Scan(&a, &b)

	if b == 1 {
		fmt.Println("Infinity")
		return
	}

	total := computeSeriesSum(a, b, 1000)
	eps := math.Pow(10, -10)

	num, denom, rational := isRational(total, eps)

	if rational {
		fmt.Printf("%.0f / %.0f\n", num, denom)
	} else {
		fmt.Println("Irrational")
	}
}
