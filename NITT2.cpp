#include <stdio.h>
#include <string.h>
#include <utility>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;



int nitt2()
{
  int test_cases;
	scanf("%d", &test_cases);
	while(test_cases--)
	{
		char digits[50001] = {0};
		scanf("%s", digits);

		// look for length
		int len = strlen(digits);
		int sum_of_digits = 0;
		for(int k = 0; k < len; k++) 
		{
			digits[k] -= '0';
			sum_of_digits += digits[k];
		}

		if(len <= 2 || (len == 3 && (digits[0]*100 + digits[1]*10 + digits[2] < 252)))
		{
			printf("No No\r\n");
			continue;
		}

		// 2^2 *  3^2 * 7  == 252
		// 3 * 5^2 * 7 == 525

		// we need to test if number is divideable by them all!

		// let's start with 2^2,
		// well basically number is divideable by 4, if last two digits are!
		int last_two_digits = digits[len - 2]*10 + digits[len-1];

		// is number divideable by 7?
		int nr[] = {1, 3, 2, 6, 4, 5};
		int count = 6;

		int exc = 0;
		int ben = 0;
		for(int j = len - 1; j >= 0; j--)
		{
			exc += digits[j] * nr[ben % count];
			ben++;
		}

		int is_divisable_by_seven = exc % 7 == 0;

		int r_252 = false;
		int r_525 = false;
	
		// check out if it's dividable by 252
		if(last_two_digits % 4 == 0 && sum_of_digits % 9 == 0 && is_divisable_by_seven) r_252 = true;
		if(sum_of_digits % 3 == 0 && is_divisable_by_seven && last_two_digits % 25 == 0) r_525 = true;

		printf("%s %s\r\n", r_252 ? "Yes" : "No", r_525 ? "Yes" : "No");
	}

	return 0;
}

