#include <stdio.h>
#include <string.h>
#include <utility>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct chill
{
  int stall_from_zero;
	int left_diff;
	int right_diff;

	int winrar;
	int pos;

	bool operator < (const chill& e) const
    {
		return (stall_from_zero < e.stall_from_zero);
    }
};

#define MAX_STALLS 100000

chill stalls[MAX_STALLS];


bool is_valid(int diff, int stall_count, int cows)
{
	int a = stalls[0].stall_from_zero;
	int wins = 1;

	for(int j = 1; j < stall_count; j++)
	{
		if(stalls[j].stall_from_zero - a >= diff)
		{
			wins++;
			a = stalls[j].stall_from_zero;
		}
	}

	return wins >= cows;
}


int exck()
{
	int test_cases;
	scanf("%d", &test_cases);

	while(test_cases--)
	{
		int N; // stalls
		int C; // cows

		scanf("%d %d", &N, &C);

		int xc;
		for(int i = 0; i < N; i++)
		{
			chill e;
			e.left_diff = -1;
			e.right_diff = -1;
			e.winrar = 0;
			e.pos = i;
			e.stall_from_zero = 0;

			scanf("%d", &e.stall_from_zero);

			stalls[i] = e;
		}

		// phase1; sort all stalls, nlogn. that's about second.
		// sort them by length
		sort(stalls, stalls + N);

		//0 <= xi <= 1,000,000,000

		// answer can't be zero!
		// possible answes range 1 <= x <= 1 billion
		int low = 1;
		int high = 1000000000;

		int answer = 0;

		while(low <= high)
		{
			int mid = (low + high) / 2;
			bool d = is_valid(mid, N, C);

			if(d)
			{
				answer = mid;
				low = mid+1;
			} else
			{
				high = mid-1;
			}
		}

		printf("%d\r\n", answer);
	}
	return 0;
}

