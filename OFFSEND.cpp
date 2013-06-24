#include <stdio.h>
#include <utility>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;



int main()
{

  int A, D;
	while(true)
	{
		scanf("%d %d", &A, &D);
		if(A == 0 && D == 0) 
			break;

		vector<int> attacking_players;
		vector<int> defending_players;

		// scan attacking players
		for(int k = 0; k < A; k++) 
		{
			int g;
			scanf("%d", &g);
			attacking_players.push_back(g);
		}

		// scan defending players
		for(int k = 0; k < D; k++) 
		{
			int g;
			scanf("%d", &g);
			defending_players.push_back(g);
		}

		sort(attacking_players.begin(), attacking_players.end());
		sort(defending_players.begin(), defending_players.end());

		bool offside = false;
		for(int k = 0; k < A; k++)
		{
			if(attacking_players[k] < defending_players[0] ||
				attacking_players[k] < defending_players[1])
			{
				offside = true;
				break;
			}
		}

		printf("%c\r\n", offside ? 'Y' : 'N');
	}

	return 0;
}

