package tasks

import (
	"bufio"
	"fmt"
	"os"
)

func allUsed(used []bool) bool {
	for _, u := range used {
		if !u {
			return false
		}
	}
	return true
}

func findCombinations(
	s []int,
	result *[][]int,
	used []bool,
	target int,
	currentSubset []int,
	currentSum int,
	start int,
) bool {
	if allUsed(used) {
		return len(currentSubset) == 0
	}

	for i := start; i < len(s); i++ {
		if !used[i] && currentSum+s[i] <= target {
			used[i] = true
			currentSubset = append(currentSubset, s[i])

			if currentSum+s[i] == target {
				*result = append(*result, append([]int{}, currentSubset...))
				newSubset := []int{}
				if findCombinations(s, result, used, target, newSubset, 0, 0) {
					return true
				}
				*result = (*result)[:len(*result)-1]
			} else {
				if findCombinations(s, result, used, target, currentSubset, currentSum+s[i], i+1) {
					return true
				}
			}

			currentSubset = currentSubset[:len(currentSubset)-1]
			used[i] = false
		}
	}
	return false
}

func SetPartition() {
	reader := bufio.NewReader(os.Stdin)

	fmt.Print("Введите длину множества: ")
	var n int
	fmt.Fscan(reader, &n)

	s := make([]int, n)
	fmt.Print("Введите элементы множества: ")
	for i := 0; i < n; i++ {
		fmt.Fscan(reader, &s[i])
	}

	totalSum := 0
	for _, x := range s {
		totalSum += x
	}

	found := false
	for k := 2; k <= n; k++ {
		if totalSum%k != 0 {
			continue
		}

		target := totalSum / k
		used := make([]bool, n)
		result := [][]int{}
		currentSubset := []int{}

		if findCombinations(s, &result, used, target, currentSubset, 0, 0) {
			fmt.Printf("Разделение найдено (сумма подмножеств = %d):\n", target)
			for _, subset := range result {
				fmt.Print("{ ")
				for _, num := range subset {
					fmt.Printf("%d ", num)
				}
				fmt.Println("}")
			}
			found = true
		}
	}

	if !found {
		fmt.Println("Не удалось найти такие подмножества")
	}
}