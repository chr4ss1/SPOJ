#include <stdio.h>
#include <utility>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct employee
{
  int id;
	int salary;
	int height;

	int parent_index;
	int sub_ordinates;

	int cur;
	bool processed;

	bool operator < (const employee& e) const
    {
		return (salary < e.salary);
    }
};

// problem states explictly that no two employees
// have same salary.
struct salary_predicate
{
    inline bool operator() (const employee& struct1, const employee& struct2)
    {
		if(struct1.height == struct2.height)
			return struct1.salary < struct2.salary;

        return (struct1.height < struct2.height);
    }
};

const int MAX_EMPLOYEES = 30000;
const int MAX_QUERIES = 200;

employee employees[MAX_EMPLOYEES];
int queries[MAX_QUERIES];



int main()
{

	int test_cases;

	scanf("%d", &test_cases);

	while(test_cases--)
	{
		int employeeCount, queryCount;
		scanf("%d %d", &employeeCount, &queryCount);


		int i = 0;
		int j = 0;
		while(i < employeeCount)
		{
			employees[i].parent_index = -1;
			employees[i].sub_ordinates = 0;

			scanf("%d %d %d", &employees[i].id, &employees[i].salary, &employees[i].height);
			i++;
		}

		map<int, int> mapper;
		while(j < queryCount)
		{
			scanf("%d", &queries[j]);
			mapper.insert(pair<int, int>(queries[j], -1));
			j++;
		}

		// now step1; sort employees structure based on height&SALARY!
		sort(employees, employees + employeeCount, salary_predicate());
		for(int b = 0; b < employeeCount; b++) 
			employees[b].cur = b;


		typedef map<employee, int> map_t;
		map_t xc;

		for(int i = 0; i < employeeCount; i++)
			xc.insert(pair<employee, int>(employees[i], 1));

		// start with smallest.
		for(int v = 0; v < employeeCount; v++)
		{
			xc.erase(employees[v]);

			map_t::iterator it = xc.lower_bound(employees[v]);
			if(it != xc.end())
			{
				employee boss = it->first;
				employees[v].parent_index = boss.cur;
				employees[boss.cur].sub_ordinates += employees[v].sub_ordinates + 1;
			}
		}


		for(int k = 0; k < employeeCount; k++)
		{
			employees[k].cur = k;
			if(mapper.find(employees[k].id) != mapper.end())
				mapper[employees[k].id] = k;
		}





		// time to print it out.
		for(int b = 0; b < queryCount; b++)
		{
			int id = queries[b];
			int index = mapper[id];

			int parent_index = employees[index].parent_index;
			int parent = parent_index < 0 ? 0 : employees[parent_index].id;



			printf("%d %d\r\n", parent, employees[index].sub_ordinates);
		}
	}

	return 0;
}

