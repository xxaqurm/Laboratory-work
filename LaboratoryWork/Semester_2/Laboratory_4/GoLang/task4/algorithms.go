package main

func bordaMethod(candidates map[string]int, voters map[string][]string) string {
	score := make(map[string]int)
	for k := range candidates {
		score[k] = 0
	}
	for _, votes := range voters {
		for i, name := range votes {
			score[name] += len(votes) - i - 1
		}
	}
	maxScore := 0
	winner := ""
	for name, val := range score {
		if val > maxScore {
			maxScore = val
			winner = name
		}
	}
	count := 0
	for _, val := range score {
		if val == maxScore {
			count++
		}
	}
	if count > 1 {
		return "NONE"
	}
	return winner
}

func condorcetMethod(candidates map[string]int, voters map[string][]string) string {
	names := []string{}
	for name := range candidates {
		names = append(names, name)
	}
	for _, candA := range names {
		isWinner := true
		for _, candB := range names {
			if candA == candB {
				continue
			}
			wins := 0
			losses := 0
			for _, prefs := range voters {
				posA := findIndex(prefs, candA)
				posB := findIndex(prefs, candB)
				if posA < posB {
					wins++
				} else {
					losses++
				}
			}
			if wins <= losses {
				isWinner = false
				break
			}
		}
		if isWinner {
			return candA
		}
	}
	return "NONE"
}

func findIndex(slice []string, target string) int {
	for i, v := range slice {
		if v == target {
			return i
		}
	}
	return len(slice)
}
