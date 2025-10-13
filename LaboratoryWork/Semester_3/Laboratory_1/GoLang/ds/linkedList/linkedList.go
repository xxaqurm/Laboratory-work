package linkedlist

type Node[T comparable] struct {
	Value T
	Prev  *Node[T]
	Next  *Node[T]
}

type LinkedList[T comparable] struct {
	head *Node[T]
	tail *Node[T]
}

func New[T comparable]() *LinkedList[T] {
	return &LinkedList[T]{head: nil, tail: nil}
}

func (ll *LinkedList[T]) PushFront(value T) {
	node := &Node[T]{Value: value, Next: ll.head}
	if ll.head != nil {
		ll.head.Prev = node
	}
	ll.head = node
	if ll.tail == nil {
		ll.tail = node
	}
}

func (ll *LinkedList[T]) PushBack(value T) {
	node := &Node[T]{Value: value, Prev: ll.tail}
	if ll.tail != nil {
		ll.tail.Next = node
	}
	ll.tail = node
	if ll.head == nil {
		ll.head = node
	}
}

func (ll *LinkedList[T]) InsertAfter(index int, value T) bool {
	curr := ll.head
	i := 0
	for curr != nil && i < index {
		curr = curr.Next
		i++
	}
	if curr == nil {
		return false
	}
	node := &Node[T]{Value: value, Next: curr.Next, Prev: curr}
	if curr.Next != nil {
		curr.Next.Prev = node
	}
	curr.Next = node
	if node.Next == nil {
		ll.tail = node
	}
	return true
}

func (ll *LinkedList[T]) InsertBefore(index int, value T) bool {
	if index == 0 {
		ll.PushFront(value)
		return true
	}
	curr := ll.head
	i := 0
	for curr != nil && i < index {
		curr = curr.Next
		i++
	}
	if curr == nil {
		return false
	}
	node := &Node[T]{Value: value, Next: curr, Prev: curr.Prev}
	if curr.Prev != nil {
		curr.Prev.Next = node
	}
	curr.Prev = node
	return true
}

func (ll *LinkedList[T]) PopFront() (T, bool) {
	if ll.head == nil {
		var zero T
		return zero, false
	}
	val := ll.head.Value
	ll.head = ll.head.Next
	if ll.head != nil {
		ll.head.Prev = nil
	} else {
		ll.tail = nil
	}
	return val, true
}

func (ll *LinkedList[T]) PopBack() (T, bool) {
	if ll.tail == nil {
		var zero T
		return zero, false
	}
	val := ll.tail.Value
	ll.tail = ll.tail.Prev
	if ll.tail != nil {
		ll.tail.Next = nil
	} else {
		ll.head = nil
	}
	return val, true
}

func (ll *LinkedList[T]) RemoveByValue(value T) bool {
	curr := ll.head
	for curr != nil {
		if curr.Value == value {
			if curr.Prev != nil {
				curr.Prev.Next = curr.Next
			} else {
				ll.head = curr.Next
			}
			if curr.Next != nil {
				curr.Next.Prev = curr.Prev
			} else {
				ll.tail = curr.Prev
			}
			return true
		}
		curr = curr.Next
	}
	return false
}

func (ll *LinkedList[T]) Find(value T) bool {
	curr := ll.head
	for curr != nil {
		if curr.Value == value {
			return true
		}
		curr = curr.Next
	}
	return false
}

func (ll *LinkedList[T]) Read() []T {
	var result []T
	curr := ll.head
	for curr != nil {
		result = append(result, curr.Value)
		curr = curr.Next
	}
	return result
}

func (ll *LinkedList[T]) ReadReverse() []T {
	var result []T
	curr := ll.tail
	for curr != nil {
		result = append(result, curr.Value)
		curr = curr.Prev
	}
	return result
}