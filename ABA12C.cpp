#include <stdio.h>
#include <utility>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map<int, int> solutions;
// this algorithm solves the next problem;
// what is minimum price we have to pay, 
// in order to buy "amount" KG of apples.
// note that prices[0](1KG) = price of 1KG
// note that prices[1](2KG) = price of 2KG
int Solve(int amount, vector<int> &prices)
{
  if(amount == 0)  return 0;
	if(amount < 0) return -1;
	if(amount == 1) return prices[0];

	map<int, int>::iterator it = solutions.find(amount);
	if(it != solutions.end()) return it->second;

	int best = -1;
	for(int k = 0; k < prices.size(); k++)
	{
		int nw = amount - (k + 1);
		if(nw >= 0 && nw < amount)
		{
			int possible_answer = Solve(nw, prices);
			if(possible_answer == -1) continue;
			
			possible_answer += prices[k];
			if(best == -1)  best = possible_answer;
			else if(possible_answer < best) best = possible_answer;
		}
	}

	solutions[amount] = best;
	return best;
}


int dksoap()
{
	int test_cases;
	scanf("%d", &test_cases);
	while(test_cases--)
	{
		solutions.clear();

		int N; // number of friends
		int K; // KG of apples he should buy.
		scanf("%d %d", &N, &K);

		vector<int> prices(K);
		for(int x = 0; x < K; x++) scanf("%d", &prices[x]);
		
		if(K == 0) 
		{
			printf("0\r\n");
			continue;
		}

		printf("%d\r\n", Solve(K, prices));
	}

	return 0;
}

