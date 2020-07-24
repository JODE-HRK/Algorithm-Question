#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int n, m, s;
int head[maxn], tot, lg[maxn], fa[maxn][22], depth[maxn];
/*
最近公共祖先
*/
struct LCA
{
    struct Edge
    {
        int fr, to, w, nxt;
    } edge[maxn];
    void init()
    {
        tot = 0;
        fill(head, head + 1 + n, -1);
    }
    void addEdge(int fr, int to, int w)
    {
        edge[tot] = (Edge){fr, to, w, head[fr]};
        head[fr] = tot++;
    }
    void dfs(int now, int father)
    { //dfs建树
        fa[now][0] = father, depth[now] = depth[father] + 1;
        for (int i = 1; (1 << i) <= depth[now]; i++)
            fa[now][i] = fa[fa[now][i - 1]][i - 1];
        for (int i = head[now]; ~i; i = edge[i].nxt)
            if (edge[i].to != father)
                dfs(edge[i].to, now);
    }
    void pre()
    {
        for (int i = 1; i <= n; i++)
            lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
        depth[0] = 0;
        dfs(s, 0);
    }
    int getans(int u, int v)
    {
        if (depth[u] < depth[v])
            swap(u, v);
        while (depth[u] > depth[v])
            u = fa[u][lg[depth[u] - depth[v]] - 1];
        if (u == v)
            return u;
        for (int k = lg[depth[u]] - 1; k >= 0; k--)
            if (fa[u][k] != fa[v][k])
                u = fa[u][k], v = fa[v][k];
        return fa[u][0];
    }
    void getLCA()
    {
        scanf("%d %d %d", &n, &m, &s); //点的数量，询问数量、源点数量
        init();
        for (int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            addEdge(u, v, 0);
            addEdge(v, u, 0);
        }
        pre();
        while (m--)
        {
            int u, v;
            scanf("%d %d", &u, &v); //查询两个点的最近公共祖先
            printf("%d\n", getans(u, v));
        }
    }
};
