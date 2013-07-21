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

vector<string> split_to_words(string s)
{
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	return vstrings;
}

int main() {
	
	string line;
	while(getline(cin, line)){
		vector<string> words = split_to_words(line);
		map<string, int> word_count;
		vector<int> table;

		long long sum = 0;
		for(int j = 0; j < words.size(); j++){
			string data = words[j];
			word_count[data] += 1;
		}

		for(map<string, int>::iterator it = word_count.begin(); it != word_count.end(); it++){
			if(it->second > 1){
				int possible_pairs = it->second * (it->second - 1) / 2;
				sum += (possible_pairs) * (sum + 1);
			}
		}

		printf("%lld\n", sum);
	}

	return 0;
}
