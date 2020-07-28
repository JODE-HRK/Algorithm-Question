/*
最大生成树+LCA求路径上的最小值
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
int n, m, tot = 0;
int head[maxn], fa[maxn], depth[maxn];
int sfa[maxn][15], mn[maxn][15];
struct EEdge
{
    int fr, to, w;
    bool operator<(const EEdge x) const
    {
        return w > x.w;
    }
} sedge[maxn];
struct Edge
{
    int fr, to, w, nxt;
} edge[maxn];
void addEdge(int u, int v, int w)
{
    edge[tot] = (Edge){u, v, w, head[u]};
    head[u] = tot++;
}
int fdfa(int x)
{
    return fa[x] == x ? x : fa[x] = fdfa(fa[x]);
}
void dfs(int now, int pa)
{
    for (int i = head[now]; ~i; i = edge[i].nxt)
    {
        int to = edge[i].to, w = edge[i].w;
        if (to == pa)
            continue;
        depth[to] = depth[now] + 1;
        sfa[to][0] = now;
        mn[to][0] = w;
        dfs(to, now);
    }
}
int lca(int u, int v)
{
    if (depth[u] == -1 || depth[v] == -1)
        return -1;
    if (depth[u] > depth[v])
        swap(u, v);
    for (int i = 0; i < 15; i++)
        if ((depth[v] - depth[u]) & (1 << i))
            v = sfa[v][i];
    if (u == v)
        return u;
    for (int i = 14; i >= 0; i--)
        if (sfa[u][i] != sfa[v][i])
            u = sfa[u][i], v = sfa[v][i];
    return sfa[u][0];
}
int ask(int u, int st)
{
    int ret = 0x7fffffff;
    for (int i = 0; i < 15; i++)
        if (st & (1 << i))
            ret = min(ret, mn[u][i]), u = sfa[u][i];
    return ret;
}
int main()
{
    scanf("%d %d", &n, &m);
    fill(head, head + 1 + n, -1);
    fill(depth, depth + 1 + n, -1);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
        scanf("%d %d %d", &sedge[i].fr, &sedge[i].to, &sedge[i].w);
    sort(sedge + 1, sedge + 1 + m);
    int k = 0;
    for (int i = 1; i <= m; i++)
    {
        if (k == n - 1)
            break;
        if (fdfa(sedge[i].fr) != fdfa(sedge[i].to))
        {
            int u = sedge[i].fr, v = sedge[i].to, w = sedge[i].w;
            addEdge(u, v, w);
            addEdge(v, u, w);
            fa[fdfa(v)] = fdfa(u);
            k++;
        }
    }
    depth[1] = 1;
    dfs(1, 0);
    // printf("YES\n");
    for (int i = 1; i < 15; i++)
        for (int j = 1; j <= n; j++)
        {
            sfa[j][i] = sfa[sfa[j][i - 1]][i - 1];
            mn[j][i] = min(mn[j][i - 1], mn[sfa[j][i - 1]][i - 1]);
        }
    int q;
    scanf("%d", &q);
    while (q--)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        int ffa = lca(u, v);
        if (ffa != -1)
            printf("%d\n", min(ask(u, depth[u] - depth[ffa]), ask(v, depth[v] - depth[ffa])));
        else
            printf("-1\n");
    }
    return 0;
}