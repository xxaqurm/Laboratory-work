package algorithms

import (
	"math"
	"math/rand"
	"task2/utils"
)

type Pair struct {
	First  uint64
	Second int
}

func MillerTest(n uint64, t int) bool {
	if n == 2 || n == 3 || n == 5 || n == 7 {
		return true
	}
	if n < 10 {
		return false
	}

	nums := make(map[uint64]struct{})
	for len(nums) < t {
		a := uint64(rand.Intn(int(n-3)) + 2)
		nums[a] = struct{}{}
	}

	for a := range nums {
		if utils.ModPow(a, n-1, n) != 1 {
			return false
		}
	}

	factors := utils.Factorize(n - 1)
	for _, q := range factors {
		onlyOne := true
		for a := range nums {
			if utils.ModPow(a, (n-1)/uint64(q.First), n) != 1 {
				onlyOne = false
				break
			}
		}
		if onlyOne {
			return false
		}
	}
	return true
}

func PocklingtonTest(n uint64, t int) bool {
	if n == 2 || n == 3 || n == 5 || n == 7 {
		return true
	}
	if n < 10 {
		return false
	}

	r := rand.Intn(3) + 1
	factors := utils.Factorize((n - 1) / uint64(r))

	nums := make(map[uint64]struct{})
	for len(nums) < t {
		a := uint64(rand.Intn(int(n-3)) + 2)
		nums[a] = struct{}{}
	}

	for a := range nums {
		if utils.ModPow(a, n-1, n) != 1 {
			return false
		}
	}

	for a := range nums {
		noOne := true
		for _, q := range factors {
			if utils.ModPow(a, (n-1)/uint64(q.First), n) == 1 {
				noOne = false
				break
			}
		}
		if noOne {
			return true
		}
	}
	return false
}

func MillerPrime(size int, primes []int) (uint64, int) {
	var n uint64 = 1
	failCount := -1
	for !MillerTest(n, 8) {
		attempts := 0
		m := uint64(1)
		uniq := make(map[int]bool)
		for utils.SizeNum(m) != size-1 {
			q := primes[rand.Intn(len(primes))]
			a := rand.Intn(20) + 1
			if utils.SizeNum(m*uint64(math.Pow(float64(q), float64(a)))) <= size-1 && !uniq[q] {
				m *= uint64(math.Pow(float64(q), float64(a)))
				uniq[q] = true
			}
			attempts++
			if attempts == 100 && utils.SizeNum(m) != size-1 {
				m = 1
				attempts = 0
				uniq = make(map[int]bool)
			}
		}
		n = 2*m + 1
		failCount++
	}
	return n, failCount
}

func PocklingtonPrime(size int, primes []int) (uint64, int) {
	var n uint64 = 1
	failCount := -1
	for !PocklingtonTest(n, 8) {
		attempts := 0
		f := uint64(1)
		for utils.SizeNum(f)-1 != size/2 {
			q := primes[rand.Intn(len(primes))]
			a := rand.Intn(20) + 1
			if utils.SizeNum(f*uint64(math.Pow(float64(q), float64(a))))-1 <= size/2 {
				f *= uint64(math.Pow(float64(q), float64(a)))
			}
			attempts++
			if attempts == 100 && utils.SizeNum(f)-1 != size/2 {
				f = 1
				attempts = 0
			}
		}
		r := f >> 1
		if r%2 == 1 {
			r++
		}
		n = r*f + 1
		failCount++
	}
	return n, failCount
}

func GostPrime(size int, primes []int) (uint64, int) {
	if size <= 1 {
		return 0, 0
	}
	if size == 2 {
		return 3, 0
	}

	q, _ := MillerPrime(int(math.Ceil(float64(size)/2)), primes)
	var p, n, u uint64
	e := rand.Float64()
	n = uint64(math.Ceil(math.Pow(2, float64(size-1))/float64(q))) + uint64(math.Ceil(math.Pow(2, float64(size-1))*e/float64(q)))
	if n%2 != 0 {
		n++
	}
	p = (n + u) * q + 1
	for p > uint64(math.Pow(2, float64(size))) {
		e = rand.Float64()
		n = uint64(math.Ceil(math.Pow(2, float64(size-1))/float64(q))) + uint64(math.Ceil(math.Pow(2, float64(size-1))*e/float64(q)))
		if n%2 != 0 {
			n++
		}
		p = (n + u) * q + 1
	}

	failCount := -1
	for !(utils.ModPow(2, p-1, p) == 1 && utils.ModPow(2, n+u, p) != 1) {
		u += 2
		p = (n + u) * q + 1
		failCount++
	}
	if failCount == -1 {
		failCount = 0
	}
	return p, failCount
}
