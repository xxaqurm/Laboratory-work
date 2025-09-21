package main

import (
	"fmt"
	"math"
	"math/rand"
	"strings"
	"time"
)

func genDoubleVector() []float64 {
	rand.Seed(time.Now().UnixNano())
	arr := make([]float64, 10)
	for i := range arr {
		arr[i] = rand.Float64()*200 - 100 // [-100, 100]
	}
	return arr
}

func genIntVector() []int {
	rand.Seed(time.Now().UnixNano())
	length := rand.Intn(991) + 10 // [10, 1000]
	arr := make([]int, length)
	for i := range arr {
		arr[i] = rand.Intn(2001) - 1000 // [-1000, 1000]
	}
	return arr
}

func processPosNeg(arr []float64) (float64, float64) {
	maxEl := arr[0]
	for _, v := range arr {
		if v > maxEl {
			maxEl = v
		}
	}
	fmt.Println("Максимальный элемент массива:", maxEl)

	sumPos := 0.0
	multNeg := 1.0
	for _, v := range arr {
		if v == maxEl {
			break
		}
		if v > 0 {
			sumPos += v
		} else if v < 0 {
			multNeg *= v
		}
	}
	return sumPos, multNeg
}

func swapCase(s string) string {
	var result strings.Builder
	for _, ch := range s {
		if ch >= 'a' && ch <= 'z' {
			result.WriteRune(ch - ('a' - 'A'))
		} else if ch >= 'A' && ch <= 'Z' {
			result.WriteRune(ch + ('a' - 'A'))
		} else {
			result.WriteRune(ch)
		}
	}
	return result.String()
}

func countGreaterThanNeighbors(arr []float64) int {
	count := 0
	for i := 1; i < len(arr)-1; i++ {
		if arr[i] > arr[i-1] && arr[i] > arr[i+1] {
			count++
		}
	}
	return count
}

func extractDigits(num int) []int {
	num = int(math.Abs(float64(num)))
	var digits []int
	for num > 0 {
		digits = append(digits, num%10)
		num /= 10
	}
	return digits
}

func arrayMixing(arr *[]int) {
	rand.Seed(time.Now().UnixNano())
	for i := 0; i < len(*arr); i++ {
		digits := extractDigits((*arr)[i])
		if len(digits) <= 1 {
			continue
		}
		sign := 1
		if (*arr)[i] < 0 {
			sign = -1
		}

		cycles := rand.Intn(24) + 7 // [7, 30]
		for j := 0; j < cycles; j++ {
			idx1 := rand.Intn(len(digits))
			idx2 := rand.Intn(len(digits))
			digits[idx1], digits[idx2] = digits[idx2], digits[idx1]
		}

		newNum := 0
		for _, d := range digits {
			newNum = newNum*10 + d
		}
		(*arr)[i] = newNum * sign
	}
}
