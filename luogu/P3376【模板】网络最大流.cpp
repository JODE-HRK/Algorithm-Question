#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 7;
int n, m, st, en;
struct Edge
{
    int to, nxt;
    ll w;
} edge[maxn << 1];
int head[maxn], tot = 0;
int dis[maxn];
void addEdge(int s, int c, int w)
{
    edge[tot].to = c, edge[tot].w = w, edge[tot].nxt = head[s];
    head[s] = tot++; // 必然是tot++，0号位必须占用对应下面的 ~i
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
ll dfs(int s, ll flow)
{ //更快的dfs寻找增广路，其实是优化了下一个bfs
    if (s == en)
        return flow;
    ll _flow = 0, __flow;
    for (int i = cur[s]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (dis[v] == dis[s] + 1 && edge[i].w)
        {
            __flow = dfs(v, min(flow, edge[i].w));
            flow -= __flow;
            edge[i].w -= __flow;
            _flow += __flow;
            edge[i ^ 1].w += __flow;
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