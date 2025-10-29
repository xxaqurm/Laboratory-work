package main

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"strconv"
	"strings"

	"laba2/tasks"
	"laba2/utils/menu"
)

type MenuOptions int

const (
	Exit MenuOptions = iota
	ArithmeticExpression
	InteractionWithSet
	SetPartition
	Subarrays
	CheckBalance
	ConvolutionMethod
	LRUCache
)

func clearScreen() {
	cmd := exec.Command("clear")
	cmd.Stdout = os.Stdout
	_ = cmd.Run()
}

func main() {
	clearScreen()
	defer func() {
		if r := recover(); r != nil {
			fmt.Println("Ошибка:", r)
		}
	}()

	args := os.Args
	choice := -1

	if len(args) == 5 {
		choice = int(InteractionWithSet)
	} else {
		menu.StartMenu()
		reader := bufio.NewReader(os.Stdin)
		input, _ := reader.ReadString('\n')
		input = strings.TrimSpace(input)
		val, err := strconv.Atoi(input)
		if err != nil {
			fmt.Println("Неверный ввод, попробуйте снова.")
			return
		}
		choice = val
	}

	switch MenuOptions(choice) {
		case Exit:
			clearScreen()
			return

		case ArithmeticExpression:
			tasks.ArithmeticExpression()

		case InteractionWithSet:
			err := tasks.InteractionWithSet(args)
			if err != nil {
				fmt.Println("Ошибка:", err)
			}

		case SetPartition:
			tasks.SetPartition()

		case Subarrays:
			tasks.Subarrays()

		case CheckBalance:
			tasks.AVLBalance()

		case ConvolutionMethod:
			tasks.IntWithHashTables()

		case LRUCache:
			tasks.InteractionWithLRU()

		default:
			clearScreen()
			fmt.Println("Неверный выбор. Попробуйте снова.")
	}
}