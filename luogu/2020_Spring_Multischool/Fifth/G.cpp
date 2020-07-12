#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, c;
char s1[5001], s2[5001];
long long dp[5001][5001];
int main()
{
    scanf("%d %d %d %d %d", &n, &m, &a, &b, &c);
    cin >> s1 + 1 >> s2 + 1;
    for(int i=0;i<=n ||i<=m;i++)
        dp[i][0] = dp[0][i] = -i *1ll* c;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = max(max(dp[i - 1][j], dp[i][j - 1]) - c, dp[i - 1][j - 1] + (s1[i] == s2[j] ? a : -b));

    printf("%lld",dp[n][m]);
    return 0;
}