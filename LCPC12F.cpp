#define SUPERINT long long

SUPERINT cards[100000];
SUPERINT X;
SUPERINT N;

SUPERINT solve()
{
  SUPERINT pairs = 0;

	map<SUPERINT, int> cek;
	for(int j = 0; j < N; j++){
		SUPERINT left = X - cards[j];

		map<SUPERINT, int>::iterator it = cek.find(left);
		if(it != cek.end())
			pairs += it->second;

		cek[cards[j]] += 1;
	}

	return pairs;
}

int main() {
	int t;
	scanf("%d", &t);

	for(int c = 1; t; t--, c++){
		scanf("%lld %lld", &X, &N);
		for(int j = 0; j < N; j++)
			scanf("%lld", &cards[j]);

		printf("%d. %lld\n", c, solve());
	}
	return 0;
}
