#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e4 + 7;
int n, m;
int w[maxn], val[maxn];
int dp[maxn];
int ans[maxn];
int getans(int l, int r, int maxx)
{
    fill(dp, dp + 1 + maxx, 0);
    for (int i = l; i <= r; i++)
        for (int j = maxx; j >= w[i]; j--)
            dp[j] = max(dp[j], dp[j - w[i]] + val[i]);
    return dp[maxx];
} //01背包一定倒序
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    for (int i = 1; i <= m; i++)
    {
        int l, r, t;
        scanf("%d %d %d", &l, &r, &t);
        ans[i] = getans(l, r, t);
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%d\n", ans[i]);
    }
    return 0;
}