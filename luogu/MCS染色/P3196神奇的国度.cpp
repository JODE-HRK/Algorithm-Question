#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int n, m, ans, htot, Htot;
int head[maxn], q[maxn], d[maxn], H[maxn], color[maxn], num[maxn], mark[maxn];
int point[maxn]; //优先队列方法使用
bool vis[maxn];
struct Edge
{
    int fr, to, nxt;
} edge[maxn << 1], Bstedge[maxn << 4];
struct Pot
{
    int val, id;
    bool operator<(const Pot x) const
    {
        return val < x.val;
    }
}; //优先队列使用
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
void addEdge(int h[], int u, int v, Edge e[])
{
    e[htot] = (Edge){u, v, h[u]};
    h[u] = htot++;
}
void init()
{
    fill(head, head + 1 + n, -1);
    fill(vis, vis + 1 + n, 0);
    fill(q, q + 1 + n, 0);
    fill(color, color + 1 + n, 0);
    fill(num, num + 1 + n, 0);
    fill(point, point + 1 + n, 0);
    fill(mark, mark + 1 + n, 0);
    htot = Htot = 0;
}
void MCSbfs() //优先队列版本,此版本写起来简单，但是无法记录颜色，并且时间稍高,需要开O2
{
    priority_queue<Pot> Q;
    ans = 0;
    Q.push((Pot){0, 1});
    while (!Q.empty())
    {
        Pot now = Q.top();
        Q.pop();
        if (vis[now.id])
            continue;
        vis[now.id] = 1;
        int u = now.id;
        if (!color[now.val])
            color[now.val] = 1, ++ans;
        for (int i = head[u]; ~i; i = edge[i].nxt)
        {
            int v = edge[i].to;
            if (vis[v])
                continue;
            point[v]++;
            Q.push((Pot){point[v], v});
        }
    }
}
void MCS()
{
    int i, j, bst = 0;
    for (i = 1; i <= n; i++)
        addEdge(H, 0, i, Bstedge);
    for (j = n; j; j--)
    {
        while (1)
        {
            for (i = H[bst]; i; i = Bstedge[i].nxt)
            {
                if (!vis[Bstedge[i].to])
                    break;
                else
                    H[bst] = Bstedge[i].nxt;
            }
            if (i)
            {
                int x = Bstedge[i].to;
                q[j] = x;
                vis[x] = 1;
                for (i = head[x]; ~i; i = edge[i].nxt)
                    if (!vis[edge[i].to])
                    {
                        int to = edge[i].to;
                        d[to]++;
                        addEdge(H, d[to], to, Bstedge);
                        bst = max(bst, d[to]);
                    }
                break;
            }
            else
                bst--;
        }
    }
    for (j = n; j; j--)
    {
        int x = q[j];
        for (i = head[x]; ~i; i = edge[i].nxt)
            mark[color[edge[i].to]] = j;
        int id = 1;
        while (id <= n && mark[id] == j)
            id++;
        color[x] = id;
        ans = max(ans, id);
    }
}
int main()
{
    n = read(), m = read();
    init();
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        a = read(), b = read();
        addEdge(head, a, b, edge);
        addEdge(head, b, a, edge);
    }
    // MCSbfs();
    MCS();
    printf("%d\n", ans);
    // for (int i = 1; i <= n; i++)
    // printf("%d ", color[i]);
    return 0;
}