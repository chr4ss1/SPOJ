
// RELATED TO PROB
#define MAX_ELEMENTS 10000000
#define MAX_NODES 33554432
#define MAX_POSTERS 40000

int T, N;

bool NODES[MAX_NODES];

int POSTERS[MAX_POSTERS][2] = {0};
bool LAZY[MAX_NODES] = {0};

inline void propagate(int index, bool val)
{
  LAZY[2*index] = val;
	LAZY[2*index+1] = val;
}


inline void handle_lazy(int index, int low, int high)
{
	if(LAZY[index]){
		NODES[index] = true;

		if(low != high)
			propagate(index, true);
		LAZY[index] = 0;
	}
}

inline void combine(int index)
{
	NODES[index] = NODES[2*index] && NODES[2*index+1];
}


int query(int index, int range1, int range2, int low, int high)
{
	handle_lazy(index, low, high);

	if(range1 > high || range2 < low)   return -1;
	if(low >= range1 && high <= range2) return NODES[index];

	int mid = (low + high) >> 1;
	int f1 = index << 1;
	int f2 = f1 + 1;

	int w = query(f1, range1, range2, low,   mid);
	int w1 = query(f2, range1, range2,  mid+1, high);
	if(w == -1) return w1;
	if(w1 == -1) return w;

	return w && w1;
}

void update(int index, int range1, int range2, int low, int high)
{
	handle_lazy(index, low, high);

	if(range1 > high || range2 < low) return;
	if(low >= range1 && high <= range2){
		NODES[index] = true;

		if(low != high) 
			propagate(index, true);
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
	T = extract_int();
	while(T--){
		N = extract_int();

		int i = N;

		int rBoundary = 0;
		int lBoundary = -1;
		while(i--){
			POSTERS[i][0] = extract_int();
			POSTERS[i][1] = extract_int();
			if(lBoundary == -1) 
				lBoundary = POSTERS[i][0];

			lBoundary = min(lBoundary, POSTERS[i][0]);
			rBoundary = max(rBoundary, POSTERS[i][1]);
		}

		int t =  (1 << (rBoundary - lBoundary + 1));
		for(int w = 0; w < MAX_NODES; w++){
			LAZY[w] = 0;
			NODES[w] = 0;
		}

		int visible_posters = 0;
		for(i = 0; i < N; i++){
			if(!query(1, POSTERS[i][0], POSTERS[i][1], lBoundary, rBoundary)){
				update(1, POSTERS[i][0], POSTERS[i][1], lBoundary, rBoundary);
				visible_posters++;
			}
		}
		printf("%d\n", visible_posters);
	}

	return 0;
}
