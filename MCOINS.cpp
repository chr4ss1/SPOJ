#include <stdio.h>
#include <utility>
#include <string.h>
#include <map>
#include <math.h>
#include <algorithm>

using namespace std;

// this is completely related to I/O and has nothing to do with problem itself.
#define MAX_CHUNK_SIZE 65536

char arr[10000000] = {0};
char *ptr = arr;

// I wrote this custom function in order to get
// better running times in SPOJ.
// This can take your 5 seconds to 1 seconds with big INPUT/OUTPUT :)
void parse_data()
{
  //FILE * pFile;
	//pFile = fopen ( "C:\\test_case.txt" , "rb" );

	int c, j;
	char *ptr = arr;
	
	// read data into buffer!
	while((c = fread(ptr, 1, MAX_CHUNK_SIZE, stdin))>0)
		ptr += MAX_CHUNK_SIZE;

	// reset ptr to beginning.
	ptr = arr;
}

// A simple inline function that can extract integer from buffer.
inline int extract_int()
{
	// skip all stupid whitespaces.
	while(*ptr == 13 || *ptr == 10 || *ptr == ' ') ptr++;

	int wtf = atoi(ptr);

	// skip the integer
	while(*ptr >= '0' && *ptr <= '9') ptr++;
	return wtf;
}

#define MAX_GAMES 50
#define BIGGEST_TOWER 1000000

int K, L, m;
int towers[MAX_GAMES];

int memo[BIGGEST_TOWER + 1] = {0};//true=WIN,false=LOSE!

int mxx()
{
	parse_data();

	K = extract_int();
	L = extract_int();
	m = extract_int();

	for(int j = 0; j < m; j++) towers[j] = extract_int();
	for(int j = 1; j <= BIGGEST_TOWER; j++){
		if(memo[j - 1] == 0) memo[j] = 1;
		else if(j - K >= 0 && memo[j - K] == 0)  memo[j] = 1;
		else if(j - L >= 0 && memo[j - L] == 0)  memo[j] = 1;
	}

	for(int k = 0; k < m; k++){
		printf("%c", memo[towers[k]] ? 'A' : 'B');
	}


	return 0;
}

