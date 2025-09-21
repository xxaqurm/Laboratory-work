package main

import (
	"fmt"
	"math"
	"strings"
)

func printTable(points [][2]float64) {
	cellWidth := 5
	border := "+" + "-" + "+"

	for range points {
		border += strings.Repeat("-", cellWidth) + "+"
	}

	fmt.Println(border)

	fmt.Printf("|%1s", "x")
	for _, point := range points {
		fmt.Printf("|%*.1f", cellWidth, point[0])
	}
	fmt.Println("|")
	fmt.Println(border)

	fmt.Printf("|%1s", "y")
	for _, point := range points {
		fmt.Printf("|%*.1f", cellWidth, point[1])
	}
	fmt.Println("|")
	fmt.Println(border)
}

func main() {
	// Значения по умолчанию
	xStart := -10.0
	xFinish := 8.0
	dx := 0.5
	var change int

	fmt.Println("Значения по умолчанию:")
	fmt.Printf("x начальное: %.1f\nx конечное: %.1f\ndx: %.1f\n", xStart, xFinish, dx)
	fmt.Print("Хотите ли вы изменить значения по умолчанию? (1 - да / 0 - нет): ")
	fmt.Scan(&change)

	if change == 1 {
		fmt.Print("\nВведите x начальное, x конечное и dx (xs xf dx): ")
		fmt.Scan(&xStart, &xFinish, &dx)
	}

	var xyValues [][2]float64

	for x := xStart; x <= xFinish; x += dx {
		var y float64
		switch {
		case x >= -10 && x <= -6:
			if x == -8 {
				y = 0
			} else {
				val := 4 - math.Pow(x+8, 2)
				if val >= 0 {
					y = math.Sqrt(val) - 2
				} else {
					y = 0 // на случай некорректного корня
				}
			}
		case x > -6 && x <= 2:
			y = 0.5*x + 1
		case x > 2 && x <= 6:
			y = 0
		case x > 6 && x <= 8:
			y = math.Pow(x-6, 2)
		default:
			y = 0
		}
		xyValues = append(xyValues, [2]float64{x, y})
	}

	printTable(xyValues)
}
