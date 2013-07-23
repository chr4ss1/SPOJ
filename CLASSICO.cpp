
int players[2000];
int player_count;

vector<int> pick_best_team(int players_left, int players_to_pick)
{
  // basecase!
	if(!players_to_pick || !players_left) 
		return vector<int>();

	// how many indexes can we consider?
	int best_choice = 0;
	int start_index = player_count - players_left;

	for(int j = 1; j <= players_left - players_to_pick; j++){
		if(players[start_index + j] > players[start_index + best_choice])
			best_choice = j;
	}

	vector<int> result = pick_best_team(players_left - best_choice - 1, players_to_pick - 1);
	result.insert(result.begin(), players[start_index + best_choice]);
	return result;
}

int main() {
	int t;
	scanf("%d", &t);

	for(int c = 1; t; t--, c++){
		scanf("%d", &player_count);
		for(int j = 0; j < player_count; j++)
			scanf("%d", &players[j]);

		if(player_count < 11){
			printf("Case %d: go home!\n", c);
			continue;
		}

		// start raping this shit.
		printf("Case %d: ", c);
		vector<int> res = pick_best_team(player_count, 11);
		for(int k = 0; k < res.size(); k++){
			if(k > 0) 
				printf(" ");

			printf("%d", res[k]);
		}

		printf("\n");
	}
	return 0;
}
