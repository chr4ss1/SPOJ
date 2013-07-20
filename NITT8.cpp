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

#define SUPERINT int
#define ULTRA_MAX(x, y) (x - ((x - y) & ((x - y) >> (sizeof(int) * 8 - 1))))
#define ULTRA_ABS(x, y) (x > y ? x : y)

pair<SUPERINT, int> girls[100000];
int N, T;
int sml, big;

unsigned long long best;

int main() {
	parse_data();

	T = extract_int();
	while(T--){
		N = extract_int();

		for(int i = 0; i < N; i++){
			girls[i].first	= extract_int();
			girls[i].second = i;
		}

		sort(girls, girls + N);
		sml = big = girls[N - 1].second;
		best = 0;

		for(int i = N - 2; i >= 0; i--){
			best = max(best, 
							ULTRA_MAX(abs(girls[i].second - sml), abs(girls[i].second - big)) 
							* (unsigned long long)girls[i].first);
	
			sml = min(sml, girls[i].second);
			big = max(big, girls[i].second);
		}

		printf("%llu\n", best);
	}
	return 0;
}
