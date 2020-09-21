#include <bits/stdc++.h>
using namespace std;
int n, m;
struct OBJ
{
    int l, r, w;
} a[400011];
int cnt;
vector<int> G[201];
int dp[202];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            a[++cnt].l = i, a[cnt].r = j;
            scanf("%d", &a[cnt].w);
            G[i].push_back(cnt);
        }
    fill(dp, dp + 1 + n, 0x7fffffff);
    dp[1] = 0;
    for (int i = 1; i <= n; i++)
    {
        int l = G[i].size();
        for (int j = 0; j < l; j++)
        {
            int id = G[i][j];
            dp[a[id].r] = min(dp[a[id].r], dp[a[id].l] + a[id].w);
        }
    }
    printf("%d", dp[n]);
    return 0;
}