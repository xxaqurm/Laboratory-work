package main

func enemyHasBetrayed(arr []bool) bool {
	for _, v := range arr {
		if !v {
			return true
		}
	}
	return false
}

func every23(round int, self []bool, enemy []bool) bool {
	if round%23 == 0 {
		return false
	}
	return true
}

func grimTrigger(round int, self []bool, enemy []bool) bool {
	if enemyHasBetrayed(enemy) {
		return false
	}
	return true
}

func titForTat(round int, self []bool, enemy []bool) bool {
	if len(enemy) == 0 {
		return true
	}
	return enemy[len(enemy)-1]
}
