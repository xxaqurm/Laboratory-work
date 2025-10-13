#ifndef STRATEGIES_H
#define STRATEGIES_H

using namespace std;

bool every23(int round_number, vector<bool> self_choices, vector<bool> enemy_choices);
bool grimTrigger(int round_number, vector<bool> self_choices, vector<bool> enemy_choices);
bool titForTat(int round_number, vector<bool> self_choices, vector<bool> enemy_choices);

#endif