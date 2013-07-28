#include<iostream>
#include<algorithm>
#include<cstdio>
#include <map>
#include <vector>
using namespace std;

#define SUPERINT long long

int main(){
  int t;
	int n;
	scanf("%d", &t);
	for(int w = 1; w <= t; w++){
		scanf("%d", &n);

		bool all_positive = true;
		SUPERINT cur_energy = 0;
		SUPERINT answer     = 0;

		for(int j = 0; j < n; j++){
			int coke;
			scanf("%d", &coke);

			if(coke < 0) 
				all_positive = false;
		
			cur_energy += coke;
			answer = min(cur_energy, answer);
		}

		printf("Scenario #%d: %lld\n", w, all_positive ? 1 : -answer + 1);
	}

   return 0;
}
