#define MAX_ELEMENTS 100001
#define MAX_NODES 400004 // 2*2^(log(MAX_ELEMENTS)+1)

struct node
{
	int start;
	int end;

	int freq;
};

struct inter_result
{
	node temp;
	bool valid;
} res;

int A[MAX_ELEMENTS] = {0};
int FREQ[MAX_ELEMENTS] = {0};
node NODES[MAX_NODES] = {0};

int N, Q;
int r1, r2;

// builds segmented tree
void build_tree(int node, int low, int high)
{
	NODES[node].start = low;
	NODES[node].end = high;

	if(low > high){
		return;
	}
	
	if(low == high){
		NODES[node].freq = FREQ[low];
		return;
	}

	int mid = (low + high) >> 1;
	int left_node = node << 1;
	int right_node = left_node + 1;

	// split step.
	build_tree(left_node, low, mid);
	build_tree(right_node, mid + 1, high);

	// merge step.
	NODES[node].freq = max(NODES[left_node].freq, NODES[right_node].freq);
}

// given segment A[start...end] inclusive.
// what is the biggest "subsegment"(biggest=sum)
inter_result query(int node_, int start, int end, int low, int high)
{
	inter_result result;
	if(start > high || end < low){
		result.valid = false;
		return result;
	}

	if(low == high || (low >= start && high <= end)){ 
		result.temp = NODES[node_];
		result.valid = true;
		return result;
	}

	int mid = (low + high) >> 1;
	inter_result r1 = query(node_ << 1, start, end, low, mid);
	inter_result r2 = query((node_ << 1) + 1, start, end, mid + 1, high);

	if(!r1.valid && !r2.valid) 
		return r1;

	if(!r1.valid) return r2;
	if(!r2.valid) return r1;

	// tricky business merging those babies :-)
	node merged_node;
	merged_node.start = low;
	merged_node.end = high;
	merged_node.freq = max(r1.temp.freq, r2.temp.freq);

	result.temp = merged_node;
	result.valid = true;
	return result;
}

int main()
{
	parse_data();
	while(true){
		N = extract_int();
		if(!N) break;

		Q = extract_int();
		for(int j = 1; j <= N; j++) 
			A[j] = extract_int();

		// preprocess A to frequency array B.
		// should be linear hehe.
		for(int j = 1; j <= N; j++){
			if(j > 1 && A[j - 1] == A[j]){
				FREQ[j] = FREQ[j - 1];
				continue;
			}

			FREQ[j] = 1;
			for(int i = j + 1; j <= N && A[i] == A[j]; i++, FREQ[j]++);
		}

		// generate segmented tree from FREQ array.
		build_tree(1, 1, N);

		while(Q--){
			r1 = extract_int();
			r2 = extract_int();

			// we need to adjust r1 and r2,
			// to complete query, instead of subqueries.
			int n1 = 1;
			int n2 = 1;
			int best = 1;

			for(int w = r1 + 1; w <= r2 && A[r1] == A[w]; w++) n1++;
			for(int z = r2 - 1; z >= r1 && A[r2] == A[z]; z--) n2++;

			best = max(n1, n2);

			r1 += n1;
			r2 -= n2;
			if(r1 <= r2){
				res = query(1, r1, r2, 1, N);
				best = max(best, res.temp.freq);
			}

			printf("%d\n", best);
		}
	}

	return 0;
}
