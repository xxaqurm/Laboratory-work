package main

import (
	"fmt"
	"math"
)

func main() {
	fmt.Println("Метод хорд:")
	xMax := 2.0
	xMin := -2.0

	b := xMax
	a := b - 0.3
	eps := math.Pow(10, -4)

	for a >= xMin {
		if f(a)*f(b) < 0 {
			chordMethod(a, b, eps)
		}
		b = a
		a -= 0.3
	}

	fmt.Println("\nМетод Ньютона:")
	b = xMax
	a = b - 0.3
	for a >= xMin {
		if f(a)*f(b) < 0 {
			initialGuess := findInitialGuess(a, b)
			newtonMethod(initialGuess, eps)
		}
		b = a
		a -= 0.3
	}

	fmt.Println("\nМетод простых итераций:")
	simpleIteration(1.5, eps, true)
	simpleIteration(0.5, eps, false)
}
