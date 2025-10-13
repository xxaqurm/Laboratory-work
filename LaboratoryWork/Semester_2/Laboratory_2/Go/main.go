package main

import "fmt"


func main() {  // go run *.go - для запуска
	var numTask int = 1
	for numTask != 0 {
		fmt.Print("Веберете программу, которую хотите запустить [1 | 2 | 3 | 0 - для завершения]: ")
		fmt.Scan(&numTask)
		if numTask == 1 {
			task1()
		} else if numTask == 2 {
			task2()
		} else if numTask == 3 {
			task3()
		}
	}

	fmt.Println("Вот и все йоу")
}