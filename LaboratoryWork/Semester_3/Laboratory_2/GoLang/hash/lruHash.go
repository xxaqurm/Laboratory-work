package hash

import (
	"fmt"
	"math"
)

type CacheItem struct {
	key       int
	value     int
	timestamp int
	valid     bool
}

type LRUCache struct {
	capacity int
	timer    int
	cache    []CacheItem
}

func NewLRUCache(cap int) *LRUCache {
	cache := make([]CacheItem, cap)
	return &LRUCache{
		capacity: cap,
		timer:    0,
		cache:    cache,
	}
}

func (l *LRUCache) findIndex(key int) int {
	for i := range l.cache {
		if l.cache[i].valid && l.cache[i].key == key {
			return i
		}
	}
	return -1
}

func (l *LRUCache) findLRUIndex() int {
	oldestTime := math.MaxInt
	oldestIndex := -1
	for i := range l.cache {
		if l.cache[i].valid && l.cache[i].timestamp < oldestTime {
			oldestTime = l.cache[i].timestamp
			oldestIndex = i
		}
	}
	return oldestIndex
}

func (l *LRUCache) findFreeSlot() int {
	for i := range l.cache {
		if !l.cache[i].valid {
			return i
		}
	}
	return -1
}

func (l *LRUCache) Get(key int) int {
	index := l.findIndex(key)
	if index == -1 {
		return -1
	}
	l.timer++
	l.cache[index].timestamp = l.timer
	return l.cache[index].value
}

func (l *LRUCache) Insert(key int, value int) {
	index := l.findIndex(key)
	if index != -1 {
		l.cache[index].value = value
		l.timer++
		l.cache[index].timestamp = l.timer
		return
	}

	freeSlot := l.findFreeSlot()
	l.timer++
	if freeSlot != -1 {
		l.cache[freeSlot] = CacheItem{
			key:       key,
			value:     value,
			timestamp: l.timer,
			valid:     true,
		}
	} else {
		lruIndex := l.findLRUIndex()
		if lruIndex != -1 {
			l.cache[lruIndex] = CacheItem{
				key:       key,
				value:     value,
				timestamp: l.timer,
				valid:     true,
			}
		}
	}
}

func (l *LRUCache) Remove(key int) bool {
	index := l.findIndex(key)
	if index == -1 {
		return false
	}
	l.cache[index].valid = false
	return true
}

func (l *LRUCache) Display() {
	fmt.Printf("LRUCache (capacity: %d, size: %d):\n", l.capacity, l.GetSize())
	for _, item := range l.cache {
		if item.valid {
			fmt.Printf("  [%d -> %d, ts: %d]\n", item.key, item.value, item.timestamp)
		}
	}
}

func (l *LRUCache) GetSize() int {
	count := 0
	for _, item := range l.cache {
		if item.valid {
			count++
		}
	}
	return count
}

func (l *LRUCache) Empty() bool {
	return l.GetSize() == 0
}

func (l *LRUCache) Keys() []int {
	keys := []int{}
	for _, item := range l.cache {
		if item.valid {
			keys = append(keys, item.key)
		}
	}
	return keys
}

func (l *LRUCache) Values() []int {
	values := []int{}
	for _, item := range l.cache {
		if item.valid {
			values = append(values, item.value)
		}
	}
	return values
}

func (l *LRUCache) Clear() {
	for i := range l.cache {
		l.cache[i].valid = false
	}
	l.timer = 0
}