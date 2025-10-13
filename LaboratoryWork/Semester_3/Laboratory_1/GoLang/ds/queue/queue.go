package queue

type Queue[T any] struct {
	items []T
}

func New[T any]() *Queue[T] {
	return &Queue[T]{items: []T{}}
}

func (q *Queue[T]) Push(item T) {
	q.items = append(q.items, item)
}

func (q *Queue[T]) Pop() (T, bool) {
	if len(q.items) == 0 {
		var zero T
		return zero, false
	}
	item := q.items[0]
	q.items = q.items[1:]
	return item, true
}

func (q *Queue[T]) Read() []T {
	return q.items
}