#include <bits/stdc++.h>
using namespace std;
const int maxn = 41;
const int mod = 998244353;
int a[maxn], b[maxn], n, m;
bool g[maxn][maxn], vis[maxn];
int ansA = 0, ansB = 0;
void get_Complement_graph()
{ //获得补图
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
                g[i][j] ^= 1;
}
void dfs(int s, int A, int B)
{
    if (s > n)
    {
        ansA = (ansA + A) % mod, ansB = (ansB + B) % mod;
        return;
    }
    if (vis[s]) //该点不能被选
    {
        dfs(s + 1, A, B);
        return;
    }
    int sum = 0;
    for (int i = s + 1; i <= n; i++)
        if (g[s][i] && !vis[i])
            sum++;
    if (!sum) //如果该点为孤立点
        dfs(s + 1, 1ll * A * (a[s] + 1) % mod, 1ll * B * (b[s] + 1) % mod);
    else
    {
        dfs(s + 1, A, B); //不选这个点
        queue<int> Q;
        while (!Q.empty())
            Q.pop();
        for (int i = s + 1; i <= n; i++)
            if (g[s][i] && !vis[i])
                vis[i] = 1, Q.push(i);
        dfs(s + 1, 1ll * A * a[s] % mod, 1ll * B * b[s] % mod); //选择这个点
        while (!Q.empty())
        {
            vis[Q.front()] = 0;
            Q.pop();
        }
    }
}
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u][v] = g[v][u] = 1;
    }
    get_Complement_graph();
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]);
    dfs(1, 1, 1);
    ansA--, ansB--;
    ansA = (ansA + mod) % mod, ansB = (ansB + mod) % mod;
    int ans = 1ll * ansA * ansB % mod;
    printf("%d", ans);
    return 0;
}