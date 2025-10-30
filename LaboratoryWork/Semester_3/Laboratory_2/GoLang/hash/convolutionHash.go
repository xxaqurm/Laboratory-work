package hash

import (
	"fmt"
)

type HashTable struct {
	table     [][]pair
	tableSize int
}

type pair struct {
	key   int
	value string
}

func NewHashTable() *HashTable {
	const size = 10
	return &HashTable{
		table:     make([][]pair, size),
		tableSize: size,
	}
}

func (h *HashTable) foldingHash(key int) int {
	sum := 0
	temp := key
	for temp > 0 {
		sum += temp % 100
		temp /= 100
	}
	index := sum % h.tableSize
	fmt.Println(index)
	return index
}

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

func (h *HashTable) Search(key int) string {
	index := h.foldingHash(key)
	for _, p := range h.table[index] {
		if p.key == key {
			return p.value
		}
	}
	return ""
}

func (h *HashTable) Remove(key int) bool {
	index := h.foldingHash(key)
	bucket := &h.table[index]

	for i, p := range *bucket {
		if p.key == key {
			*bucket = append((*bucket)[:i], (*bucket)[i+1:]...)
			return true
		}
	}
	return false
}

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