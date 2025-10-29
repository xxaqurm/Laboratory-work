package tasks

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	"laba2/ds" // замените на путь к пакету ds с BST
)

func AVLBalance() {
	fmt.Println("Введите элементы (заканчивается 0):")

	reader := bufio.NewReader(os.Stdin)
	line, _ := reader.ReadString('\n')
	line = strings.TrimSpace(line)
	elems := strings.Split(line, " ")

	tree := &ds.BST{}
	for _, s := range elems {
		val, err := strconv.Atoi(s)
		if err != nil {
			continue
		}
		if val == 0 {
			break
		}
		tree.Root = tree.Insert(tree.Root, val)
	}

	isBalanced := true
	tree.CheckBalance(tree.Root, &isBalanced)

	if isBalanced {
		fmt.Println("YES")
	} else {
		fmt.Println("NO")
	}
}