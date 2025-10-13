package main

import (
	"fmt"
	"math/rand"
	"time"
)

var POINTS = [][]int{
	{4, 20},
	{0, 24},
}

type Strategy func(int, []bool, []bool) bool

func main() {
	rand.Seed(time.Now().UnixNano())
	cntRounds := rand.Intn(101) + 100
	algorithmNum := func() int {
		return rand.Intn(3)
	}

	algorithmNames := map[int]string{
		0: "every23",
		1: "grimTrigger",
		2: "titForTat",
	}

	firstAlgorithm := algorithmNum()
	secondAlgorithm := algorithmNum()
	for firstAlgorithm == secondAlgorithm {
		secondAlgorithm = algorithmNum()
	}

	fmt.Println("Rounds:", cntRounds)
	fmt.Println()
	fmt.Println("First algorithm:", algorithmNames[firstAlgorithm])
	fmt.Println("Second algorithm:", algorithmNames[secondAlgorithm])
	fmt.Println()

	strategies := []Strategy{
		every23,
		grimTrigger,
		titForTat,
	}

	historyFirst := []bool{}
	historySecond := []bool{}

	pointsFirst := 0
	pointsSecond := 0

	for i := 0; i < cntRounds; i++ {
		moveFirst := strategies[firstAlgorithm](i+1, historyFirst, historySecond)
		moveSecond := strategies[secondAlgorithm](i+1, historySecond, historyFirst)

		historyFirst = append(historyFirst, moveFirst)
		historySecond = append(historySecond, moveSecond)

		var valFirst, valSecond int
		if moveFirst {
			if moveSecond {
				valFirst = POINTS[1][1]
				valSecond = POINTS[1][1]
			} else {
				valFirst = POINTS[1][0]
				valSecond = POINTS[0][1]
			}
		} else {
			if moveSecond {
				valFirst = POINTS[0][1]
				valSecond = POINTS[1][0]
			} else {
				valFirst = POINTS[0][0]
				valSecond = POINTS[0][0]
			}
		}

		pointsFirst += valFirst
		pointsSecond += valSecond
	}

	if pointsFirst > pointsSecond {
		fmt.Println("First algorithm win!")
	} else if pointsFirst < pointsSecond {
		fmt.Println("Second algorithm wins!")
	} else {
		fmt.Println("It's a draw!")
	}

	fmt.Println("First algorithm points:", pointsFirst)
	fmt.Println("Second algorithm points:", pointsSecond)
}
