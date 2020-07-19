/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-15 08:53:11
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-15 15:50:31
 */
#include <bits/stdc++.h>
using namespace std;
#define INF 1000000000000LL
typedef long long ll;
const int maxn = 2e6 + 7;
const int sumedge = maxn * 2;
int n, m, tot = 0, s, t;
int head[maxn];
int id[501][501];
ll g[501][501][2];
struct Edge
{
    int to;
    ll w;
    int nxt;
} edge[sumedge];
struct Node
{
    int id;
    ll dis;
    bool operator<(const Node x) const
    {
        return dis > x.dis;
    }
};
void addEdge(int u, int v, ll w)
{
    edge[tot] = (Edge){v, w, head[u]};
    head[u] = tot++;
}
void init()
{
    memset(head, -1, sizeof(head));
    s = 0, t = (n - 1) * n / 2 + 1;
    for (int i = 1, cnt = 0; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            g[i][j][0] = g[i][j][1] = INF, id[i][j] = ++cnt;
}
void build()
{
    for (int l = 1; l < n; l++)
        for (int r = l + 1; r <= n; r++)
        {
            if (r < n)
            {
                ll w = g[l][r][0];
                addEdge(id[l][r], id[l][r + 1], w);
                addEdge(id[l][r + 1], id[l][r], w);
            }
            if (l > 1)
            {
                ll w = g[l][r][1];
                addEdge(id[l][r], id[l - 1][r], w);
                addEdge(id[l - 1][r], id[l][r], w);
            }
        }
    for (int l = 1, r = n; l < n; l++)
    {
        ll w = g[l][r][0];
        addEdge(s, id[l][r], w);
    }
    for (int l = 1, r = 2; r <= n; r++)
    {
        ll w = g[l][r][1];
        addEdge(id[l][r], t, w);
    }
}
ll dis[maxn * 2];
bool vis[maxn * 2];
ll dij()
{
    priority_queue<Node> Q;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    // printf("%lld\n", dis[t]);
    Q.push((Node){s, 0});
    while (!Q.empty())
    {
        Node now = Q.top();
        Q.pop();
        if (vis[now.id])
            continue;
        vis[now.id] = 1;
        for (int i = head[now.id]; ~i; i = edge[i].nxt)
        {
            int to = edge[i].to;
            ll w = edge[i].w;
            if (!vis[to] && dis[to] > dis[now.id] + w)
            {
                dis[to] = dis[now.id] + w;
                Q.push((Node){to, dis[to]});
            }
        }
    }
    return dis[t];
}
int main()
{
    scanf("%d %d", &n, &m);
    init();
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        ll w;
        char sp;
        scanf("%d %d %c %lld", &l, &r, &sp, &w);
        int d = sp == 'L' ? 0 : 1;
        g[l][r][d] = min(g[l][r][d], w);
    }
    build();
    ll ans = dij();
    if (ans >= INF)
        printf("-1");
    else
        printf("%lld", ans);
    return 0;
}