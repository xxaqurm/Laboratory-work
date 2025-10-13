package forwardlist

type Node[T comparable] struct {
	Value T
	Next  *Node[T]
}

type ForwardList[T comparable] struct {
	head *Node[T]
}

func New[T comparable]() *ForwardList[T] {
	return &ForwardList[T]{head: nil}
}

func (fl *ForwardList[T]) PushFront(value T) {
	fl.head = &Node[T]{Value: value, Next: fl.head}
}

func (fl *ForwardList[T]) PushBack(value T) {
	if fl.head == nil {
		fl.head = &Node[T]{Value: value}
		return
	}
	curr := fl.head
	for curr.Next != nil {
		curr = curr.Next
	}
	curr.Next = &Node[T]{Value: value}
}

func (fl *ForwardList[T]) InsertAfter(index int, value T) bool {
	curr := fl.head
	i := 0
	for curr != nil && i < index {
		curr = curr.Next
		i++
	}
	if curr == nil {
		return false
	}
	curr.Next = &Node[T]{Value: value, Next: curr.Next}
	return true
}

func (fl *ForwardList[T]) InsertBefore(index int, value T) bool {
	if index == 0 {
		fl.PushFront(value)
		return true
	}
	curr := fl.head
	i := 0
	for curr != nil && i < index-1 {
		curr = curr.Next
		i++
	}
	if curr == nil || curr.Next == nil {
		return false
	}
	curr.Next = &Node[T]{Value: value, Next: curr.Next}
	return true
}

func (fl *ForwardList[T]) PopFront() (T, bool) {
	if fl.head == nil {
		var zero T
		return zero, false
	}
	val := fl.head.Value
	fl.head = fl.head.Next
	return val, true
}

func (fl *ForwardList[T]) PopBack() (T, bool) {
	if fl.head == nil {
		var zero T
		return zero, false
	}
	if fl.head.Next == nil {
		val := fl.head.Value
		fl.head = nil
		return val, true
	}
	curr := fl.head
	for curr.Next.Next != nil {
		curr = curr.Next
	}
	val := curr.Next.Value
	curr.Next = nil
	return val, true
}

func (fl *ForwardList[T]) RemoveByValue(value T) bool {
	if fl.head == nil {
		return false
	}
	if fl.head.Value == value {
		fl.head = fl.head.Next
		return true
	}
	curr := fl.head
	for curr.Next != nil && curr.Next.Value != value {
		curr = curr.Next
	}
	if curr.Next == nil {
		return false
	}
	curr.Next = curr.Next.Next
	return true
}

func (fl *ForwardList[T]) Find(value T) bool {
	curr := fl.head
	for curr != nil {
		if curr.Value == value {
			return true
		}
		curr = curr.Next
	}
	return false
}

func (fl *ForwardList[T]) Read() []T {
	var result []T
	curr := fl.head
	for curr != nil {
		result = append(result, curr.Value)
		curr = curr.Next
	}
	return result
}

func (fl *ForwardList[T]) ReadReverse() []T {
	var result []T
	curr := fl.head
	for curr != nil {
		result = append([]T{curr.Value}, result...)
		curr = curr.Next
	}
	return result
}
