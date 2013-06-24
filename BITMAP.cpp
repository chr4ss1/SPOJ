#include <stdio.h>
#include <utility>
#include <queue>

using namespace std;

int width;
int height;

int bitmap[183][183] = {0};
char visited[183][183] = {0};

int main()
{
  int test_cases;
	scanf("%d", &test_cases);

	while(test_cases--)
	{
		scanf("%d %d", &height, &width);

		queue<pair<int, int> > que;
		for(int h = 0; h < height; h++)
		{
			char f;
			scanf("%c", &f);//RN
			for(int w = 0; w < width; w++)
			{
				scanf("%c", &bitmap[h][w]);
				bitmap[h][w] -= '0';
				if(bitmap[h][w] == 1)
				{
					visited[h][w] = 1;
					que.push(make_pair(w, h));
				}
			}
		}

		while(!que.empty())
		{
			pair<int, int> element = que.front();
			que.pop();

			int w = element.first;
			int h = element.second;

			visited[h][w] = 1;

			const int possibleMoves = 4;
			int moves[possibleMoves][2] = {{w + 1, h}, {w - 1, h}, {w, h + 1}, {w, h - 1}};
			for(int j = 0; j < possibleMoves; j++)
			{
				int possibleMoveX = moves[j][0];
				int possibleMoveY = moves[j][1];

				// should we check it out?! YES!
				if(possibleMoveX >= 0 && possibleMoveY >= 0 && possibleMoveX < width && possibleMoveY < height
					&& visited[possibleMoveY][possibleMoveX] == 0)
				{
					bitmap[possibleMoveY][possibleMoveX] = bitmap[h][w] + 1;
					que.push(make_pair(possibleMoveX, possibleMoveY));

					visited[possibleMoveY][possibleMoveX] = 1;
				}
			}
		}

		for(int k = 0; k < height; k++)
		{
			for(int v = 0; v < width; v++)
			{
				printf("%d ", bitmap[k][v] - 1);
				bitmap[k][v] = 0;
			}
			printf("\n");
		}

		// reset to zero
		for(int v = 0; v < 183; v++)
			for(int k = 0; k < 183; k++)
				visited[v][k] = 0;
	}

	return 0;
}
