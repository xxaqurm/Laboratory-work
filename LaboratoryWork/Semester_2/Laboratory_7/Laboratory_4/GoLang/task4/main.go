package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"strconv"
)

func main() {
	var n, k int
	reader := bufio.NewReader(os.Stdin)

	for {
		fmt.Print("Введите количество кандидатов и избирателей (n, k): ")
		line, _ := reader.ReadString('\n')
		parts := strings.Fields(line)
		if len(parts) == 2 {
			n, _ = strconv.Atoi(parts[0])
			k, _ = strconv.Atoi(parts[1])
			if n > 0 && k >= 0 {
				break
			}
		}
		fmt.Println("Количество кандидатов и избирателей должно быть больше 0.")
	}

	candidates := make(map[string]int)
	fmt.Print("Введите имена кандидатов: ")
	line, _ := reader.ReadString('\n')
	names := strings.Fields(line)
	for i := 0; i < n && i < len(names); i++ {
		candidates[names[i]] = 0
	}

	voters := make(map[string][]string)
	fmt.Println("Ввеедите имена изберателей и их голоса (имя голос1 голос2 ...): ")
	for i := 0; i < k; i++ {
		fmt.Printf("Избиратель %d: ", i+1)
		line, _ := reader.ReadString('\n')
		parts := strings.Fields(line)
		if len(parts) < n+1 {
			i--
			continue
		}
		name := parts[0]
		votes := []string{}
		for j := 1; j <= n; j++ {
			vote := parts[j]
			if _, ok := candidates[vote]; ok {
				votes = append(votes, vote)
			} else {
				fmt.Printf("Кандидат %s не найден. Попробуйте снова.\n", vote)
				i--
				break
			}
		}
		if len(votes) == n {
			voters[name] = votes
		}
	}

	winnerBord := bordaMethod(candidates, voters)
	if winnerBord == "NONE" {
		fmt.Println("Победитель по методу Борда не выявлен.")
	} else {
		fmt.Println("Победитель по методу Борда:", winnerBord)
	}

	winnerCondorcet := condorcetMethod(candidates, voters)
	if winnerCondorcet == "NONE" {
		fmt.Println("Победитель по методу Кондорсе не выявлен.")
	} else {
		fmt.Println("Победитель по методу Конкордета:", winnerCondorcet)
	}

	if winnerBord != winnerCondorcet {
		fmt.Println("\nПобедители по разным алгоритмам различаются.")
	}
}
