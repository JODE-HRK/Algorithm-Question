#include <bits/stdc++.h>
#define ll long long
using namespace std;
int v[2010], n;
ll dp[2010][2010];
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &v[i]);
	// dp[0][0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= i; j++)
		{
			int right = i - j;
			dp[i][j] = max(dp[i - 1][j] + v[n - right + 1] * i, dp[i - 1][j - 1] + v[j] * i);
		}
	ll ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans = max(ans, dp[n][i]);
	}
	printf("%lld", ans);
	return 0;
}