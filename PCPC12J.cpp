#include <stdio.h>
#include <utility>
#include <string.h>
#include <map>
#include <algorithm>

using namespace std;

typedef map<int, int> intmap;
typedef pair<int, int> intpair;

int ra()
{
  int test;
	scanf("%d", &test);
	while(test--){
		int i, lucky;
		scanf("%d", &lucky);
		i = lucky;

		intmap lucky_divisors;
		while(i--){
			int d;
			scanf("%d", &d);

			if(lucky_divisors.find(d) == lucky_divisors.end())
				lucky_divisors[d] = 0;

			lucky_divisors[d] += 1;
		}

		// lucky=f
		int best_freq = -1;
		int best_divisor = -1;

		for(intmap::iterator it = lucky_divisors.begin(); it != lucky_divisors.end(); it++){
			int divisor = it->first;
			int frequency = it->second;
			if(divisor && frequency % divisor == 0){
				if(best_freq == -1){
					best_freq = frequency;
					best_divisor = divisor;
					continue;
				}

				if(best_freq == frequency && best_divisor > divisor){
					best_divisor = divisor;
					continue;
				}

				if(frequency > best_freq){
					best_freq = frequency;
					best_divisor = divisor;
				}

			}
		}

		printf("%d\n", best_divisor);
	}

	return 0;
}

