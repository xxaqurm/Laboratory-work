package ds

import (
	"errors"
	"fmt"
)

type StackNode[T any] struct {
	Key  T
	Next *StackNode[T]
}

type Stack[T any] struct {
	head *StackNode[T]
}

func NewStack[T any]() *Stack[T] {
	return &Stack[T]{head: nil}
}

func (s *Stack[T]) Push(value T) {
	newNode := &StackNode[T]{Key: value, Next: s.head}
	s.head = newNode
}

func (s *Stack[T]) Pop() error {
	if s.head == nil {
		return errors.New("[ERROR] Stack is empty")
	}
	s.head = s.head.Next
	return nil
}

func (s *Stack[T]) Top() (T, error) {
	if s.head == nil {
		var zero T
		return zero, errors.New("[ERROR] Stack is empty")
	}
	return s.head.Key, nil
}

func (s *Stack[T]) Empty() bool {
	return s.head == nil
}

func (s *Stack[T]) Print() {
	for node := s.head; node != nil; node = node.Next {
		fmt.Printf("%v ", node.Key)
	}
	fmt.Println()
}