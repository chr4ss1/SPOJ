#include <stdio.h>
#include <utility>
#include <queue>
#include <vector>
#include <map>


using namespace std;


int main()
{
  int testCases;
	scanf("%d", &testCases);
	while(testCases--)
	{
		int weightOfEmptyPig;
		int weightOfRequired;
		int coins;

		scanf("%d %d", &weightOfEmptyPig, &weightOfRequired);
		scanf("%d", &coins);

		vector<pair<int, int> > coinList;
		for(int j = 0; j < coins; j++)
		{
			int value, weight;
			scanf("%d %d", &value, &weight);

			coinList.push_back(make_pair(value, weight));
		}

		if(weightOfRequired == weightOfEmptyPig)
		{
			printf("This is impossible.\r\n");
			continue;
		}




		int ck = weightOfRequired - weightOfEmptyPig+1;
		int *xd = new int[ck];
		for(int i = 0; i < ck; i++) 
			xd[i] = -1;

		xd[0] = 0;
		
		for(int weightOffset = 1; weightOffset < ck; weightOffset++)
		{
			int useless = true;
			for(int coin = 0; coin < coinList.size(); coin++)
			{
				int coinWeight = coinList[coin].second;
				int coinValue = coinList[coin].first;

				if(weightOffset - coinWeight < 0) continue;

				int rx = xd[weightOffset - coinWeight];
				if(rx == -1) continue;

				rx += coinValue;
				if(rx < xd[weightOffset] || xd[weightOffset] == -1) 
					xd[weightOffset] = rx;
			}
		}


		int a = xd[ck - 1];
		if(a == -1)
			printf("This is impossible.\r\n");
		else
			printf("The minimum amount of money in the piggy-bank is %d.\r\n", a);

	}

	return 0;
}

