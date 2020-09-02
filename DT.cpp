#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
int n, m, q, cntnode = n;
int b[maxn], h[maxn], fa[maxn], val[maxn], sz[maxn], dfn[maxn], tot = 0;
vector<int> G[maxn];
struct Edge
{
    int fr, to, w;
    bool operator<(const Edge &x) const
    {
        return w < x.w;
    }
} edge[maxn];
int getfa(int x)
{
    return x == fa[x] ? x : fa[x] = getfa(fa[x]);
}
void dfs(int now, int father)
{
    sz[now] = 1;
    dfn[now] = ++tot;
    int l = G[now].size();
    for (int i = 0; i < l; i++)
    {
        int to = G[now][i];
        if (to == father)
            continue;
        dfs(to, now);
        sz[now] += sz[to];
    }
}
int main()
{
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &h[i]), b[i] = h[i], fa[i] = i, val[i] = 0;
    sort(b + 1, b + 1 + n);
    int num = unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 1; i <= n; i++)
        h[i] = lower_bound(b + 1, b + 1 + n, h[i]) - b;
    for (int i = 1; i <= m; i++)
        scanf("%d %d %d", &edge[i].fr, &edge[i].to, &edge[i].w);
    sort(edge + 1, edge + 1 + m);
    int cnt = 0;
    for (int i = 1; i <= m; i++)
    {
        int fr = getfa(edge[i].fr), to = getfa(edge[i].to);
        if (fr != to)
        {
            fa[getfa(fr)] = fa[getfa(to)] = ++cntnode;
            val[cntnode] = edge[i].w;
            G[fr].push_back(cntnode);
            G[to].push_back(cntnode);
            G[cntnode].push_back(fr);
            G[cntnode].push_back(to);
            cnt++;
        }
        if (cnt == n - 1)
            break;
    }
    dfs(1, 0);
}