
struct block
{
  int area;
	int height;

	int bx, by;
	
	bool operator < (const block &bl) const
	{
		return (area > bl.area);
	}
} BLOCKS[3 * 30];

int block_count;
map<int, int> cache;

// what is the tallest tower we can make, so
// that it ends with block_id?!
int solve(int block_id)
{
	map<int, int>::iterator it = cache.find(block_id);
	if(it != cache.end()) return it->second;

	int best = 0;
	bool init = false;

	for(int k = block_id - 1; k >= 0; k--){
		if((BLOCKS[k].bx > BLOCKS[block_id].bx
			&& BLOCKS[k].by > BLOCKS[block_id].by))
		{
			int ts = solve(k);
			if(!init){
				best = ts;
				init = true;
			}

			best = max(best, ts);
		}
	}

	return cache[block_id] = BLOCKS[block_id].height + best;
}

int main() {
	while(scanf("%d", &block_count) == 1 && block_count)
	{
		for(int j = 0, k = 0; j < block_count; j++, k += 3){
			int width, height, depth;
			scanf("%d %d %d", &height, &width, &depth);

			// generate 3 rotations of block.
			BLOCKS[k].area = width * height;
			BLOCKS[k].height = depth;
			BLOCKS[k].bx = max(width, height);
			BLOCKS[k].by = min(width, height);

			BLOCKS[k+1].area = width * depth;
			BLOCKS[k+1].height = height;
			BLOCKS[k+1].bx = max(width, depth);
			BLOCKS[k+1].by = min(width, depth);

			BLOCKS[k+2].area = height * depth;
			BLOCKS[k+2].height = width;
			BLOCKS[k+2].bx = max(depth, height);
			BLOCKS[k+2].by = min(depth, height);
		}

		block_count *= 3;
		sort(BLOCKS, BLOCKS + block_count);

		int		best;
		bool	init = false;
		
		cache.clear();
		for(int j = 0; j < block_count; j++){
			int ts = solve(j);
			if(!init){
				best = ts;
				init = true;
			}

			best = max(best, ts);
		}

		printf("%d\n", best);
	}
	return 0;
}
