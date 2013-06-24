#include <stdio.h>
#include <utility>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;


int main()
{
  while(true)
	{
		int budget, parties;

		scanf("%d %d", &budget, &parties);
		if(budget == 0 && parties == 0)
			break;

		int bx[101][501][2] = {0};
		int partyCount = parties;

		vector<pair<int, int>> vec;
		int index = 0;
		while(parties--)
		{
			int fun, fee;
			scanf("%d %d", &fee, &fun);

			bx[index][fee][0] = fun;
			bx[index][fee][1] = fee;

			vec.push_back(make_pair<int, int>(fun, fee));
			index++;
		}

		// start building from zero.
		for(int party = 0; party < partyCount; party++)
		{
			int partyFun = vec[party].first;
			int partyFee = vec[party].second;

			int partyIndex = party + 1;

			for(int currentBudget = 1; currentBudget <= budget; currentBudget++)
			{
				int previousFunWithoutParty = bx[partyIndex-1][currentBudget][0];
				int previousBudgetWithoutParty = bx[partyIndex-1][currentBudget][1];

				// assume explictly that this is best choice
				// eg the same choice that was previously, but using parties 0..partyIndex-1
				bx[partyIndex][currentBudget][0] = previousFunWithoutParty;
				bx[partyIndex][currentBudget][1] = previousBudgetWithoutParty;
				
				// can we possibly do better?
				if(currentBudget - partyFee >= 0)
				{
					int funWithParty = bx[partyIndex - 1][currentBudget - partyFee][0] + partyFun;
					int feeWithParty = bx[partyIndex - 1][currentBudget - partyFee][1] + partyFee;

					if(previousFunWithoutParty < funWithParty)
					{
						bx[partyIndex][currentBudget][0] = funWithParty;
						bx[partyIndex][currentBudget][1] = feeWithParty;
					}
				}
			}
		}

		printf("%d %d\r\n", bx[vec.size()][budget][1], bx[vec.size()][budget][0]);
	}

	return 0;
}

