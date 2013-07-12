#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>
#include <algorithm>
#include <map>

using namespace std;

#define MAX_ELEMENTS 100001
#define MAX_NODES 400004
#define SUPERINT unsigned long long int

struct node
{
  int low, high;
	SUPERINT value;
} NODES[MAX_NODES];

SUPERINT LAZY[MAX_NODES] = {0};

void propagate(int index, SUPERINT val)
{
	LAZY[2*index] += val;
	LAZY[2*index+1] += val;
}

void handle_lazy(int index, int low, int high)
{
	if(LAZY[index]){
		NODES[index].value += LAZY[index] * (high - low + 1);
		if(low != high) propagate(index, LAZY[index]);

		LAZY[index] = 0;
	}
}

// initialize all necessary properties
// in reality, we could even skip this if needed.
void build(int index, int low, int high)
{
	NODES[index].low = low;
	NODES[index].high = high;
	NODES[index].value = 0;

	if(low == high) return;

	int mid = (low + high)/2;
	build(2*index, low, mid);
	build(2*index+1, mid+1, high);
}

SUPERINT query(int index, int range1, int range2, int low, int high)
{
	handle_lazy(index, low, high);

	if(low >= range1 && high <= range2) return NODES[index].value;
	if(range1 > high || range2 < low)   return 0;

	int mid = (low + high)/2;
	return query(2*index, range1, range2, low,   mid)
		+ query(2*index+1, range1, range2,  mid+1, high);
}

void update(int index, int range1, int range2, int low, int high, SUPERINT v)
{
	handle_lazy(index, low, high);

	if(range1 > high || range2 < low) return;
	if(low >= range1 && high <= range2){
		NODES[index].value += v * (high - low + 1);
		if(low != high) 
			propagate(index, v);
		return;
	}

	int mid = (low + high)/2;
	update(2*index, range1, range2, low, mid, v);
	update(2*index+1, range1, range2, mid+1, high, v);

	NODES[index].value = NODES[2*index].value + NODES[2*index+1].value;
}


int T, N, C;
int operation;
int param1, param2;
SUPERINT v;

int main()
{
	scanf("%d", &T);
	while(T--){
		for(int w = 0; w < MAX_NODES; w++) 
			LAZY[w] = 0;

		scanf("%d %d", &N, &C);

		build(1, 1, N);
		while(C--){
			scanf("%d %d %d", &operation, &param1, &param2);

			if(operation){
				printf("%llu\n", query(1, param1, param2, 1, N));
				continue;
			}

			scanf("%llu", &v);
			update(1, param1, param2, 1, N, v);
		}
	}

	return 0;
}
