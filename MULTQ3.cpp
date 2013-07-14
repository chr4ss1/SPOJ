
// RELATED TO PROB
#define MAX_ELEMENTS 100001
#define MAX_NODES 400004
#define SUPERINT unsigned long long int

int N, Q;
int OP, PARAM1, PARAM2;

struct node
{
  int low, high;

	int div3_modulo0;
	int div3_modulo1;
	int div3_modulo2;

	int cur_modulo;
} NODES[MAX_NODES];

int A[MAX_ELEMENTS] = {0};
int LAZY[MAX_NODES] = {0};

inline void propagate(int index, int val)
{
	LAZY[2*index] += val;
	LAZY[2*index+1] += val;
}

inline void super_shift(int index)
{
	int t1 = NODES[index].div3_modulo0;
	int t2 = NODES[index].div3_modulo1;

	NODES[index].div3_modulo0 = NODES[index].div3_modulo2;
	NODES[index].div3_modulo1 = t1;
	NODES[index].div3_modulo2 = t2;
}

inline void handle_lazy(int index, int low, int high)
{
	if(LAZY[index]){
			int mod = LAZY[index] % 3;
			if(mod){
				super_shift(index);
				if(mod == 2)	super_shift(index);
				if(low != high) propagate(index, LAZY[index]);
			}
		LAZY[index] = 0;
	}
}

inline void combine(int index)
{
	NODES[index].div3_modulo0 = NODES[2*index].div3_modulo0 + NODES[2*index+1].div3_modulo0;
	NODES[index].div3_modulo1 = NODES[2*index].div3_modulo1 + NODES[2*index+1].div3_modulo1;
	NODES[index].div3_modulo2 = NODES[2*index].div3_modulo2 + NODES[2*index+1].div3_modulo2;
}

// initialize all necessary properties
// in reality, we could even skip this if needed.
void build(int index, int low, int high)
{
	NODES[index].low = low;
	NODES[index].high = high;

	if(low == high){
		NODES[index].div3_modulo0 = 0;
		NODES[index].div3_modulo1 = 0;
		NODES[index].div3_modulo2 = 0;
		NODES[index].cur_modulo = A[index] % 3;
		switch(NODES[index].cur_modulo){
			case 0: NODES[index].div3_modulo0++; break;
			case 1: NODES[index].div3_modulo1++; break;
			case 2: NODES[index].div3_modulo2++; break;
		}
		return;
	}

	int mid = (low + high)>>1;
	int f1 = index << 1;
	int f2 = f1 + 1;

	build(f1, low, mid);
	build(f2, mid+1, high);
	combine(index);
}

int query(int index, int range1, int range2, int low, int high)
{
	handle_lazy(index, low, high);

	if(range1 > high || range2 < low)   return 0;
	if(low >= range1 && high <= range2) return NODES[index].div3_modulo0;

	int mid = (low + high) >> 1;
	int f1 = index << 1;
	int f2 = f1 + 1;

	return query(f1, range1, range2, low,   mid)
		+ query(f2, range1, range2,  mid+1, high);
}

void update(int index, int range1, int range2, int low, int high)
{
	handle_lazy(index, low, high);

	if(range1 > high || range2 < low) return;
	if(low >= range1 && high <= range2){
		super_shift(index);

		// increment all by 1.
		if(low != high) 
			propagate(index, 1);
		return;
	}

	int mid = (low + high) >> 1;
	int f1 = index << 1;
	int f2 = f1 + 1;

	update(f1, range1, range2, low, mid);
	update(f2, range1, range2, mid+1, high);
	combine(index);
}


int main()
{
	parse_data();
	N = extract_int();
	Q = extract_int();

	build(1, 1, N);
	while(Q--){
		OP = extract_int();
		PARAM1 = extract_int() + 1;
		PARAM2 = extract_int() + 1;
		switch(OP){
		case 0:
			update(1, PARAM1, PARAM2, 1, N);
			break;
		case 1:
			printf("%d\n", query(1, PARAM1, PARAM2, 1, N));
			break;
		}
	}

	return 0;
}
