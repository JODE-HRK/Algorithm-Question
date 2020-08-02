#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 7;
int n, m, r, p;
int val[maxn], head[maxn], tot = 0;
int opt, x, y, z;
int depth[maxn];
struct Edge
{
    int fr, to, nxt;
} edge[maxn];
void addEdge(int fr, int to)
{
    edge[tot] = (Edge){fr, to, head[fr]};
    head[fr] = tot++;
}
void dfs(int now, int fa)
{
    depth[now] = depth[fa] + 1;
    for (int i = head[now]; ~i; i = edge[i].nxt)
        if (edge[i].to != fa)
            dfs(edge[i].to, now);
}
int main()
{
    scanf("%d %d", &n, &m, &r, &p);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    depth[0] = 0;
    dfs(1, 0);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &opt);
        if (opt == 1)
        {
            scanf("%d %d %d", &x, &y, &z);
            pathAdd(x, y, z);
        }
        else if (opt == 2)
        {
            scanf("%d %d", &x, &y);
        }
        else if (opt == 3)
        {
            scanf("%d %d", &x, &z);
        }
        else
        {
            scanf("%d", &x);
        }
    }
}