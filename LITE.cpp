// ACTUAL PROBLEM SOLUTION =]]
#define MIN_STALLS 2
#define MAX_STALLS 100000
#define MAX_NODES  400016

int N, M;
int operation;
int range1, range2;

struct node
{
	int start;
	int end;

	int lights_on;
	int lights_off;
} NODES[MAX_NODES];

int LAZY[MAX_NODES] = {0};

void flip_switches(int index)
{
	int t = NODES[index].lights_on;
	NODES[index].lights_on = NODES[index].lights_off;
	NODES[index].lights_off = t;
}

void propagate(int index, int i)
{
	LAZY[2*index] += i;
	LAZY[2*index+1] += i;
}

// handles lazy update for NODES[index],
// and then propagates it down to children.
void handle_lazy(int index, int start, int end)
{
	// check if we have any lazy updates in "queue"
	if(LAZY[index]){
		// note that if we have even times of flipings "queued",
		// then we end up at the same state we started from,
		// so we skip the update part. 
		if(LAZY[index] % 2) flip_switches(index);
		if(start != end)    propagate(index, LAZY[index]);

		LAZY[index] = 0;
	}
}


int query(int index, int range1, int range2, int start, int end)
{
	if(!NODES[index].lights_off && !NODES[index].lights_on){
			NODES[index].lights_off = end - start + 1;
			NODES[index].lights_on  = 0;
	}

	node &left = NODES[2*index];
	node &right = NODES[2*index+1];

	handle_lazy(index, start, end);

	if(range2 < start || range1 > end)   return 0;
	if(start >= range1 && end <= range2) return NODES[index].lights_on;

	int w = query(2*index, range1, range2, start, (start + end)/2) + 
			query(2*index+1, range1, range2, (start+end)/2+1, end);

	NODES[index].lights_off = left.lights_off + right.lights_off;
	NODES[index].lights_on = left.lights_on + right.lights_on;

	return w;
}

// given range [range1..range2], we want to update segmented tree
// lazily and flip the switches.
void update(int index, int range1, int range2, int start, int end)
{
	// if some segment has lights_off=0 and lights_on=0, then
	// it means that it's uninitialized and we do installation.
	// we assume that all lights are off.
	if(!NODES[index].lights_off && !NODES[index].lights_on){
			NODES[index].lights_off = end - start + 1;
			NODES[index].lights_on  = 0;
	}

	// sometimes we need to handle lazy-updates that came from the parent.
	// we just check if we have some pending updates, and if we do have
	// we basically DO the updates(flip the switches) and then propagate
	// that update down to our children and mark ourselves as "DONE" for now.
	handle_lazy(index, start, end);

	// we are dealing with a segment that does not fall on our radar.
	// hence we don't really care about it right now.
	// this eliminates a lot of cases, since we don't explictly test for this.
	if(range2 < start || range1 > end) return;

	// if we find segment that is completely inside our [range1..range2] update,
	// then we basically update that segment directly, eg flip all the switches,
	// and propagate the "FLIP" command down to our children.
	if(start >= range1 && end <= range2){
		flip_switches(index);
		if(start != end)
			propagate(index, 1);
		return;
	}

	// update both children now,
	update(2*index, range1, range2, start, (start+end)/2);
	update(2*index+1, range1, range2, (start+end)/2+1, end);

	node &left = NODES[2*index];
	node &right = NODES[2*index+1];

	// we recalculate the value, because in meanwhile, we might have had 
	// some "LAZY" updates performed, and thus we need to update our new state.
	NODES[index].lights_off = left.lights_off + right.lights_off;
	NODES[index].lights_on = left.lights_on + right.lights_on;
}

int main()
{
	parse_data();
	N = extract_int();
	M = extract_int();

	while(M--){
		operation = extract_int();
		range1    = extract_int();
		range2	  = extract_int();

		if(operation){
			printf("%d\n", query(1, range1, range2, 1, N));
			continue;
		}

		update(1, range1, range2, 1, N);
	}
	return 0;
}


