package tasks

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	"laba2/ds" // замените на путь к пакету ds с DynamicArray
)

// createSubarrays рекурсивно создаёт все подмассивы
func createSubarrays(arr *ds.DynamicArray[string], current *ds.DynamicArray[string], idx int, subarrays *ds.DynamicArray[*ds.DynamicArray[string]]) {
	if idx == arr.GetSize() {
		// создаём копию current, чтобы сохранить текущее состояние
		temp := ds.NewDynamicArray[string]()
		for i := 0; i < current.GetSize(); i++ {
			val, _ := current.At(i)
			temp.PushBack(val)
		}
		subarrays.PushBack(temp)
		return
	}

	// не включаем текущий элемент
	createSubarrays(arr, current, idx+1, subarrays)

	// включаем текущий элемент
	val, _ := arr.At(idx)
	current.PushBack(val)
	createSubarrays(arr, current, idx+1, subarrays)
	current.DelElm(current.GetSize() - 1)
}

func Subarrays() {
	reader := bufio.NewReader(os.Stdin)

	fmt.Print("Введите длину массива: ")
	input, _ := reader.ReadString('\n')
	input = strings.TrimSpace(input)
	n, _ := strconv.Atoi(input)

	arr := ds.NewDynamicArray[string]()
	fmt.Println("Введите элементы массива через пробел:")
	line, _ := reader.ReadString('\n')
	line = strings.TrimSpace(line)
	elems := strings.Split(line, " ")

	for i := 0; i < n; i++ {
		arr.PushBack(elems[i])
	}

	result := ds.NewDynamicArray[*ds.DynamicArray[string]]()
	current := ds.NewDynamicArray[string]()

	createSubarrays(arr, current, 0, result)

	fmt.Print("[ ")
	for i := 0; i < result.GetSize(); i++ {
		subarray, _ := result.At(i)
		fmt.Print("{")
		for j := 0; j < subarray.GetSize(); j++ {
			elem, _ := subarray.At(j)
			fmt.Print(elem)
			if j != subarray.GetSize()-1 {
				fmt.Print(",")
			}
		}
		fmt.Print("}")
		if i != result.GetSize()-1 {
			fmt.Print(" ")
		}
	}
	fmt.Println(" ]")
}