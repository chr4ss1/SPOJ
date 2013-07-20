#include <iostream>
#include <string>
#include <vector>
#include <string.h>
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


#define MAX_LENGTH 15


char hash_map[101][MAX_LENGTH + 1];

int calculate_hash(char *buff)
{
	int hash	= 0;
	int pos		= 1;

	while(*buff){
		hash += *buff * pos;
		buff++;
		pos++;
	}

	return (hash * 19) % 101;
}

void insert_string(char *buff)
{
	int hash	= calculate_hash(buff);
	int j	= 0;

	for(int k = 0; k < 101; k++){
		if(!strcmp(hash_map[k], buff))
			return;
	}

	while(j < 20){
		int pos = (hash + j*j + 23*j) % 101;
		if(hash_map[pos][0] == 0){
			strcpy(hash_map[pos], buff);
			return;
		} else{
			if(strcmp(hash_map[pos], buff) == 0)
				return;
		}

		j++;
	}
}

void delete_string(char *buff)
{
	int j	= 0;	
	while(j < 101){
		if(strcmp(hash_map[j], buff) == 0){
			memset(hash_map[j], 0, sizeof(16 * sizeof(char)));
			return;
		}

		j++;
	}
}


int main() {
	parse_data();

	int T = extract_int();
	while(T--){
		int N = extract_int();

		memset(hash_map, 0, sizeof(hash_map));
		// 1=null terminator
		// 2=ADD: or DEL: both 4 characters
		char temp[MAX_LENGTH + 1 + (4)];
		while(N--){
			extract_string(temp);
			
			bool add_op = (strncmp(temp, "ADD:", 4) == 0);
			if(add_op)	insert_string(temp + 4);
			if(!add_op)	delete_string(temp + 4);
		}

		int count = 0;
		for(int j = 0; j < 101; j++){
			if(hash_map[j][0]) 
				count++;
		}

		printf("%d\n", count);
		for(int j = 0; j < 101; j++){
			if(hash_map[j][0]){
				printf("%d:%s\n", j, hash_map[j]);
			}
		}
	}
	return 0;
}
