#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define MAX_CITIES 10000

struct node
{
	int city_index;
	int cur_cost;
	bool operator < (const node& e) const{return (cur_cost > e.cur_cost);}
};

struct city
{
	int best_cost;
	bool explored;
	vector<pair<int, int> > neighbours;
};

int				city_count;
city			CITIES[MAX_CITIES + 1];
char			temp_city_second[11];
char			temp_city[11];

// Returns best path from start->end
// using dijkstra algorithm. http://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
int dijkstra(int start, int end)
{
	if(start == end) return 0;
	for(int e = 0; e <= city_count; e++){ 
		CITIES[e].explored	= false;
		CITIES[e].best_cost = 0;
	}

	priority_queue<node> pque;
	node beg; 
	beg.city_index	= start;
	beg.cur_cost	= 0;
	pque.push(beg);

	while(!pque.empty()){
		node cur_node = pque.top();
		pque.pop();

		city &cur_city = CITIES[cur_node.city_index];
		if(cur_city.explored)						continue;
		if(cur_city.best_cost != cur_node.cur_cost) continue;
		if(cur_node.city_index == end)				return cur_city.best_cost;

		for(int n = 0; n < cur_city.neighbours.size(); n++){
			int neighbour_index		= cur_city.neighbours[n].first;
			int cost_to_travel		= cur_city.neighbours[n].second;

			city &neighbour_city	= CITIES[neighbour_index];
			if(neighbour_city.explored) continue;
			if(neighbour_city.best_cost == 0 || cur_city.best_cost + cost_to_travel < neighbour_city.best_cost){
				neighbour_city.best_cost = cur_city.best_cost + cost_to_travel;

				beg.city_index	= neighbour_index;
				beg.cur_cost	=  neighbour_city.best_cost;
				pque.push(beg);
			}
		}
		cur_city.explored = true;
	}

	// no path found, indicate it with -1.
	return -1;
}

int main() {
	parse_data();

	int test_cases = extract_int();
	while(test_cases--){
		memset(HASH_MAP, 0, sizeof(hash_map) * MAX_HASH);
		city_count = extract_int();

		for(int i = 1; i <= city_count; i++){
			extract_string(temp_city);
			hash_string_setval((unsigned char *)temp_city, i);

			int neighbours_count = extract_int();
			CITIES[i].neighbours.resize(neighbours_count);

			for(int j = 0; j < neighbours_count; j++){
				int city_index	= extract_int();
				int cost		= extract_int();

				CITIES[i].neighbours[j].first	= city_index;
				CITIES[i].neighbours[j].second	= cost; 
			}
		}

		for(int q = extract_int(); q; q--){
			extract_string(temp_city);
			extract_string(temp_city_second);
			printf("%d\n", dijkstra(
				HASH_MAP[hash_string_getval((unsigned char*)temp_city)].index, 
				HASH_MAP[hash_string_getval((unsigned char*)temp_city_second)].index));
		}
	}
	return 0;
}
