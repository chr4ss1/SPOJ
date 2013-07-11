
struct node
{
  int start;
	int end;

	int opening_excessive;
	int closing_excessive;
};


#define MAX_BRACETS 30000 + 20 // 0 terminator & string starts from index 1
#define MAX_LOG 120108

char bracets[MAX_BRACETS] = {0};
node NODES[MAX_LOG+100];

int T = 1;
int N, M;
int operation;


void build(int node_, int low, int high)
{
	NODES[node_].start = low;
	NODES[node_].end = high;
	NODES[node_].opening_excessive = 0;
	NODES[node_].closing_excessive = 0;

	if(high == low){
		NODES[node_].opening_excessive = bracets[low] == '(' ? 1 : 0;
		NODES[node_].closing_excessive = bracets[low] == ')' ? 1 : 0;
		return;
	}

	build(2*node_, low, (low + high)/2);
	build(2*node_+1, (low + high)/2 + 1, high);

	node &left_node = NODES[2*node_];
	node &right_node = NODES[2*node_+1];

	// if both segments are already OKAY
	// OKAY means that each bracet has been matched
	// then we basically have no excessive ones, if we merge them.
	if(!left_node.opening_excessive 
		&& !left_node.closing_excessive
		&& !right_node.opening_excessive
		&& !right_node.closing_excessive)
	{
		NODES[node_].opening_excessive = 0;
		NODES[node_].closing_excessive = 0;
		return;
	}

	NODES[node_].closing_excessive = left_node.closing_excessive;
	NODES[node_].opening_excessive = right_node.opening_excessive;

	if(left_node.opening_excessive > right_node.closing_excessive){
		NODES[node_].opening_excessive += left_node.opening_excessive - right_node.closing_excessive;
	} else if(left_node.opening_excessive < right_node.closing_excessive){
		NODES[node_].closing_excessive += right_node.closing_excessive - left_node.opening_excessive;
	} else {

	}
}

// this is pretty much same as build(), but
// with a little exception, that we skip updating of RANGES
// that we don't care about.
// theoretically should give us logN time.
void update(int node_, int low, int high, int number)
{
	if(number < low || number > high) 
		return;

	if(low == high){
		NODES[node_].opening_excessive = bracets[low] == '(' ? 1 : 0;
		NODES[node_].closing_excessive = bracets[low] == ')' ? 1 : 0;
		return;
	}


	node &left_node = NODES[2*node_];
	node &right_node = NODES[2*node_+1];

	update(2*node_, low, (low + high)/2, number);
	update(2*node_+1, (low + high)/2 + 1, high, number);

	NODES[node_].closing_excessive = left_node.closing_excessive;
	NODES[node_].opening_excessive = right_node.opening_excessive;

	if(left_node.opening_excessive > right_node.closing_excessive){
		NODES[node_].opening_excessive += left_node.opening_excessive - right_node.closing_excessive;
	} else if(left_node.opening_excessive < right_node.closing_excessive){
		NODES[node_].closing_excessive += right_node.closing_excessive - left_node.opening_excessive;
	}
}

int main()
{
	parse_data();
	while(T <= 10){
		printf("Test %d:\n", T++);
		N = extract_int();
		extract_string(bracets + 1);
		M = extract_int();

		build(1, 1, N);
		while(M--){
			operation = extract_int();
			if(!operation){
				printf("%s\n", !NODES[1].opening_excessive && !NODES[1].closing_excessive ? "YES" : "NO");
				continue;
			}

			// flip it
			// and let the update propagate through segmented tree.
			bracets[operation] = bracets[operation] == ')' ? '(' : ')';
			update(1, 1, N, operation);
		}
	}

	return 0;
}


