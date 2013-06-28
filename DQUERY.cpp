
struct query
{
  int range1;
	int range2;
	int position;
	int answer;

	bool operator < (const query& e) const
    {
		return (range1 < e.range1);
    }

	bool operator > (const query& e) const
    {
		return (position < e.position);
    }
};


#define MAX_SEQUENCE_ELEMENTS 30000 + 1 // dummy element, it's easier this way. just ignore the A[0], it doesn't mean anything :-)
#define MAX_QUERIES 200000

int A[MAX_SEQUENCE_ELEMENTS] = {0};
int DISTINCT[MAX_SEQUENCE_ELEMENTS] = {0};
query QUERIES[MAX_QUERIES];

int N, Q;
int range1, range2;
int temp;

map<int, int> umap;


int main()
{
	parse_data();
	N = extract_int();
	for(int w = 1; w <= N; w++){
		temp = extract_int();

		if(umap.find(temp) == umap.end()) 
			umap[temp] = 0;

		umap[temp]++;

		// let A[w] store elements from the input
		// and DISTINCT store count of dinstinct elements from 1..W
		A[w] = temp;
		DISTINCT[w] = umap.size();
	}

	Q = extract_int();
	for(int q = 0; q < Q; q++){
		QUERIES[q].range1 = extract_int();
		QUERIES[q].range2 = extract_int();
		QUERIES[q].position = q;
	}

	sort(QUERIES, QUERIES + Q);

	int cur_start = 1;
	int global_diff = 0;
	// start processing each query, one by one.
	for(int q = 0; q < Q; q++){
		// QUERIES[q]
		// if the queri does not start from 1,
		// then we need to update DISTINCT table, to reflect that information.
		// eg remove first elements fom the DISTINCT table that do not reflect correct info.
		for(int er = cur_start; er < QUERIES[q].range1; er++){
			umap[A[er]]--;
			if(!umap[A[er]]){
				global_diff++;
			} else{
				for(int az = er + 1; az <= N; az++){
					if(A[az] == A[er]) break;
					DISTINCT[az]--;
				}
			}
		}

		QUERIES[q].answer = DISTINCT[QUERIES[q].range2] - global_diff;
		cur_start = QUERIES[q].range1;
	}

	sort(QUERIES, QUERIES + Q, greater<query>());
	for(int q = 0; q < Q; q++){
		printf("%d\n", QUERIES[q].answer);
	}

	return 0;
}


