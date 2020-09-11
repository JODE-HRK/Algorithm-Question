/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-31 20:40:32
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-09-11 10:48:49
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 7;
int n, m, k, st, en;
struct Edge
{
    int to, nxt;
    ll flow;
} edge[maxn << 1];
int head[maxn], tot = 0;
int u[maxn], v[maxn], cost[maxn], f[maxn];
int dis[maxn], cur[maxn];
ll ansflow, anscost;
void addEdge(int fr, int to, ll fl)
{
    edge[tot].to = to, edge[tot].flow = fl, edge[tot].nxt = head[fr];
    head[fr] = tot++;
}
void init()
{
    for (int i = 0; i <= tot; i++)
        cur[i] = head[i];
}
bool bfs()
{
    fill(dis, dis + 1 + 2 * n, -1);
    queue<int> Q;
    while (!Q.empty())
        Q.pop();
    Q.push(st);
    dis[st] = 0;
    while (!Q.empty())
    {
        int now = Q.front();
        Q.pop();
        for (int i = head[now]; ~i; i = edge[i].nxt)
        {
            int v = edge[i].to;
            if (edge[i].flow && dis[v] == -1)
            {
                dis[v] = dis[now] + 1;
                if (v == en)
                    return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}
ll dfs(int s, ll flow)
{
    if (s == en)
        return flow;
    ll _flow = 0, __flow;
    for (int i = cur[s]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (dis[v] == dis[s] + 1 && edge[i].flow)
        {
            __flow = dfs(v, min(flow, edge[i].flow));
            flow -= __flow;
            edge[i].flow -= __flow;
            _flow += __flow;
            edge[i ^ 1].flow += __flow;
            if (!flow)
                break;
        }
    }
    if (!_flow)
        dis[s] = -1;
    return _flow;
}
ll Dinic()
{
    ll ans = 0;
    while (bfs())
    { //bfs构建层次网络 判断是否存在一条到en的点
        // printf("YES\n");
        init();
        ans += dfs(st, 0x7fffffff); //一次dfs完成所有增广
    }
    return ans;
}
struct E
{
    int to, w;
};
vector<E> G[maxn], NG[maxn];
int D[maxn];
bool vis[maxn];
void dij()
{
    fill(D, D + 1 + n, 0x7fffffff);
    fill(vis, vis + 1 + n, 0);
    queue<int> Q;
    Q.push(1);
    D[1] = 0;
    while (!Q.empty())
    {
        int x = Q.front();
        Q.pop();
        if (x == n)
            continue;
        vis[x] = 0;
        int l = G[x].size();
        for (int i = 0; i < l; i++)
        {
            E tp = G[x][i];
            int to = tp.to, ww = tp.w;
            if (D[to] >= D[x] + ww)
            {
                if (D[to] > D[x] + ww)
                    NG[to].clear();
                NG[to].push_back((E){x, ww});
                D[to] = D[x] + ww;
                if (!vis[to])
                    Q.push(to), vis[to] = 1;
            }
        }
    }
}
int main()
{
    scanf("%d %d", &n, &m);
    fill(head, head + 1 + 2 * n, -1);
    for (int i = 1; i <= m; i++)
    {
        int fr, to, w;
        scanf("%d %d %d", &fr, &to, &w);
        G[fr].push_back((E){to, w});
        G[to].push_back((E){fr, w});
    }
    dij();
    // printf("%d\n", D[n]);
    int x;
    scanf("%d", &x);
    for (int i = 2; i < n; i++)
    {
        scanf("%d", &x);
        addEdge(i, n + i, x);
        addEdge(n + i, i, 0);
    }
    scanf("%d", &x);
    int l = NG[n].size();
    for (int i = 0; i < l; i++)
    {
        int to = NG[n][i].to;
        addEdge(n, to, 0x7fffffff);
        addEdge(to, n, 0);
    }
    for (int i = 2; i < n; i++)
    {
        l = NG[i].size();
        for (int j = 0; j < l; j++)
        {
            int to = NG[i][j].to;
            addEdge(i + n, to, 0x7fffffff);
            addEdge(to, i + n, 0);
        }
    }
    st = n,
    en = 1;
    printf("%lld ", Dinic());
    return 0;
}