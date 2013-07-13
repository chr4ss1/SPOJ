#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

#define SUPERINT unsigned long long int
#define MAX_ELEMENTS 100001   // 10^5
#define MAX_NODES	800008

int N, Q;
char OP;
SUPERINT PARAM1, PARAM2;
SUPERINT NUMBERS[MAX_ELEMENTS];

struct node
{
	int start;
	int end;

	SUPERINT maximum_element;
	SUPERINT next_maximum_element;

} NODES[MAX_NODES];

struct intermediate_result
{
	node temp_node;
	bool valid;
};


node combine(const node &left, const node &right)
{
	node result;
	if(left.maximum_element == right.maximum_element){
		result.maximum_element = left.maximum_element;
		result.next_maximum_element = left.maximum_element;
		return result;
	}

	if(left.maximum_element > right.maximum_element){
		result.maximum_element = left.maximum_element;
		result.next_maximum_element = max(left.next_maximum_element, right.maximum_element);
	} else{
		result.maximum_element = right.maximum_element;
		result.next_maximum_element = max(right.next_maximum_element, left.maximum_element);
	}

	return result;
}

void build(int index, int low, int high)
{
	NODES[index].start = low;
	NODES[index].end = high;

	if(low == high){
		NODES[index].maximum_element = NUMBERS[low];
		NODES[index].next_maximum_element = 0;
		return;
	}

	int mid = (low + high) / 2;
	build(2*index, low, mid);
	build(2*index+1, mid + 1, high);

	NODES[index] = combine(NODES[2*index], NODES[2*index + 1]);
}

void update(int index, int low, int high, int element)
{
	if(low > element || high < element) return;
	if(low == high){
		NODES[index].maximum_element = NUMBERS[low];
		NODES[index].next_maximum_element = 0;
		return;
	}

	int mid = (low + high) / 2;
	update(2*index, low, mid, element);
	update(2*index+1, mid + 1, high, element);

	NODES[index] = combine(NODES[2*index], NODES[2*index + 1]);
}

intermediate_result query(int index, int range1, int range2, int low, int high)
{
	intermediate_result result;

	if(range1 > high || range2 < low){
		result.valid = false;
		return result;
	}

	if(low >= range1 && high <= range2){
		result.valid = true;
		result.temp_node = NODES[index];
		return result;
	}

	int mid = (low + high) / 2;
	intermediate_result f1 = query(2*index, range1, range2, low, mid);
	intermediate_result f2 = query(2*index+1, range1, range2, mid + 1, high);

	if(!f1.valid && !f2.valid){
		result.valid = false;
		return result;
	}

	result.valid = true;
	if(!f1.valid || !f2.valid){
		result.temp_node = f1.valid ? f1.temp_node : f2.temp_node;
		return result;
	}

	result.temp_node = combine(f1.temp_node, f2.temp_node);
	return result;
}

int main()
{
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) 
		scanf("%llu", &NUMBERS[i]);

	build(1, 1, N);

	scanf("%d\n", &Q);
	while(Q--){
		scanf("%c %llu %llu\n", &OP, &PARAM1, &PARAM2);
		switch(OP){
		case 'U':
			NUMBERS[PARAM1] = PARAM2;
			update(1, 1, N, PARAM1);
			break;
		case 'Q':
			intermediate_result result = query(1, (int)PARAM1, (int)PARAM2, 1, N);
			printf("%llu\n", result.temp_node.maximum_element + result.temp_node.next_maximum_element);
			break;
		}
	}
	return 0;
}
