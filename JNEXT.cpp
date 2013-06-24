#include <stdio.h>
#include <string.h>
#include <utility>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct magic
{
  int val;
	int pos;

	bool operator < (const magic& e) const
    {
		return pos > e.pos;
    }
};



int main()
{
	int test_cases;
	scanf("%d", &test_cases);
	while(test_cases--)
	{
		int digit_count;
		scanf("%d", &digit_count);
		int *digits = new int[digit_count + 1];

		vector<vector<magic> > arr(10); // 0-9

		int all_same = true;
		for(int k = 0; k < digit_count; k++) 
		{
			scanf("%d", &digits[k]);
			
			// if all the digits are not same,
			// or left digit is smaller than right one,
			// then we know that answer can't be -1
			if(k > 0 && (digits[k - 1] != digits[k])) 
				all_same = false;

			magic m;
			m.val = digits[k];
			m.pos = k;
			
			arr[m.val].push_back(m);
		}

		// we output -1(not possible)
		// when all digits are same, or
		// we have only one digit.
		if(digit_count == 1 || all_same)
		{
			printf("-1\r\n");
			continue;
		}


		for(int v = 0; v < 10; v++)
			sort(arr[v].begin(), arr[v].end());


		// how many digits are we currently considering.
		// starting from (right)
		// we start by considering only two rightmost digits.
		int left_bound = 0; // inclusive :-)


		int left = -1;
		int right = -1;

		for(int w = digit_count - 1; w > 0; w--)
		{
			int digit_position = w;
			int digit = digits[w];

			if(digit_position < left_bound) 
				break;

			// we have digit@position w
			// we want to find smaller digit than "digit" at left
			// while minimizing length between them.

			int best = -1;
			for(int cv = digit - 1; cv >= 0; cv--)
			{
				magic e; 
				e.pos = digit_position - 1;

				vector<magic>::iterator it = lower_bound(arr[cv].begin(), arr[cv].end(), e);
				if(it != arr[cv].end())
				{
					// voila, we found digit on the left. 
					// run some checks and see if we take it, or not.
					if(best == -1) best = it->pos;
					else if(it->pos > best) best = it->pos;
				}
			}

			// we have found better candiate!
			if(best != -1 && best >= left_bound)
			{
				left = best;
				right = w;

				left_bound = left + 1;
			}

		}

		if(left == -1)
		{
			printf("-1\r\n");
			continue;
		}
		
		// swap those two digits
		int te = digits[left];
		digits[left] = digits[right];
		digits[right] = te;

		sort(digits + left + 1, digits + digit_count);
		for(int k = 0; k < digit_count; k++)
		{
			printf("%c", digits[k] + '0');
		}
		printf("\r\n");

		delete[] digits;
	}

	return 0;
}

