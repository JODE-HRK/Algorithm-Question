/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-17 12:07:40
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-17 12:07:48
 */
#include <bits/stdc++.h>
#define ll long long
#define inf 0x7fffffff
#define INF 1000000000000ll
#define pii pair<int, int>
#define pll pair<ll, ll>
const int maxn = 1e6 + 7;
using namespace std;
inline int read()
{
    int x = 0;
    char c = getchar();
    while (c > '9' || c < '0')
        c = getchar();
    while (c >= '0' && c <= '9')
        x = x * 10 + c - '0', c = getchar();
    return x;
}
int head[maxn], tot = 0;
struct Edge
{
    int fr, to, w, nxt;
} edge[maxn];
int n, m, s, t;
int ans = 0;
void addEdge(int fr, int to, int w)
{
    edge[tot] = (Edge){fr, to, w, head[fr]};
    head[fr] = tot++;
}
int dis[maxn], cur[maxn];
bool bfs()
{
    fill(dis, dis + 1 + n * 2 + 1, -1);
    queue<int> Q;
    while (!Q.empty())
        Q.pop();
    Q.push(s);
    dis[s] = 0;
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
                if (v == t)
                    return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}
void init()
{
    for (int i = 0; i <= n * 2 + 1; i++)
        cur[i] = head[i];
}
int dfs(int now, int flow)
{
    if (now == t)
        return flow;
    int _flow = 0, __flow;
    for (int i = cur[now]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (dis[v] == dis[now] + 1 && edge[i].w)
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
        dis[now] = -1;
    return _flow;
}
void MCMF()
{
    while (bfs())
    {
        init();
        ans += dfs(s, inf);
    }
}
int fa[maxn];
void getans(int x)
{
    printf("%d ", x);
    for (int i = head[x]; ~i; i = edge[i].nxt)
        if (edge[i].fr > 0 && edge[i].fr <= n && edge[i].w == 0 && edge[i].to > n && edge[i].to <= 2 * n)
            getans(edge[i].to - n);
}
int main()
{
    n = read(), m = read();
    fill(head, head + 1 + 2 * n + 1, -1);
    s = 0, t = n << 1 | 1;
    while (m--)
    {
        int a, b;
        a = read(), b = read();
        addEdge(a, b + n, 1);
        addEdge(b + n, a, 0);
    }
    for (int i = 1; i <= n; i++)
    {
        addEdge(s, i, 1), addEdge(i, s, 0);
        addEdge(n + i, t, 1), addEdge(t, n + i, 0);
    }
    MCMF();
    // printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 0; i < tot; i++)
        if (edge[i].w == 0 && edge[i].fr > 0 && edge[i].fr <= n && edge[i].to > n && edge[i].to <= 2 * n && fa[edge[i].fr] != fa[edge[i].to - n])
            fa[edge[i].to - n] = fa[edge[i].fr];
    for (int i = 1; i <= n; i++)
        if (fa[i] == i)
            getans(i), cout << endl;
    printf("%d", n - ans);
    return 0;
}