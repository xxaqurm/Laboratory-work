#include <vector>
#include "strategies.h"

using namespace std;

bool enemyHasBetrayed(vector<bool> arr) {
    /* Проверяет на предательство */
    for (int i = 0; i < arr.size(); i++) {
        if (!arr[i]) {
            return true;
        }
    }
    return false;
}

bool every23(int round_number, vector<bool> self_choices, vector<bool> enemy_choices) {
    /* Прредавать каждый 23 раунд */
    if (round_number % 23 == 0) {
        return false;
    }
    return true;
}

bool grimTrigger(int round_number, vector<bool> self_choices, vector<bool> enemy_choices) {
    /* Никогда не сотрудничать с тем, кто предал */
    if (enemyHasBetrayed(enemy_choices)) {
        return false;
    }
    return true;
}

bool titForTat(int round_number, vector<bool> self_choices, vector<bool> enemy_choices) {
    /* Сначала сотрудничать, потом делать так, как противник */
    if (enemy_choices.empty()) {
        return true;
    }
    return enemy_choices.back();
}