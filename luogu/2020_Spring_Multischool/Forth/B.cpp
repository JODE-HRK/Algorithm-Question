#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7, mod = 1e9 + 7;
int n, m, c;
int d[maxn];
int g[1001][1001];
set<int> M[maxn]; //set不会记录重复的数
int ppow(int x, int y)
{
    int sum = 1;
    while (y)
    {
        if (y & 1)
            sum = 1ll * sum * x % mod;
        y >>= 1;
        x = 1ll * x * x % mod;
    }
    return sum;
}
int main()
{
    int mn = mod, mx = -mod;
    scanf("%d %d %d", &n, &m, &c);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &g[i][j]), mn = min(mn, g[i][j]), mx = max(mx, g[i][j]);
    if (mn == mx) //没有相连的时候，概率期望值就是1
    {
        cout << "1";
        return 0;
    }
    for (int i = 1; i <= c; i++)
        M[i].insert(i);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (i > 1)
                M[g[i][j]].insert(g[i - 1][j]);
            if (i < n)
                M[g[i][j]].insert(g[i + 1][j]);
            if (j > 1)
                M[g[i][j]].insert(g[i][j - 1]);
            if (j < m)
                M[g[i][j]].insert(g[i][j + 1]);
        }
    int ans = 0;
    for (int i = 1; i <= c; i++)
        ans = (ans + ppow(M[i].size(), mod - 2)) % mod; //逆元
    printf("%d", (c - ans + mod) % mod);
    return 0;
}