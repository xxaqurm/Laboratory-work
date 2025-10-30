package hash

import (
	"fmt"
	"strconv"
)

type State int

const (
	Empty State = iota
	Occupied
	Deleted
)

type Entry struct {
	key   int
	value string
	state State
}

type OpenHash struct {
	table    []Entry
	capacity int
	size     int
}

func NewOpenHash(cap int) *OpenHash {
	if cap <= 0 {
		cap = 16
	}
	table := make([]Entry, cap)
	for i := range table {
		table[i].state = Empty
	}
	return &OpenHash{
		table:    table,
		capacity: cap,
		size:     0,
	}
}

func (h *OpenHash) hash(key int) int {
	s := strconv.Itoa(key)
	var hashVal uint64
	for _, c := range s {
		hashVal = hashVal*131 + uint64(c)
	}
	return int(hashVal % uint64(h.capacity))
}

func (h *OpenHash) Insert(key int, value string) {
	idx := h.hash(key)
	start := idx

	for {
		switch h.table[idx].state {
		case Empty, Deleted:
			h.table[idx].key = key
			h.table[idx].value = value
			h.table[idx].state = Occupied
			h.size++
			return
		case Occupied:
			if h.table[idx].key == key {
				h.table[idx].value = value
				return
			}
		}
		idx = (idx + 1) % h.capacity
		if idx == start {
			fmt.Println("Таблица переполнена!")
			return
		}
	}
}

func (h *OpenHash) Find(key int) (string, bool) {
	idx := h.hash(key)
	start := idx

	for {
		switch h.table[idx].state {
		case Empty:
			return "", false
		case Occupied:
			if h.table[idx].key == key {
				return h.table[idx].value, true
			}
		}
		idx = (idx + 1) % h.capacity
		if idx == start {
			break
		}
	}
	return "", false
}

func (h *OpenHash) Remove(key int) bool {
	idx := h.hash(key)
	start := idx

	for {
		switch h.table[idx].state {
		case Empty:
			return false
		case Occupied:
			if h.table[idx].key == key {
				h.table[idx].state = Deleted
				h.size--
				return true
			}
		}
		idx = (idx + 1) % h.capacity
		if idx == start {
			break
		}
	}
	return false
}

func (h *OpenHash) Display() {
	for i, entry := range h.table {
		if entry.state == Occupied {
			fmt.Printf("%d: (%d -> %s)\n", i, entry.key, entry.value)
		}
	}
}