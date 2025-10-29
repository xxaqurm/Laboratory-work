package ds

import (
	"errors"
	"fmt"
)

// DynamicArray — аналог std::vector или кастомного динамического массива из C++.
type DynamicArray[T any] struct {
	data     []T
	size     int
	capacity int
}

// NewDynamicArray создаёт новый пустой массив.
func NewDynamicArray[T any]() *DynamicArray[T] {
	capacity := 10
	return &DynamicArray[T]{
		data:     make([]T, capacity),
		size:     0,
		capacity: capacity,
	}
}

// resizeToRight увеличивает ёмкость массива на 10.
func (da *DynamicArray[T]) resizeToRight() {
	newCapacity := da.capacity + 10
	newData := make([]T, newCapacity)
	copy(newData, da.data[:da.size])
	da.data = newData
	da.capacity = newCapacity
}

// resizeToLeft уменьшает ёмкость массива на 10 (если возможно).
func (da *DynamicArray[T]) resizeToLeft() {
	if da.capacity <= 10 {
		return
	}
	newCapacity := da.capacity - 10
	newData := make([]T, newCapacity)
	copy(newData, da.data[:da.size])
	da.data = newData
	da.capacity = newCapacity
}

// PushBack добавляет элемент в конец.
func (da *DynamicArray[T]) PushBack(value T) {
	if da.size == da.capacity {
		da.resizeToRight()
	}
	da.data[da.size] = value
	da.size++
}

// Insert вставляет элемент по индексу.
func (da *DynamicArray[T]) Insert(value T, pos int) error {
	if pos < 0 || pos > da.size {
		return errors.New("invalid index")
	}
	if da.size == da.capacity {
		da.resizeToRight()
	}
	// сдвигаем элементы вправо
	da.data = append(da.data[:pos+1], da.data[pos:da.size]...)
	da.data[pos] = value
	da.size++
	return nil
}

// GetElm возвращает элемент по индексу.
func (da *DynamicArray[T]) GetElm(pos int) (T, error) {
	if pos < 0 || pos >= da.size {
		var zero T
		return zero, errors.New("invalid index")
	}
	return da.data[pos], nil
}

// At возвращает элемент по индексу (аналог operator[]).
func (da *DynamicArray[T]) At(pos int) (T, error) {
	return da.GetElm(pos)
}

// Replace заменяет элемент по индексу.
func (da *DynamicArray[T]) Replace(value T, pos int) error {
	if pos < 0 || pos >= da.size {
		return errors.New("invalid index")
	}
	da.data[pos] = value
	return nil
}

// DelElm удаляет элемент по индексу.
func (da *DynamicArray[T]) DelElm(pos int) error {
	if pos < 0 || pos >= da.size {
		return errors.New("invalid index")
	}
	copy(da.data[pos:], da.data[pos+1:da.size])
	da.size--
	if da.size <= da.capacity-10 {
		da.resizeToLeft()
	}
	return nil
}

// GetSize возвращает количество элементов.
func (da *DynamicArray[T]) GetSize() int {
	return da.size
}

// Clear очищает массив, но не изменяет ёмкость.
func (da *DynamicArray[T]) Clear() {
	da.size = 0
}

// IsEmpty проверяет, пуст ли массив.
func (da *DynamicArray[T]) IsEmpty() bool {
	return da.size == 0
}

// Destroy очищает и обнуляет данные.
func (da *DynamicArray[T]) Destroy() {
	da.data = nil
	da.size = 0
	da.capacity = 0
}

// Print выводит массив в консоль в формате {1, 2, 3}
func (da *DynamicArray[T]) Print() {
	fmt.Print("{")
	for i := 0; i < da.size; i++ {
		fmt.Print(da.data[i])
		if i != da.size-1 {
			fmt.Print(", ")
		}
	}
	fmt.Print("}")
}