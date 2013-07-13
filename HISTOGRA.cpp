#include <iostream>
#include <stdlib.h>
#include <utility>
#include <string.h>

using namespace std;

#define SUPERINT unsigned long long int

int N;
SUPERINT rectangles[100001];

SUPERINT solve(int low, int high)
{
  if(low == high) 
		return rectangles[low];

	int mid = (low + high) / 2;
	SUPERINT ewk = max(solve(low, mid), solve(mid + 1, high));

	int f1 = mid;
	int f2 = mid + 1;
	SUPERINT seen = 1000000005;

	bool initialized = false;
	bool left_valid = true;
	bool right_valid = true;

	while(true){
		if(!left_valid && !right_valid) break;
		if(left_valid && right_valid){
			bool left_bigger = rectangles[f1] > rectangles[f2];
			seen = min(seen, rectangles[left_bigger ? f1 : f2]);
			ewk = max(seen * (f2 - f1), ewk);

			left_valid = left_bigger ? f1 - 1 >= low : left_valid;
			right_valid = left_bigger ? right_valid : f2 + 1 <= high;

			if(left_valid && left_bigger) f1--;
			if(right_valid && !left_bigger) f2++;

			continue;
		}

		seen = min(seen, rectangles[left_valid ? f1 : f2]);
		ewk = max(seen * (f2 - f1 + 1), ewk);

		left_valid = left_valid ?   f1 - 1 >= low : left_valid;
		right_valid = right_valid ? f2 + 1 <= high : right_valid;

		if(left_valid) f1--;
		if(right_valid) f2++;
	}
	

	return ewk;
}

int main()
{
	while(true){
		scanf("%d", &N);
		if(!N) break;
		for(int i = 1; i <= N; i++)
			scanf("%llu", &rectangles[i]);

		printf("%llu\n", solve(1, N));
	}

	return 0;
}
