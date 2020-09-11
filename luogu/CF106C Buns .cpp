#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
int n, m;
int c[maxn], a[maxn], b[maxn], d[maxn];
int dp[maxn];
int main()
{
    scanf("%d %d %d %d", &n, &m, &c[0], &d[0]);
    //多重背包转01背包
    for (int i = n; i >= c[0]; i--)
        dp[i] = i / c[0] * d[0];
    for (int i = 1; i <= m; i++)
    {
        scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
        for (int j = 1; j <= (a[i] / b[i]); j++)
        {
            for (int k = n; k >= c[i]; k--)
            {
                dp[k] = max(dp[k], dp[k - c[i]] + d[i]);
            }
        }
    }
    printf("%d", dp[n]);
    return 0;
}