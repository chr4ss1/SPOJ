
// RELATED TO PROB
#define MAX_ELEMENTS 22000 + 1
#define MAX_NODES 88004

int T, N, K;

int NODES[MAX_NODES];
bool LAZY[MAX_NODES] = {0};

int A[MAX_ELEMENTS];

int get_next(int *arr, int pos);
int get_prev(int *arr, int pos);

inline void combine(int index)
{
  NODES[index] = NODES[2*index] & NODES[2*index+1];
}

void build(int index, int low, int high)
{
	if(low == high){
		NODES[index] = A[low];
		return;
	}

	int mid = (low + high) >> 1;
	int f1 = index << 1;
	int f2 = f1 + 1;

	build(f1, low, mid);
	build(f2, mid+1, high);
	combine(index);
}

int query(int index, int r1, int r2, int low, int high)
{
	if(r1 > high || r2 < low) return -1;
	if(low >= r1 && high <= r2) return NODES[index];

	
	int mid = (low + high) >> 1;
	int f1 = index << 1;
	int f2 = f1 + 1;

	int q1 = query(f1, r1, r2, low, mid);
	if(!q1) return 0;

	int q2 = query(f2, r1, r2, mid+1, high);
	if(!q2) return 0;

	if(q1 == -1) return q2;
	if(q2 == -1) return q1;
	return q1 & q2;
}

int main()
{
	parse_data();
	T = extract_int();
	while(T--){
		N = extract_int();
		K = extract_int();

		for(int i = 1; i <= N; i++)
			A[i] = extract_int();

		for(int m = 1; m < MAX_NODES; m++) 
			NODES[m] = 0;

		if(K >= N) 
			K = N - 1;
		
		build(1, 1, N);
		for(int i = 1; i <= N; i++){
			if(i > 1) printf(" ");

			// break number into three segments possibly.
			int ls1 = i - K;
			int rs1 = i + K;

			// easy case, only two segments.
			if(ls1 >= 1 && rs1 <= N){
				printf("%d", query(1, ls1, rs1, 1, N));
				continue;
			}

			if(ls1 < 1 && rs1 > N){
				printf("%d", query(1, 1, N, 1, N));
				continue;
			}

			if(ls1 < 1){
				int we = query(1, 1, rs1, 1, N);
				int wx = query(1, N - (ls1*-1), N, 1, N);
				printf("%d", we & wx);
				continue;
			}

			int we = query(1, ls1, N, 1, N);
			int wx = query(1, 1, rs1 - N, 1, N);
			printf("%d", we & wx);
		}

		printf("\n");
	}

	return 0;
}
