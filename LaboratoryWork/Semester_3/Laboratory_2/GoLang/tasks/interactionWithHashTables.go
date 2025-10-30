package tasks

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	"laba2/hash"
)

func IntWithHashTables() {
	reader := bufio.NewReader(os.Stdin)

	fmt.Print("Выберите режим (1 - метод цепочек, 2 - метод открытой адресации): ")
	modeLine, _ := reader.ReadString('\n')
	modeLine = strings.TrimSpace(modeLine)
	method, _ := strconv.Atoi(modeLine)

	if method == 1 {
		hsh := hash.NewHashTable()

		for {
			fmt.Print("Введите команду (INSERT key value | SEARCH key | REMOVE key | DISPLAY): ")
			line, _ := reader.ReadString('\n')
			line = strings.TrimSpace(line)
			parts := strings.Split(line, " ")
			if len(parts) == 0 {
				continue
			}

			cmd := strings.ToUpper(parts[0])

			switch cmd {
			case "INSERT":
				if len(parts) < 3 {
					fmt.Println("Неверный формат команды INSERT")
					continue
				}
				key, err := strconv.Atoi(parts[1])
				if err != nil {
					fmt.Println("Ключ должен быть числом")
					continue
				}
				value := parts[2]
				hsh.Insert(key, value)

			case "SEARCH":
				if len(parts) < 2 {
					fmt.Println("Неверный формат команды SEARCH")
					continue
				}
				key, err := strconv.Atoi(parts[1])
				if err != nil {
					fmt.Println("Ключ должен быть числом")
					continue
				}
				res := hsh.Search(key)
				if res == "" {
					fmt.Println("Элемент отсутствует")
				} else {
					fmt.Println("Значение:", res)
				}

			case "REMOVE":
				if len(parts) < 2 {
					fmt.Println("Неверный формат команды REMOVE")
					continue
				}
				key, err := strconv.Atoi(parts[1])
				if err != nil {
					fmt.Println("Ключ должен быть числом")
					continue
				}
				if hsh.Remove(key) {
					fmt.Println("Элемент удален")
				} else {
					fmt.Println("Элемент для удаления не найден")
				}

			case "DISPLAY":
				hsh.Display()

			default:
				fmt.Println("[ ERROR ] Unknown command")
			}
		}

	} else if method == 2 {
		hsm := hash.NewOpenHash(16)

		for {
			fmt.Print("Введите команду (INSERT key value | SEARCH key | REMOVE key | DISPLAY): ")
			line, _ := reader.ReadString('\n')
			line = strings.TrimSpace(line)
			parts := strings.Split(line, " ")
			if len(parts) == 0 {
				continue
			}

			cmd := strings.ToUpper(parts[0])

			switch cmd {
			case "INSERT":
				if len(parts) < 3 {
					fmt.Println("Неверный формат команды INSERT")
					continue
				}
				key, err := strconv.Atoi(parts[1])
				if err != nil {
					fmt.Println("Ключ должен быть числом")
					continue
				}
				value := parts[2]
				hsm.Insert(key, value)

			case "SEARCH":
				if len(parts) < 2 {
					fmt.Println("Неверный формат команды SEARCH")
					continue
				}
				key, err := strconv.Atoi(parts[1])
				if err != nil {
					fmt.Println("Ключ должен быть числом")
					continue
				}
				if val, found := hsm.Find(key); found {
					fmt.Println("Элемент присутствует:", val)
				} else {
					fmt.Println("Элемент отсутствует!")
				}

			case "REMOVE":
				if len(parts) < 2 {
					fmt.Println("Неверный формат команды REMOVE")
					continue
				}
				key, err := strconv.Atoi(parts[1])
				if err != nil {
					fmt.Println("Ключ должен быть числом")
					continue
				}
				if hsm.Remove(key) {
					fmt.Println("Элемент удален")
				} else {
					fmt.Println("Элемент для удаления не найден")
				}

			case "DISPLAY":
				hsm.Display()

			default:
				fmt.Println("[ ERROR ] Unknown command")
			}
		}

	} else {
		fmt.Println("[ ERROR ] Unknown method")
	}
}