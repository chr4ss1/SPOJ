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
  int eggs_needed;
	int flour_needed;
	int sugar_needed;
	int milk_needed;
};


// specifies ingredients needed for ONE cake.
int eggs_per_cake, flour_per_cake, sugar_per_cake, milk_per_cake;

// returns the number of cakes we can make using our ingredients
// and shows minimum amount of things we need to buy in order to make it.
magic Solve(int eggs_left, int flour_left, int sugar_left, int milk_left)
{
	// base case,
	// when we have all the ingredients EXACTLY
	// then we can create 1 cake without buying anything.
	if(eggs_left == eggs_per_cake && 
		flour_left == flour_per_cake &&
		sugar_left == sugar_per_cake &&
		milk_left == milk_per_cake)
	{
		magic e;
		e.eggs_needed = 0;
		e.flour_needed = 0;
		e.milk_needed = 0;
		e.sugar_needed = 0;
		return e;
	}


	//subtract as many cakes as possible from here.
	int cakes_made = 0;
	while(true)
	{
		if(eggs_left >= eggs_per_cake  &&
			flour_left >= flour_per_cake  &&
			sugar_left >= sugar_per_cake  &&
			milk_left >= milk_per_cake )
		{
			eggs_left -= eggs_per_cake;
			flour_left -= flour_per_cake;
			sugar_left -= sugar_per_cake;
			milk_left -= milk_per_cake;
			cakes_made++;
		} else break;
	}

	// we now have some ingredients left, but not enough to make real cake.
	// let,s see what we have to buy.
	magic e; 
	e.eggs_needed = 0;
	e.flour_needed = 0;
	e.milk_needed = 0;
	e.sugar_needed = 0;

	// we have used up all reserves, so the answer is ready :)
	if(eggs_left==0 && flour_left==0 && sugar_left==0 && milk_left == 0)
		return e;


	// fill the missing reserves, if we have any!
	if(eggs_left < eggs_per_cake)
	{
		e.eggs_needed = eggs_per_cake - eggs_left;
		eggs_left = eggs_per_cake;
	}
	if(flour_left < flour_per_cake)
	{
		e.flour_needed = flour_per_cake - flour_left;
		flour_left = flour_per_cake;
	}
	if(sugar_left < sugar_per_cake)
	{
		e.sugar_needed = sugar_per_cake - sugar_left;
		sugar_left = sugar_per_cake;
	}
	if(milk_left < milk_per_cake)
	{
		e.milk_needed = milk_per_cake - milk_left;
		milk_left = milk_per_cake;
	}

	magic k = Solve(eggs_left, flour_left, sugar_left, milk_left);

	// merge results.
	e.eggs_needed += k.eggs_needed;
	e.flour_needed += k.flour_needed;
	e.milk_needed += k.milk_needed;
	e.sugar_needed += k.sugar_needed;
	return e;
}


int main()
{
	while(true)
	{
		int eggs, flour, sugar, milk;

		scanf("%d %d %d %d %d %d %d %d", &eggs, 
			&flour, &sugar, &milk, 
			&eggs_per_cake, &flour_per_cake, &sugar_per_cake, 
			&milk_per_cake);

		if(eggs == -1)
			return 0;

		magic x = Solve(eggs, flour, sugar, milk);
		printf("%d %d %d %d\r\n", x.eggs_needed, x.flour_needed, x.sugar_needed, x.milk_needed);
	}
	return 0;
}

