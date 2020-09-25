#include <bits/stdc++.h>
using namespace std;
int V, W;
int n;
int v[51], w[51], val[51];
int dp[500][500];
int main()
{
    scanf("%d %d", &V, &W);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d %d", &v[i], &w[i], &val[i]);
    for (int i = 1; i <= n; i++)
    {
        for (int j = V; j >= v[i]; j--)
            for (int k = W; k >= w[i]; k--)
            {
                dp[j][k] = max(dp[j][k], dp[j - v[i]][k - w[i]] + val[i]);
            }
    }
    printf("%d", dp[V][W]);
    return 0;
}