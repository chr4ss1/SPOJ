#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define MAX_CHUNK_SIZE 65536
#define IS_WHITESPACE(x) (((x == 13) || (x == 10) || (x == ' ')))

char arr[10000000] = {0};
char *ptr = arr;
char *end_ptr;
int total;

void parse_data()
{
  int c, j;
	char *ptr = arr;

	while((c = fread(ptr, 1, MAX_CHUNK_SIZE, stdin)) > 0) ptr += c;

	end_ptr = ptr;
	ptr = arr;
}
inline void skip_whitespaces(){while(IS_WHITESPACE(*ptr)) ptr++;}
inline int extract_int()
{
	skip_whitespaces();

	char *p;
	int number = strtol(ptr, &p, 10);
	number = ptr == p ? -1 : number;

	while(*ptr >= '0' && *ptr <= '9')ptr++;
	return number;
}

inline int extract_string(char *buff)
{
	skip_whitespaces();
	while(*ptr == ' ') ptr++;

	char *beginning = buff;
	while(*ptr != 13 && *ptr != 10 && *ptr != ' ' && ptr < end_ptr) *buff++ = *ptr++;

	*buff = 0;
	return buff - beginning;
}

#define SUPERINT long long int

int main() {
	parse_data();

	int test_cases = extract_int();
	while(test_cases--){
		int N = extract_int();

		vector<pair<SUPERINT, int> > girls(N);
		for(int i = 0; i < N; i++){
			SUPERINT height = extract_int();
			girls[i] = make_pair<SUPERINT, int>(height, i+1);
		}
		
		// sort by height.
		sort(girls.begin(), girls.end());

		priority_queue<SUPERINT> less;
		priority_queue<SUPERINT, vector<SUPERINT>, greater<SUPERINT> > bigger;

		SUPERINT best = 0;
		for(int i = N - 1; i >= 0; i--){
			if(!less.empty()){
				best = max(best, abs(less.top()		- girls[i].second) * girls[i].first);
				best = max(best, abs(bigger.top()	- girls[i].second) * girls[i].first);
			}

			less.push(girls[i].second);
			bigger.push(girls[i].second);
		}

		printf("%lld\n", best);
	}
	return 0;
}
