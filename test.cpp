#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 7;
int n, m, st, en;
struct Edge
{
    int to, w, nxt;
} edge[maxn << 1];
int head[maxn], tot = 0;
int dis[maxn];
void addEdge(int s, int c, int w)
{
    edge[tot].to = c, edge[tot].w = w, edge[tot].nxt = head[s];
    head[s] = tot++;
}
int cur[maxn << 1];
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
            if (edge[i].w && dis[v] == -1)
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
ll dfs(int s, int flow)
{
    if (s == en)
        return flow;
    for (int i = cur[s]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (dis[v] == dis[s] + 1 && edge[i].w)
        {
            int k = dfs(v, min(flow, edge[i].w));
            if (k)
            {
                edge[i].w -= k;
                edge[i ^ 1].w += k;
                return k;
            }
        }
    }
    return 0;
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
int main()
{
    scanf("%d %d %d %d", &n, &m, &st, &en);
    fill(head, head + 2 + 2 * m, -1);
    for (int i = 1; i <= m; i++)
    {
        int fr, to, w;
        scanf("%d %d %d", &fr, &to, &w);
        addEdge(fr, to, w);
        addEdge(to, fr, 0);
    }
    printf("%lld", Dinic());
    return 0;
}