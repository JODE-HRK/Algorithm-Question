#include <bits/stdc++.h>
using namespace std;
int n, k;
int dp[1010][1010];
bool judge(int col, int row, int i, int j)
{
	if (col & i == 0 && row & j == 0)
		return 1;
	return 0;
}
int main()
{
	scanf("%d %d", &n, &k);
	int state = (1 << n), ans = 0;
	memset(dp, 0, sizeof(dp));
	for (int col = 0; col < state; col++)
	{
		for (int row = 0; row < state; row++)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
					if (judge(col, row, i, j))
					{
						int ccol, rrow;
						ccol = col | i | max(i - 1, 0) | min(i + 1, n - 1);
						rrow = row | i | max(i - 1, 0) | min(i + 1, n - 1);
						dp[ccol][rrow] = max(dp[ccol][rrow], dp[col][row] + 1);
						if (dp[ccol][rrow] == k)
							ans++;
					}
			}
		}
	}
	printf("%d", ans);
	return 0;
}