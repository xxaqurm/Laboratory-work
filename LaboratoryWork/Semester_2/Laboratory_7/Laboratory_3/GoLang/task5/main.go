package main

import (
	"fmt"
	"math"
)

func coffee(Tk float64, Tsr float64, r float64, timeSteps []float64) []float64 {
	/* Моделирует остывание кофе */
	var temperatures []float64
	for _, t := range timeSteps {
		T := Tsr + (Tk - Tsr) * math.Exp(-r * t)
		temperatures = append(temperatures, T)
	}
	return temperatures
}

func printResults(timeSteps []float64, temperatures []float64) {
	/* Выводит таблицу результатов */
	fmt.Println("Результаты моделирования остывания кофе:")
	fmt.Println("----------------------------------------")
	fmt.Println("|  Время (мин)  |  Температура (°C)  |")
	fmt.Println("----------------------------------------")

	for i := 0; i < len(timeSteps); i++ {
		fmt.Printf("|%10.1f     |%14.2f    |\n", timeSteps[i], temperatures[i])
	}
	fmt.Println("----------------------------------------")
}

func main() {
	var num_meas int = 0
	var r float64 = 0
	var Tk float64 = 0
	var Tsr float64 = 0

	fmt.Printf("Моделирование остывания кофе\n----------------------------\n")
	fmt.Print("Введите начальную температуру кофе (в градусах цельсия): ")
	fmt.Scan(&Tk)

	fmt.Print("Введите температуру окружающей среды (в градусах цельсия): ")
	fmt.Scan(&Tsr)

	fmt.Print("Введите коэффициент охлаждения (0 < r < 1): ")
	fmt.Scan(&r)

	fmt.Print("Введите количество измерений: ")
	fmt.Scan(&num_meas)

	timeSteps := make([]float64, num_meas)
	fmt.Println("Введите моменты времени для зимерений (в минутах):")
	for i := 0; i < num_meas; i++ {
		fmt.Printf("Измерение %d: ", i + 1)
		fmt.Scan(&timeSteps[i])
	}

	temperatures := coffee(Tk, Tsr, r, timeSteps)
	printResults(timeSteps, temperatures)
}