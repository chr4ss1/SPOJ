#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

#define MAX_ENTRIES 101

struct entry
{
  int enters;
	int leaves;

	
	bool operator < (const entry& e) const
	{
		return (enters < e.enters);
    }

} ENTRIES[MAX_ENTRIES] = {0};

int T, N;
int people;

int extension;
entry last;

int main()
{
	scanf("%d", &T);
	while(T--){
		people = 1;
		extension = 0;

		scanf("%d", &N);
		for(int w = 1; w <= N; w++)
			scanf("%d %d", &ENTRIES[w].enters, &ENTRIES[w].leaves);

		sort(ENTRIES + 1, ENTRIES + N + 1);

		int ce = 0;

		priority_queue<int, vector<int>, greater<int>> que;
		for(int e = 1; e <= N; e++){
			ce++; // we have joined the BALL!

			// check out all the people who leave the BALL.
			while(!que.empty() && que.top() < ENTRIES[e].enters){
				ce--;
				que.pop();
			}

			que.push(ENTRIES[e].leaves);
			people = max(ce, people);
		}
		

		printf("%d\n", people);
	}

	return 0;
}
