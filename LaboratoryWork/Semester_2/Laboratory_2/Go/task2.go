package main

import "fmt"


func print_bottles(bottle string, count int) {
	/* Выводит бутылки на экран. */
	for i := 0; i < count; i++ {
		if i % 3 == 0 {
			fmt.Println()
		}
		fmt.Printf("%s ", bottle)
	}
}


func drink_simulation(n, m int) [2]int {
	/* Показывает все шаги питья. */
	full := n
	empty := 0
	total_drunk := 0
	iterations := 0

	full_bottle := "●"
	empty_bottle := "○"

	// Выведем дано
	fmt.Print("Дано")
	print_bottles(full_bottle, full)
	fmt.Print("\n\n")

	for {
		// Шаг 1: выпить все полные бутылки
		if full > 0 {
			total_drunk += full
			empty += full
			full = 0
			iterations++

			// Выведем все выпитые бутылки
			fmt.Printf("%d шаг", iterations)
			print_bottles(empty_bottle, empty)
			fmt.Print("\n\n")

			if (empty < m) {  // Условие завершения
				break
			}

			// Шаг 2: Обмен пустых бутылок на полные
			full = empty / m
			empty = empty % m
			iterations++

			// Выведем бутылки после обмена
			fmt.Printf("%d шаг", iterations)
			print_bottles(full_bottle, full)
			print_bottles(empty_bottle, empty)
			fmt.Print("\n\n")
		} 
	}

	return [2]int{total_drunk, iterations}
}


func task2() {
	var n, m int
	fmt.Print("Введите количество полных бутылок и количество бутылок, которых достаточно для обмена: ")
	fmt.Scan(&n, &m)

	fmt.Printf("Input: %d %d \n", n, m)

	result := drink_simulation(n, m)

	total := result[0]
	iters := result[1]

	fmt.Printf("Output (total, iters): %d %d \n", total, iters)
}