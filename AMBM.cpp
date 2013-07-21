#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <map>
#include <queue>
#include <math.h>
#include <algorithm>
#include <iterator>
#include <sstream>

#define SUPERINT unsigned long long

using namespace std;

SUPERINT a[50];
SUPERINT b[50];

int main() {

  int t;
	scanf("%d", &t);

	while(t--){

		int K;
		SUPERINT N;
		SUPERINT exp = 1;

		scanf("%llu %d", &N, &K);
		for(int j = 0; j < K; j++){
			scanf("%llu", &a[j]);

			b[j] = (b[j-1] << 1) + a[j];
		}

		vector<int> wr;
		for(int j = K - 1; j >= 0 && N; j--){
			if(N >= b[j]){
				wr.push_back(j + 1);
				N -= b[j];
			}

			if(N < 0) 
				break;
		}

		if(wr.empty() || N){
			printf("-1\n");
			continue;
		}

		for(int j = wr.size() - 1; j >= 0; j--){
			if(j < wr.size() - 1) printf(" ");
			printf("%d", wr[j]);
		}
		printf("\n");
	}
	return 0;
}
