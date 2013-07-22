#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <map>
#include <queue>
#include <math.h>
#include <algorithm>
#include <limits.h>
#include <iterator>
#include <sstream>

using namespace std;

int dp[100000][5];
int row_count;

int main() {
  int t = 0;
	while(scanf("%d", &row_count) == 1 && row_count){
		for(int j = 0; j < row_count; j++){
			scanf("%d %d %d", &dp[j][1], &dp[j][2], &dp[j][3]);

			dp[j][0] = INT_MAX;
			dp[j][4] = INT_MAX;
		}

		dp[0][1] = INT_MAX;
		// start processing nodes
		for(int row = 0; row < row_count; row++){
			for(int element = 1; element <= 3; element++){
				if(!row && element <= 2) continue;

				int best = dp[row][element-1];
				if(row > 0){
					best = min(best, dp[row-1][element+1]);
					best = min(best, dp[row-1][element-1]);
					best = min(best, dp[row-1][element]); 
				}

				dp[row][element] += best;
			}
		}

		++t;
		printf("%d. %d\n", t, dp[row_count - 1][2]);
	}
	return 0;
}

