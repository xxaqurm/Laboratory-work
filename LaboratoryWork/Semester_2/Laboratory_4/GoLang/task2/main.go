package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func main() {
	fmt.Println("Сгенерированный массив с случайными дробными числами:")
	doubleArr := genDoubleVector()
	for _, v := range doubleArr {
		fmt.Printf("%.2f ", v)
	}
	fmt.Println("\n")

	sum, product := processPosNeg(doubleArr)
	fmt.Println("Найдем сумму положительных и произведение отрицательных элементов массива, расположенных до максимального элемента.")
	fmt.Printf("Сумма положительных элементов: %.2f\n", sum)
	fmt.Printf("Произведение отрицательных элементов: %.2f\n\n", product)

	fmt.Print("Введите строку для изменения регистра: ")
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	str := scanner.Text()
	swapped := swapCase(str)
	fmt.Println("Строка с измененным регистром:", swapped)

	fmt.Print("\nКоличество элементов, которые больше соседнего: ")
	fmt.Println(countGreaterThanNeighbors(doubleArr))

	fmt.Println("\nСгенерированный массив с случайными целыми числами:")
	intArr := genIntVector()
	sumInt := 0
	for _, v := range intArr {
		sumInt += v
		fmt.Printf("%d ", v)
	}
	fmt.Println("\n\nСумма элементов этого массива:", sumInt)

	arrayMixing(&intArr)
	fmt.Println("\nПеремешанный массив:")
	for _, v := range intArr {
		fmt.Printf("%d ", v)
	}
	fmt.Println()

	sort.Ints(intArr)
	sumSorted := 0
	fmt.Println("\nОтсортированный массив:")
	for _, v := range intArr {
		sumSorted += v
		fmt.Printf("%d ", v)
	}
	fmt.Println()

	fmt.Printf("\nСумма измененного массива: %d\n", sumSorted)
	fmt.Printf("Сумма исходного массива: %d\n", sumInt)
	fmt.Printf("Разница между суммами: %d\n", sumSorted-sumInt)
}
