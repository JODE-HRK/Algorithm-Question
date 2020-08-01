#include <bits/stdc++.h>
using namespace std;
// const int inf = 0x7fffffff;
const int maxn = 1e5 + 7;
int n, m, s, t;
int r[maxn], c[maxn], sum = 0;
int head[maxn], tot = 0, cur[maxn], dis[maxn];
struct Edge
{
    int to, flow, nxt;
} edge[2 * (maxn << 3)];
void addEdge(int fr, int to, int w)
{
    edge[tot] = (Edge){to, w, head[fr]};
    head[fr] = tot++;
}
void init()
{
    for (int i = 0; i <= tot; i++)
        cur[i] = head[i];
}
bool bfs()
{
    fill(dis, dis + 2 + n + m, -1);
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
            if (edge[i].flow && dis[v] == -1)
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
int dfs(int st, int flow)
{
    if (st == t)
        return flow;
    int _flow = 0, __flow;
    for (int i = cur[st]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (dis[v] == dis[st] + 1 && edge[i].flow)
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
        dis[st] = -1;
    return _flow;
}
int Dinic()
{
    int ans = 0;
    while (bfs())
    { //bfs构建层次网络 判断是否存在一条到en的点
        init();
        ans += dfs(s, 0x7fffffff); //一次dfs完成所有增广
    }
    // return ans;
    if (ans == sum)
        return 1;
    return 0;
}
int main()
{
    // freopen(".in", "r", stdin);
    scanf("%d %d", &n, &m);
    fill(head, head + n + m + 10, -1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &r[i]), sum += r[i];
    for (int j = 1; j <= m; j++)
        scanf("%d", &c[j]);
    s = 0, t = n + m + 1;
    for (int i = 1; i <= n; i++)
    {
        addEdge(s, i, r[i]);
        addEdge(i, s, 0);
    }
    for (int j = 1; j <= m; j++)
    {
        addEdge(j + n, t, c[j]);
        addEdge(t, j + n, 0);
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            addEdge(i, j + n, 1);
            addEdge(j + n, i, 0);
        }
    if (Dinic())
    {
        printf("1\n");
        for (int i = 1; i <= n; i++)
        {
            for (int j = head[i]; ~j; j = edge[j].nxt)
                if (edge[j].flow == 0)
                    printf("%d ", edge[j].to - n);
            cout << endl;
        }
    }
    else
        printf("0\n");
    return 0;
}