package main

import (
	"fmt"
	"math"
)

func f(x float64) float64 {
	return x*x - 3*math.Sin(x)
}

func df(x float64) float64 {
	return 2*x - 3*math.Cos(x)
}

func ddf(x float64) float64 {
	return 2 + 3*math.Sin(x)
}

func findMinAbsDerivative(a, b float64) float64 {
	m := math.Abs(df(a))
	for x := a; x <= b; x += 1e-4 {
		val := math.Abs(df(x))
		if val < m {
			m = val
		}
	}
	return m
}

func findMaxAbsDerivative(a, b float64) float64 {
	M := math.Abs(df(a))
	for x := a; x <= b; x += 1e-4 {
		val := math.Abs(df(x))
		if val > M {
			M = val
		}
	}
	return M
}

func chordMethod(a, b, eps float64) {
	fmt.Println("N\tx_prev\tx_next\t|x_next - x_prev|")
	x := (a + b) / 2

	var xPrev, xNext float64
	iters := 0

	if ddf(x)*f(a) > 0 {
		xPrev = b
		for {
			xNext = xPrev - (f(xPrev)*(xPrev-a))/(f(xPrev)-f(a))
			M := findMaxAbsDerivative(a, b)
			m := findMinAbsDerivative(a, b)
			iters++
			fmt.Printf("%d\t%.4f\t%.4f\t%.4f\n", iters, xPrev, xNext, math.Abs(xNext-xPrev))
			if ((M - m) / m) * math.Abs(xNext-xPrev) <= eps {
				return
			}
			xPrev = xNext
		}
	} else {
		xPrev = a
		for {
			xNext = xPrev - (f(xPrev)*(b-xPrev))/(f(b)-f(xPrev))
			M := findMaxAbsDerivative(a, b)
			m := findMinAbsDerivative(a, b)
			iters++
			fmt.Printf("%d\t%.4f\t%.4f\t%.4f\n", iters, xPrev, xNext, math.Abs(xNext-xPrev))
			if ((M - m) / m) * math.Abs(xNext-xPrev) <= eps {
				return
			}
			xPrev = xNext
		}
	}
}

func findInitialGuess(a, b float64) float64 {
	for x := a; x <= b; x += 1e-4 {
		if f(x)*ddf(x) > 0 {
			return x
		}
	}
	return a
}

func newtonMethod(x, eps float64) {
	fmt.Println("N\tx_prev\tx_next\t|x_next - x_prev|")
	var xPrev float64
	iters := 0
	for {
		xPrev = x
		x = xPrev - f(xPrev)/df(xPrev)
		iters++
		fmt.Printf("%d\t%.4f\t%.4f\t%.4f\n", iters, xPrev, x, math.Abs(x-xPrev))
		if math.Abs(x - xPrev) < eps {
			return
		}
	}
}

func phiPositive(x float64) float64 {
	return math.Sqrt(3 * math.Sin(x))
}

func phiNegative(x float64) float64 {
	return math.Asin(x * x / 3)
}

func simpleIteration(x0, eps float64, positive bool) {
	fmt.Println("N\tx_prev\tx_next\t|x_next - x_prev|")
	x := x0
	var xPrev float64
	iters := 0

	for {
		xPrev = x
		if positive {
			x = phiPositive(xPrev)
		} else {
			x = phiNegative(xPrev)
		}
		iters++
		fmt.Printf("%d\t%.4f\t%.4f\t%.4f\n", iters, xPrev, x, math.Abs(x - xPrev))
		if math.Abs(x - xPrev) < eps {
			break
		}
	}
}
