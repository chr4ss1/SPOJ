#include <iostream>
#include <string>
#include <vector>
#include <string.h>
using namespace std;

struct item
{
  int type;
	int price;
	int quality;
};

vector<vector<item> > shop(7);

int main() {
	int items, rublas;
	scanf("%d %d", &items, &rublas);

	int flags[7];
	memset(flags, -1, sizeof(flags));

	while(items--){
		item it;
		scanf("%d %d %d", &it.type, &it.price, &it.quality);

		if(it.type < 1 || it.type > 6) continue;

		flags[it.type] = flags[it.type] == -1 ? it.price : min(flags[it.type], it.price);
		shop[it.type].push_back(it);
	}

	for(int j = 1, cur = rublas; j <= 6; j++){
		if(flags[j] == -1){
			printf("0\n");
			return 0;
		}
		cur -= flags[j];
		if(cur < 0){
			printf("0\n");
			return 0;
		}
	}

	int dp[7][1200];
	memset(dp, -1, sizeof(dp));

	for(int i = 0; i < 1200; i++){
		for(int j = 0; j < shop[1].size(); j++){
			item it = shop[1][j];
			if(i - it.price < 0) continue;

			dp[1][i] = max(dp[1][i], it.quality);
		}
	}

	for(int shop_index = 2; shop_index <= 6; shop_index++){
		for(int rub = 1; rub < 1200; rub++){
			dp[shop_index][rub] = -1; 
			for(int ex = 0; ex < shop[shop_index].size(); ex++){
				item cur_item = shop[shop_index][ex];
				if(rub - cur_item.price < 0)						continue; 
				int rw = min(dp[shop_index - 1][rub - cur_item.price], cur_item.quality);
				if(dp[shop_index][rub] == -1)					dp[shop_index][rub] = rw;

				dp[shop_index][rub] = max(dp[shop_index][rub], rw);
			}
		}
	}

	printf("%d\n", dp[6][rublas]);
	return 0;
}
