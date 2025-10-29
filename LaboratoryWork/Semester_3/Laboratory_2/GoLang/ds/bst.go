package ds

import "math"

// BSTNode представляет узел бинарного дерева поиска.
type BSTNode struct {
	Val   int
	Left  *BSTNode
	Right *BSTNode
}

// BST — структура бинарного дерева поиска.
type BST struct {
	Root *BSTNode
}

// Insert добавляет новый элемент в дерево.
func (t *BST) Insert(root *BSTNode, val int) *BSTNode {
	if root == nil {
		return &BSTNode{Val: val}
	}
	if val < root.Val {
		root.Left = t.Insert(root.Left, val)
	} else if val > root.Val {
		root.Right = t.Insert(root.Right, val)
	}
	return root
}

// CheckBalance проверяет балансировку дерева.
// Возвращает высоту поддерева и изменяет isBalanced по ссылке.
func (t *BST) CheckBalance(root *BSTNode, isBalanced *bool) int {
	if root == nil {
		return 0
	}

	leftHeight := t.CheckBalance(root.Left, isBalanced)
	rightHeight := t.CheckBalance(root.Right, isBalanced)

	if math.Abs(float64(leftHeight-rightHeight)) > 1 {
		*isBalanced = false
	}

	if leftHeight > rightHeight {
		return leftHeight + 1
	}
	return rightHeight + 1
}