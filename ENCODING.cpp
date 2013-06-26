#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <string.h>
#include <queue>
#include <stdio.h>

using namespace std;



// this is completely related to I/O and has nothing to do with problem itself.
#define MAX_CHUNK_SIZE 65536
#define IS_WHITESPACE(x) (((x == 13) || (x == 10) || (x == ' ')))
#define CHECK_BIT(var,pos) (((var) & (1<<(pos))) > 0)

char arr[10000000] = {0};
char *ptr = arr;
char *end_ptr;
int total;

// I wrote this custom function in order to get
// better running times in SPOJ.
// This can take your 5 seconds to 1 seconds with big INPUT/OUTPUT :)
void parse_data()
{
  //FILE * pFile;
	//pFile = fopen ( "C:\\Intel\\test_case.txt" , "rb" );

	int c, j;
	char *ptr = arr;

	// read data into buffer!
	while((c = fread(ptr, 1, MAX_CHUNK_SIZE, stdin)) > 0){
		ptr += c;
	}

	// reset ptr to beginning.
	end_ptr = ptr;
	ptr = arr;
}

inline void skip_whitespaces()
{
	while(IS_WHITESPACE(*ptr))
		ptr++;
}

// A simple inline function that can extract integer from buffer.
// If no int could be extracted, -1 is returned.
// be careful!
inline int extract_int()
{
	skip_whitespaces();

	char *p;
	int wtf = strtol(ptr, &p, 10);
	wtf = ptr == p ? -1 : wtf;

	while(*ptr >= '0' && *ptr <= '9') 
		ptr++;

	return wtf;
}

// it does not check buffer overflows.
// we don't need this in SPOJ.
// returns length of string it read.
 inline int extract_string(char *buff)
 {
	 ptr++;

	 char *beginning = buff;
	 while(*ptr != 13 && *ptr != 10 && ptr < end_ptr)
		 *buff++ = *ptr++;
	 
	 *buff = 0;
	 return buff - beginning;
 }

#define MAX_R 21
#define MAX_C 21
#define MAX_STRING (MAX_R * MAX_C / 5 + 1)

 int T;
 int R;
 int C;
 int message_length;
 int val;
 int scenario = 1;

 int x, y;
 int base_x, base_y;
 int max_x, max_y;

 char matrix[MAX_C][MAX_R] = {0};
 char message[MAX_STRING] = {0};
 char binary[6] = {0};


 enum moving_dir
 {
	 left_m,
	 right_m, 
	 down_m,
	 up_m
 };

int main()
{
	parse_data();
	T = extract_int();
	while(T--){
		C = extract_int();
		R = extract_int();
		message_length = extract_string(message);

		// this part is ready,
		// basically it just extracts message, then
		// converts it into binary string.
		printf("%d ", scenario++);
		
		memset(matrix, '0', MAX_C * MAX_R);
		moving_dir dir = left_m;
		max_x = R;
		max_y = C;
		base_x = 0;
		base_y = 0;
		x = 0;
		y = 0;

		for(int j = 0; j < message_length; j++){
			val = message[j] == ' ' ? 0 : message[j] - 'A' + 1;
			binary[0] = CHECK_BIT(val, 4) + '0';
			binary[1] = CHECK_BIT(val, 3) + '0';
			binary[2] = CHECK_BIT(val, 2) + '0';
			binary[3] = CHECK_BIT(val, 1) + '0';
			binary[4] = CHECK_BIT(val, 0) + '0';
			binary[5] = 0;

			// fill our spiral with the information we got.
			for(int v = 0; v < 5; v++){
				matrix[y][x] = binary[v];

				switch(dir){
				case left_m:
					x++;
					if(x == max_x){
						dir = down_m;
						x--;
						y++;
					}

					break;

				case right_m:
					x--;
					if(x < base_x){
						dir = up_m;
						x = base_x;
						y--;
					}
					break;

				case up_m:
					y--;
					if(y - base_x == 0){
						dir = left_m;

						base_x++;
						base_y++;

						x = base_x;
						y = base_y;
						
						max_x -= 1;
						max_y -= 1;
					}
					break;

				case down_m:
					y++;
					if(y == max_y){
						dir = right_m;
						y--;
						x--;
					}

					break;
				}
			}
		}

		// print out everything.
		for(int col = 0; col < C; col++){
			for(int row = 0; row < R; row++){
				printf("%c", matrix[col][row]);
			}
		}

		if(T > 0)
			printf("\n");
	}

	return 0;
}
