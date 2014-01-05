#include <iostream>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

struct human
{
	int id;

	queue<int> preffered;
	vector<int> positions;

	bool is_engaded;
	int  partner_id;
};
struct stable_match
{
	int men_id;
	int women_id;
};

bool is_first_preffered(
	human first_man, 
	human second_man, 
	human woman)
{
	return woman.positions[first_man.id] < woman.positions[second_man.id];
}

vector<human> read(int count, int is_women)
{
	human sentinel;

	vector<human> humans;
	humans.push_back(sentinel);

	for (int i = 0; i < count; i++)
	{
		int index;
		cin >> index;

		human temp;
		temp.is_engaded = false;
		temp.id = index;

		if (is_women)
			temp.positions.resize(count + 1);

		for (int j = 0; j < count; j++)
		{
			int temp_pref;
			cin >> temp_pref;

			temp.preffered.push(temp_pref);

			if (is_women)
				temp.positions[temp_pref] = j;
		}

		humans.push_back(temp);
	}

	return humans;
}

vector<stable_match> solve(
	vector<human> men, 
	vector<human> women,
	int marriages)
{
	vector<stable_match> result;
	stack<int> free_men;

	// all men are free by default.
	for (int i = 1; i <= marriages; i++)
		free_men.push(i);

	while (!free_men.empty()){

		int current_man = free_men.top();
		free_men.pop();

		human &man = men[current_man];

		// proposte to first women that we can find.
		while (!man.preffered.empty())
		{
			int proposal = man.preffered.front();
			man.preffered.pop();

			human &woman = women[proposal];

			// if woman is not engaged
			// we will attempt to engage her.
			if (!woman.is_engaded){
				woman.is_engaded = true;
				man.is_engaded = true;

				man.partner_id = woman.id;
				woman.partner_id = man.id;
			}
			else{
				// this is going to be a little more trickier
				// what do we do when women is already engaged with someone?
				// we have to figure out if our "man" will make better offer
				// if he does, we can let the other man become "free" again.
				human &engaged_man = men[woman.partner_id];
				if (!is_first_preffered(man, engaged_man, woman))
					continue;

				engaged_man.is_engaded = false;
				free_men.push(engaged_man.id);

				man.is_engaded = true;
				man.partner_id = woman.id;
				woman.partner_id = man.id;
			}

			break;
		}
	}

	for (int i = 1; i < men.size(); i++){
		human &man = men[i];

		stable_match match;
		match.men_id = man.id;
		match.women_id = man.partner_id;

		result.push_back(match);
	}


	return result;
}

int main()
{
	int test_cases;
	cin >> test_cases;

	while (test_cases--){
		int marriages;
		cin >> marriages;

		vector<human> women = read(marriages, true);
		vector<human> men   = read(marriages, false);
		
		vector<stable_match> results = solve(men, women, marriages);
		for (int j = 0; j < results.size(); j++)
			cout << results[j].men_id << " " << results[j].women_id << endl;
	}
	return 0;
}
