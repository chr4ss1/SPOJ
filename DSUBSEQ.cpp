#include <stdio.h>
#include <string.h>

#define MAX_MOD 1000000007

char str[100001];

int main()
{
	int test_cases;
	scanf("%d", &test_cases);
	while(test_cases--){
		scanf("%s", str);

		int len = strlen(str);
		int last_occurence;
		unsigned characters[100] = {0};

		// let's create an array that represents how many distinct subsequences we have, 
		// if we can use only i first characters.
		// let's call it dp.
		// dp[0] since we have no characters to use, but empty subsequence is still valid one!
		int *dp = new int[len+1];
		dp[0] = 1;

		for(int i = 1; i <= len; i++){
			last_occurence = characters[str[i-1]];

			// basically, if we have one more character to use,
			// we can generate TWICE the amount of subsequences.
			// 2^n to be correct.
			dp[i] = dp[i-1]<<1;

			// but the trick here is, that we need to count distinct subsequences.
			// for that, we keep track of the last character that is same as str[i-1],
			// if we have such, then we subtract the ones that regenerate DUPLICATE subsequences again.
			// we don't need them.
			if(last_occurence)
				dp[i] -= dp[last_occurence - 1];

			// set up last occurence for specific character
			characters[str[i-1]] = i;
			
			// don't let it grow too much.
			// our final answer will be too big, we just have to keep it small.
			// (X+N+E+M) % MOD  == X%MOD + N%MOD + E%MOD + M%MOD
			// it can grow either way, just make sure we keep it correct.
			dp[i] -= dp[i] > MAX_MOD ? MAX_MOD : 0;
			dp[i] += dp[i] < 0 ? MAX_MOD : 0;
		}

		printf("%d\r\n", dp[len]);
		delete [] dp;
	}

	return 0;
}