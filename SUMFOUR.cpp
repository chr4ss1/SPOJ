#include<iostream>
#include<algorithm>
#include <string>
#include<cstdio>
#include <map>
#include <vector>
using namespace std;



int main(){

  int n;
	scanf("%d", &n);

	vector<int> lanes[4];
	while(n--){
		int A, B, C, D;
		scanf("%d %d %d %d", &A, &B, &C, &D);

		lanes[0].push_back(A);
		lanes[1].push_back(B);
		lanes[2].push_back(C);
		lanes[3].push_back(D);
	}

	vector<int> sum;
	for(int j = 0; j < lanes[0].size(); j++){
		for(int k = 0; k < lanes[1].size(); k++){
			sum.push_back(lanes[0][j] + lanes[1][k]);
		}
	}

	sort(sum.begin(), sum.end());

	int count = 0;
	for(int j = 0; j < lanes[2].size(); j++){
		for(int k = 0; k < lanes[3].size(); k++){
			int val = -(lanes[2][j] + lanes[3][k]);

			vector<int>::iterator up = upper_bound(sum.begin(), sum.end(), val);
			vector<int>::iterator lo = lower_bound(sum.begin(), sum.end(), val);

			count += up - lo;
		}
	}

	printf("%d\n", count);
   return 0;
}
