#define MAX_ELEMENTS 50001
#define MAX_NODES 200004 // 2*2^(log(MAX_ELEMENTS)+1)

struct node
{
	int start;
	int end;

	int total_sum;
	int maximum_sum;
	int maximum_sum_left;
	int maximum_sum_right;
};

struct inter_result
{
	node temp;
	bool valid;
} res;

int A[MAX_ELEMENTS] = {0};
node NODES[MAX_NODES] = {0};

int N, M;
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
		NODES[node].maximum_sum = A[low];
		NODES[node].maximum_sum_left = A[low];
		NODES[node].maximum_sum_right = A[low];
		NODES[node].total_sum = A[low];
		return;
	}

	int mid = (low + high) >> 1;
	int left_node = node << 1;
	int right_node = left_node + 1;

	build_tree(left_node, low, mid);
	build_tree(right_node, mid + 1, high);

	NODES[node].total_sum = NODES[left_node].total_sum + NODES[right_node].total_sum;
	NODES[node].maximum_sum_left = max(NODES[left_node].maximum_sum_left, 
		NODES[left_node].total_sum + NODES[right_node].maximum_sum_left);

	NODES[node].maximum_sum_right = max(NODES[right_node].maximum_sum_right, 
		NODES[right_node].total_sum + NODES[left_node].maximum_sum_right);

	NODES[node].maximum_sum = max(NODES[left_node].maximum_sum, NODES[right_node].maximum_sum);
	NODES[node].maximum_sum = max(NODES[node].maximum_sum, NODES[node].total_sum);
	NODES[node].maximum_sum = max(NODES[node].maximum_sum, NODES[node].maximum_sum_left);
	NODES[node].maximum_sum = max(NODES[node].maximum_sum, NODES[node].maximum_sum_right);
	NODES[node].maximum_sum = max(NODES[node].maximum_sum, NODES[left_node].maximum_sum_right + NODES[right_node].maximum_sum_left);
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
	merged_node.total_sum = r1.temp.total_sum + r2.temp.total_sum;
	merged_node.maximum_sum = max(r1.temp.maximum_sum, r2.temp.maximum_sum);
	merged_node.maximum_sum_left = max(r1.temp.maximum_sum_left, r1.temp.total_sum + r2.temp.maximum_sum_left);
	merged_node.maximum_sum_right = max(r2.temp.maximum_sum_right, r2.temp.total_sum + r1.temp.maximum_sum_right);

	merged_node.maximum_sum = max(merged_node.maximum_sum, merged_node.maximum_sum_left);
	merged_node.maximum_sum = max(merged_node.maximum_sum, merged_node.maximum_sum_right);
	merged_node.maximum_sum = max(merged_node.maximum_sum, merged_node.total_sum);
	merged_node.maximum_sum = max(merged_node.maximum_sum, r1.temp.maximum_sum_right + r2.temp.maximum_sum_left);

	result.temp = merged_node;
	result.valid = true;
	return result;
}

int main()
{
	parse_data();
	N = extract_int();
	for(int j = 1; j <= N; j++) 
		A[j] = extract_int();

	M = extract_int();
	build_tree(1, 1, N);
	while(M--){
		r1 = extract_int();
		r2 = extract_int();
		res = query(1, r1, r2, 1, N);

		printf("%d\n", res.temp.maximum_sum);
	}

	return 0;
}
