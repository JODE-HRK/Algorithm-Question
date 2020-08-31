#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 4e5 + 7;
int n, k;
ll dp[maxn][10], sz[maxn], ans;
vector<int> G[maxn];
void dfs(int now, int fa, int d)
{
    sz[now] = 1;
    dp[now][d % k] = 1;
    // dep[now] = dep[fa] + 1;
    // int s[k];
    for (int i = 0; i < G[now].size(); i++)
        if (G[now][i] != fa)
        {
            int to = G[now][i];
            dfs(to, now, d + 1);
            for (int ip = 0; ip < k; ip++)
            {
                for (int j = 0; j < k; j++)
                {
                    int x = (ip + j - d * 2) % k;
                    int y = (k - x) % k;
                    ans += y * dp[now][ip] * dp[to][j];
                }
            }
            for (int ip = 0; ip < k; ip++)
                dp[now][ip] += dp[to][ip];
            ans += (n - sz[to]) * sz[to];
            sz[now] += sz[to];
        }
}
int main()
{
    scanf("%d %d", &n, &k);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0, 0);
    printf("%lld", ans / k);
    return 0;
}