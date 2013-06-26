#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <stdio.h>

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
	//pFile = fopen ( "C:\\Intel\\test_case.txt" , "rb" );

	int c, j;
	char *ptr = arr;

	// read data into buffer!
	while((c = fread(ptr, 1, MAX_CHUNK_SIZE, stdin))>0)
		ptr += MAX_CHUNK_SIZE;

	// reset ptr to beginning.
	ptr = arr;
}

// A simple inline function that can extract integer from buffer.
 int extract_int()
{
	// skip all stupid whitespaces.
	while(*ptr == 13 || *ptr == 10 || *ptr == ' ') ptr++;

	int wtf = strtol(ptr, 0, 0);

	// skip the integer
	while(*ptr >= '0' && *ptr <= '9') ptr++;
	return wtf;
}

// problem specific

#define MAX_EMPLOYEES 1000
#define MAX_EDGES 10000

int T; // testcases
int N; // number of employees
int R; // number of relations

int R1, R2; // R1 < R2
int cur_rank;
int scenario;


struct employee
{
	int id;
	int	incoming_edges;
	int edges[MAX_EDGES];
	int edge_count;
	bool processed;
};

employee employees[MAX_EMPLOYEES];

int main()
{
	parse_data();
	T = extract_int();
	scenario = 1;

	while(T--){
		N = extract_int();
		R = extract_int();
		for(int j = 0; j < N; j++){
			employees[j].id = j;
			employees[j].edge_count = 0;
			employees[j].incoming_edges = 0;
			employees[j].processed = false;
		}

		for(int r = 0; r < R; r++){
			R1 = extract_int();
			R2 = extract_int();
			employees[R2].edges[employees[R2].edge_count] = R1;
			employees[R2].edge_count++;
			employees[R1].incoming_edges += 1;
		}

		// scan all employees that have zero incoming edges.
		// they must be "roots" aka rank 0 candidates.
		cur_rank = 1;
		vector<int> rank_candidates;
		vector<int> next_level;
		for(int j = 0; j < N; j++){
			if(!employees[j].incoming_edges)
				rank_candidates.push_back(j);
		}

		// start the actual algorithm that takes care of ranking.
		// the idea is simple.
		// we start with nodes that have no incoming edges to them,
		// we call them "root" nodes. by definition, they have to be "root" ones.

		printf("Scenario #%d:\n", scenario++);
		while(rank_candidates.size() > 0){
			sort(rank_candidates.begin(), rank_candidates.end());
			next_level.clear();

			for(int w = 0; w < rank_candidates.size(); w++){
				printf("%d %d\n", cur_rank, rank_candidates[w]);
				employees[rank_candidates[w]].processed = true;
				for(int child = 0; child < employees[rank_candidates[w]].edge_count; child++){
					if(!employees[employees[rank_candidates[w]].edges[child]].processed){
						employees[employees[rank_candidates[w]].edges[child]].incoming_edges -= 1;
						if(!employees[employees[rank_candidates[w]].edges[child]].incoming_edges){
							next_level.push_back(employees[rank_candidates[w]].edges[child]);
						}
					}
				}
			}

			cur_rank++;
			rank_candidates = next_level;
		}
	}

	return 0;
}
