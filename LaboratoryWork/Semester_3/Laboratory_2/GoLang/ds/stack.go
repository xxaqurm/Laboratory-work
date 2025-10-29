package ds

import (
	"errors"
	"fmt"
)

// StackNode — элемент стека.
type StackNode[T any] struct {
	Key  T
	Next *StackNode[T]
}

// Stack — структура стека на связном списке.
type Stack[T any] struct {
	head *StackNode[T]
}

// NewStack создаёт новый пустой стек.
func NewStack[T any]() *Stack[T] {
	return &Stack[T]{head: nil}
}

// Push добавляет элемент на вершину стека.
func (s *Stack[T]) Push(value T) {
	newNode := &StackNode[T]{Key: value, Next: s.head}
	s.head = newNode
}

// Pop удаляет верхний элемент стека.
// Возвращает ошибку, если стек пуст.
func (s *Stack[T]) Pop() error {
	if s.head == nil {
		return errors.New("[ERROR] Stack is empty")
	}
	s.head = s.head.Next
	return nil
}

// Top возвращает верхний элемент без удаления.
// Возвращает ошибку, если стек пуст.
func (s *Stack[T]) Top() (T, error) {
	if s.head == nil {
		var zero T
		return zero, errors.New("[ERROR] Stack is empty")
	}
	return s.head.Key, nil
}

// Empty проверяет, пуст ли стек.
func (s *Stack[T]) Empty() bool {
	return s.head == nil
}

// Print выводит все элементы стека.
func (s *Stack[T]) Print() {
	for node := s.head; node != nil; node = node.Next {
		fmt.Printf("%v ", node.Key)
	}
	fmt.Println()
}