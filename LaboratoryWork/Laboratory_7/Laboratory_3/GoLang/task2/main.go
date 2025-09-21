package main

import (
	"fmt"
	"math/rand"
	"task2/primality"
	"task2/utils"
)

func main() {
	primes := utils.EratosthenesSieve(500)

	fmt.Println("Алгоритмы для генерации простых чисел:")
	fmt.Println("1 - Тест Миллера")
	fmt.Println("2 - Тест Поклингтона")
	fmt.Println("3 - ГОСТ Р34.10-94")
	fmt.Print("Выберите алгоритм (1/2/3) или 0 для выхода: ")

	var choice int
	for {
		fmt.Scan(&choice)
		if choice >= 1 && choice <= 3 {
			break
		} else if choice == 0 {
			return
		}
		fmt.Print("Неверный ввод. Попробуйте снова: ")
	}

	generatorFuncs := []func(int, []int) (uint64, int){
		algorithms.MillerPrime,
		algorithms.PocklingtonPrime,
		algorithms.GostPrime,
	}

	primeSet := make(map[uint64][2]int)
	for len(primeSet) < 10 {
		size := rand.Intn(9) + 5
		prime, attempts := generatorFuncs[choice-1](size, primes)

		var passed bool
		if choice == 1 {
			passed = algorithms.PocklingtonTest(prime, 8)
		} else {
			passed = algorithms.MillerTest(prime, 8)
		}
		
		if _, exists := primeSet[prime]; !exists {
			primeSet[prime] = [2]int{attempts, boolToInt(passed)}
		}
	}

	fmt.Println("\nТаблица:")
	utils.PrintTable(primeSet)
}

func boolToInt(b bool) int {
	if b {
		return 1
	}
	return 0
}
