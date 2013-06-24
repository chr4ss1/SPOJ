#include <stdio.h>
#include <utility>
#include <queue>
#include <vector>
#include <map>

using namespace std;

int exectes()
{
  int test_cases;
	int n, who_starts;

	scanf("%d", &test_cases);

	while(test_cases--)
	{
		scanf("%d %d", &n, &who_starts);
		
		printf("%s wins.\r\n", !who_starts ? "Airborne" : "Pagfloyd");
	}

	return 0;
}

