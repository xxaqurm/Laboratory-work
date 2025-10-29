package menu

import "fmt"

func StartMenu() {
	fmt.Println("Список программ:")
	fmt.Println("0. Exit")
	fmt.Println("1. Arithmetic expression")
	fmt.Println(`2. Interactions with set (для использования перезапустите программу и используйте следующий шаблон: go run ./cmd/main --file somethingFile.txt --query "COMMAND StructName Data")`)
	fmt.Println("3. Set partition")
	fmt.Println("4. Subarrays")
	fmt.Println("5. Check AVL-tree balance")
	fmt.Println("6. Convolution method")
	fmt.Println("7. LRU cache")
	fmt.Print("Выберите программу: ")
}