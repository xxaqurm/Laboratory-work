package ds

import "math"

type BSTNode struct {
	Val   int
	Left  *BSTNode
	Right *BSTNode
}

type BST struct {
	Root *BSTNode
}

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