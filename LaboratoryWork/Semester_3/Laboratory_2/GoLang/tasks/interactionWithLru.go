package tasks

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	"laba2/hash"
)

func InteractionWithLRU() {
	reader := bufio.NewReader(os.Stdin)

	fmt.Println("Размер кэша (cap) и количество запросов (Q)")

	fmt.Print("cap: ")
	capLine, _ := reader.ReadString('\n')
	capLine = strings.TrimSpace(capLine)
	capacity, _ := strconv.Atoi(capLine)

	fmt.Print("Q: ")
	qLine, _ := reader.ReadString('\n')
	qLine = strings.TrimSpace(qLine)
	Q, _ := strconv.Atoi(qLine)

	cache := hash.NewLRUCache(capacity)

	for i := 0; i < Q; i++ {
		fmt.Print("Введите команду (SET key value | GET key): ")
		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)
		parts := strings.Split(line, " ")
		if len(parts) == 0 {
			continue
		}

		cmd := strings.ToUpper(parts[0])

		switch cmd {
		case "SET":
			if len(parts) < 3 {
				fmt.Println("Неверный формат команды SET")
				continue
			}
			key, err1 := strconv.Atoi(parts[1])
			value, err2 := strconv.Atoi(parts[2])
			if err1 != nil || err2 != nil {
				fmt.Println("Ключ и значение должны быть числами")
				continue
			}
			cache.Insert(key, value)

		case "GET":
			if len(parts) < 2 {
				fmt.Println("Неверный формат команды GET")
				continue
			}
			key, err := strconv.Atoi(parts[1])
			if err != nil {
				fmt.Println("Ключ должен быть числом")
				continue
			}
			val := cache.Get(key)
			fmt.Println(val)

		default:
			fmt.Println("[ ERROR ] Unknown command")
		}
	}
}