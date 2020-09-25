#include <bits/stdc++.h>
using namespace std;
int n, m;
int w[1001], val[1001], k;
vector<int> G[1001];
int dp[1001];
int main()
{
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d %d", &w[i], &val[i], &k);
        G[k].push_back(i);
    }
    fill(dp, dp + 1 + m, 0);
    // printf("YES\n");
    for (int i = 1; i <= n; i++)
    {
        int l = G[i].size();
        for (int p = m; p >= 0; p--)
            for (int j = 0; j < l; j++) //对于每一组中的每一个物品都要单独做
            {
                int id = G[i][j];
                if (w[id] <= p) //分组背包需要判断
                    dp[p] = max(dp[p], dp[p - w[id]] + val[id]);
            }
    }
    printf("%d", dp[m]);
    return 0;
}