package hash

import (
	"fmt"
)

// HashTable — аналог C++ класса HashTable
type HashTable struct {
	table     [][]pair
	tableSize int
}

// pair — пара ключ-значение
type pair struct {
	key   int
	value string
}

// NewHashTable — конструктор
func NewHashTable() *HashTable {
	const size = 10
	return &HashTable{
		table:     make([][]pair, size),
		tableSize: size,
	}
}

// foldingHash — хеш-функция "folding"
func (h *HashTable) foldingHash(key int) int {
	sum := 0
	temp := key
	for temp > 0 {
		sum += temp % 100
		temp /= 100
	}
	index := sum % h.tableSize
	fmt.Println(index) // как и в оригинале — вывод индекса
	return index
}

// Insert — вставляет или перезаписывает ключ
func (h *HashTable) Insert(key int, value string) {
	index := h.foldingHash(key)
	bucket := &h.table[index]

	for i := range *bucket {
		if (*bucket)[i].key == key {
			(*bucket)[i].value = value
			return
		}
	}

	*bucket = append(*bucket, pair{key: key, value: value})
}

// Search — ищет по ключу
func (h *HashTable) Search(key int) string {
	index := h.foldingHash(key)
	for _, p := range h.table[index] {
		if p.key == key {
			return p.value
		}
	}
	return ""
}

// Remove — удаляет по ключу
func (h *HashTable) Remove(key int) bool {
	index := h.foldingHash(key)
	bucket := &h.table[index]

	for i, p := range *bucket {
		if p.key == key {
			// удалить элемент i
			*bucket = append((*bucket)[:i], (*bucket)[i+1:]...)
			return true
		}
	}
	return false
}

// Display — выводит все непустые ячейки
func (h *HashTable) Display() {
	for i, bucket := range h.table {
		if len(bucket) > 0 {
			fmt.Printf("%d: ", i)
			for _, p := range bucket {
				fmt.Printf("[%d -> %s] ", p.key, p.value)
			}
			fmt.Println()
		}
	}
}