package dynamicarray

import "fmt"

type DynamicArray[T any] struct {
	data []T
}

func New[T any]() *DynamicArray[T] {
	return &DynamicArray[T]{data: make([]T, 0)}
}

func (da *DynamicArray[T]) PushBack(item T) {
	da.data = append(da.data, item)
}

func (da *DynamicArray[T]) Insert(index int, item T) error {
	if index < 0 || index > len(da.data) {
		return fmt.Errorf("index out of range")
	}
	da.data = append(da.data[:index], append([]T{item}, da.data[index:]...)...)
	return nil
}

func (da *DynamicArray[T]) Get(index int) (T, error) {
	if index < 0 || index >= len(da.data) {
		var zero T
		return zero, fmt.Errorf("index out of range")
	}
	return da.data[index], nil
}

func (da *DynamicArray[T]) Delete(index int) error {
	if index < 0 || index >= len(da.data) {
		return fmt.Errorf("index out of range")
	}
	da.data = append(da.data[:index], da.data[index+1:]...)
	return nil
}

func (da *DynamicArray[T]) Set(index int, item T) error {
	if index < 0 || index >= len(da.data) {
		return fmt.Errorf("index out of range")
	}
	da.data[index] = item
	return nil
}

func (da *DynamicArray[T]) Len() int {
	return len(da.data)
}

func (da *DynamicArray[T]) Read() []T {
	return da.data
}