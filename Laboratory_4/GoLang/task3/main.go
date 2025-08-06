package main

import (
	"fmt"
	"time"
)

// XORShift32 — генератор псевдослучайных чисел
func xorshift32(seed *uint32) uint32 {
	*seed ^= *seed << 16
	*seed ^= *seed >> 21
	*seed ^= *seed << 11
	return *seed
}

func main() {
	// Используем текущее время в качестве начального значения
	seed := uint32(time.Now().Unix())

	for i := 0; i < 10; i++ {
		rnd := xorshift32(&seed)
		fmt.Printf("Случайное число: %d\n", rnd)
	}
}
