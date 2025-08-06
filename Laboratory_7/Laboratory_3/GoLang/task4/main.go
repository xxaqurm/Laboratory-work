package main

import (
	"fmt"
)

func main() {
	var n, m int
	fmt.Print("Введите П и В: ")
	fmt.Scan(&n, &m)

	a := make([]int, n)
	fmt.Printf("Введите %d целых чисел: ", n)
	for i := 0; i < n; i++ {
		fmt.Scan(&a[i])
	}

	prefix := make([]int, n+1)
	for i := 0; i < n; i++ {
		prefix[i+1] = prefix[i] + a[i]
	}

	dp := make([]int, n+1)

	for i := n - 1; i >= 0; i-- {
		best := -1_000_000_000
		for k := 1; k <= m && i+k <= n; k++ {
			sum := prefix[i+k] - prefix[i]
			value := sum - dp[i+k]
			if value > best {
				best = value
			}
		}
		dp[i] = best
	}

	if dp[0] > 0 {
		fmt.Println("Победил Паша!")
	} else if dp[0] < 0 {
		fmt.Println("Победила Вика!")
	} else {
		fmt.Println("Ничья!")
	}
}
