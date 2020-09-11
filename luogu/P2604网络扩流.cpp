/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-31 20:40:32
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-09-11 00:06:53
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 7;
int n, m, k, st, en;
struct Edge
{
    int to, nxt;
    ll flow, cost;
} edge[maxn << 1];
int head[maxn], tot = 0;
int u[maxn], v[maxn], cost[maxn], f[maxn];
int dis[maxn], cur[maxn];
ll ansflow, anscost;
void addEdge(int fr, int to, ll fl, ll c)
{
    edge[tot].to = to, edge[tot].flow = fl, edge[tot].cost = c, edge[tot].nxt = head[fr];
    head[fr] = tot++;
}
void init()
{
    for (int i = 0; i <= tot; i++)
        cur[i] = head[i];
}
bool bfs()
{
    fill(dis, dis + 1 + n, -1);
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
        init();
        ans += dfs(st, 0x7fffffff); //一次dfs完成所有增广
    }
    return ans;
}
ll flow[maxn], c[maxn];
int pre[maxn], eid[maxn], vis[maxn];
int spfa()
{
    fill(c, c + n + 1, 0x7fffffff);
    fill(flow, flow + 1 + n, 0x7fffffff);
    // fill(vis, vis + 1 + n, 0);SPFA无需重制，在此处查询流
    queue<int> Q;
    while (!Q.empty())
        Q.pop();
    Q.push(st);
    c[st] = 0, pre[en] = 0;
    while (!Q.empty())
    {
        int now = Q.front();
        Q.pop();
        vis[now] = 0;
        for (int i = head[now]; ~i; i = edge[i].nxt)
        {
            if (edge[i].flow && c[now] + edge[i].cost < c[edge[i].to])
            {
                c[edge[i].to] = c[now] + edge[i].cost;
                pre[edge[i].to] = now;
                eid[edge[i].to] = i;
                flow[edge[i].to] = min(flow[now], edge[i].flow);
                if (!vis[edge[i].to])
                    Q.push(edge[i].to), vis[edge[i].to] = 1;
            }
        }
    }
    return pre[en];
}
void MCMF()
{
    ansflow = anscost = 0;
    while (spfa())
    {
        // printf("%d\n", pre[en]);
        ansflow += flow[en];
        anscost += (flow[en] * c[en]);
        for (int i = en; i != st; i = pre[i]) //根据pre记录回退更新边
        {
            edge[eid[i]].flow -= flow[en];
            edge[eid[i] ^ 1].flow += flow[en];
        }
    }
}
int main()
{
    scanf("%d %d %d", &n, &m, &k);
    fill(head, head + 1 + n, -1);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d %d %d %d", &u[i], &v[i], &f[i], &cost[i]);
        addEdge(u[i], v[i], 1ll * f[i], 0);
        addEdge(v[i], u[i], 0, 0);
    }
    st = 1, en = n;
    printf("%lld ", Dinic());
    addEdge(0, 1, k, 0);
    addEdge(1, 0, 0, 0);
    st = 0;
    for (int i = 1; i <= m; i++)
    {
        addEdge(u[i], v[i], 0x7fffffff, cost[i]);
        addEdge(v[i], u[i], 0, -cost[i]);
    }
    MCMF();
    printf("%lld", anscost);
    return 0;
}