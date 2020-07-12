#include <bits/stdc++.h>
using namespace std;
#define inf 0x7fffffff
#define maxn 5005
#define maxm 200005
struct edge
{
    int v, w, next;
} e[maxm << 1];
int head[maxn], dis[maxn], cnt, n, m, tot, now = 1, ans;
bool vis[maxn];
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return x * f;
}
inline void add(int u, int v, int w)
{
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
} //向前星邻接表
inline void init()
{
    n = read(), m = read();
    for (int i = 1, u, v, w; i <= m; ++i)
    {
        u = read(), v = read(), w = read();
        add(u, v, w), add(v, u, w); //建立邻接表
    }
}
inline int prim()
{
    for (int i = 2; i <= n; ++i)
        dis[i] = inf;
    for (int i = head[1]; i; i = e[i].next)
        dis[e[i].v] = min(dis[e[i].v], e[i].w); //更新所有剩余的点到当前节点的距离
    while (++tot < n)
    {
        int minn = inf;
        vis[now] = 1;
        for (int i = 1; i <= n; ++i)
            if (!vis[i] && minn > dis[i])
                minn = dis[i], now = i; //首先从起始位置选出一个离我们需要的点集最近的点
        ans += minn;
        for (int i = head[now]; i; i = e[i].next)
        {
            int v = e[i].v;
            if (dis[v] > e[i].w && !vis[v])
                dis[v] = e[i].w; //更新所有剩余的点到当前节点的距离
        }
    }
    return ans;
}
int main()
{
    init();
    printf("%d", prim());
    return 0;
}