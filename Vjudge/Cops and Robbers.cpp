#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 7;
int n, m, c;
int st, en;
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
    head[s] = tot++;
    edge[tot].to = s, edge[tot].w = 0, edge[tot].nxt = head[c];
    head[c] = tot++;
}
int cur[maxn << 1];
void init()
{
    for (int i = 0; i <= tot; i++)
        cur[i] = head[i];
}
bool bfs()
{
    memset(dis, -1, sizeof(dis));
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
{
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
int Movx[4] = {0, -1, 0, 1};
int Movy[4] = {1, 0, -1, 0};
char g[101][101];
int w[30001], cnt = 0;
int getid(int x, int y, int p)
{
    if (x < 1 || x > n || y < 1 || y > m)
        return 2 * n * m + 101;
    return 2 * ((x - 1) * m + y - 1) + p;
}
int main()
{
    scanf("%d %d %d", &m, &n, &c);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++)
        scanf("%s", g[i] + 1);
    for (int i = 1; i <= c; i++)
        scanf("%d", &w[i]);
    st = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (g[i][j] == 'B')
                st = getid(i, j, 1);
            else if (g[i][j] == '.')
                addEdge(getid(i, j, 0), getid(i, j, 1), 0x7fffffff);
            else
                addEdge(getid(i, j, 0), getid(i, j, 1), w[g[i][j] - 'a' + 1]);
            addEdge(getid(i, j, 1), getid(i - 1, j, 0), 0x7fffffff);
            addEdge(getid(i, j, 1), getid(i, j - 1, 0), 0x7fffffff);
            addEdge(getid(i, j, 1), getid(i + 1, j, 0), 0x7fffffff);
            addEdge(getid(i, j, 1), getid(i, j + 1, 0), 0x7fffffff);
        }
    en = 2 * n * m + 101;
    ll ans = Dinic();
    if (ans < 1ll * 0x7fffffff)
        printf("%d", ans);
    else
        printf("-1");
    return 0;
}