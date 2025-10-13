package utils

import (
	"fmt"
	"math"
)

type Pair struct {
	First  int
	Second int
}

func EratosthenesSieve(limit int) []int {
	isPrime := make([]bool, limit+1)
	for i := 2; i <= limit; i++ {
		isPrime[i] = true
	}

	for p := 2; p*p <= limit; p++ {
		if isPrime[p] {
			for i := p * p; i <= limit; i += p {
				isPrime[i] = false
			}
		}
	}

	primes := []int{}
	for i := 2; i <= limit; i++ {
		if isPrime[i] {
			primes = append(primes, i)
		}
	}
	return primes
}

func Factorize(num uint64) []Pair {
	primes := EratosthenesSieve(500)
	result := []Pair{}

	for _, prime := range primes {
		exponent := 0
		for num%uint64(prime) == 0 && num > 0 {
			exponent++
			num /= uint64(prime)
		}
		if exponent > 0 {
			result = append(result, Pair{prime, exponent})
		}
	}
	return result
}

func ModPow(a, exp, m uint64) uint64 {
	res := uint64(1)
	base := a % m
	for exp > 0 {
		if exp&1 == 1 {
			res = (res * base) % m
		}
		base = (base * base) % m
		exp >>= 1
	}
	return res
}

func SizeNum(n uint64) int {
	if n == 0 {
		return 0
	}
	return int(math.Log2(float64(n))) + 1
}

func PrintTable(data map[uint64][2]int) {
	colWidth := 15

	for k := range data {
		fmt.Printf("%-*v", colWidth, k)
	}
	fmt.Println()

	for _, v := range data {
		if v[1] == 1 {
			fmt.Printf("%-*v", colWidth, "+")
		} else {
			fmt.Printf("%-*v", colWidth, "-")
		}
	}
	fmt.Println()

	for _, v := range data {
		fmt.Printf("%-*v", colWidth, v[0])
	}
	fmt.Println()
}
