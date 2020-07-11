#include <bits/stdc++.h>
using namespace std;
const int maxn = 210;
int n, m, start, en;
int G[maxn][maxn];
int path[maxn], flow[maxn];
int bfs()
{
    queue<int> Q;
    while (!Q.empty())
        Q.pop();
    Q.push(start);
    memset(path, -1, sizeof(path));
    path[start] = 0, flow[start] = 0x7fffffff;
    while (!Q.empty())
    {
        int tmp = Q.front();
        Q.pop();
        if (tmp == en)
            break;
        for (int i = 1; i <= m; i++)
        {
            if (i != start && path[i] == -1 && G[tmp][i])
            {
                flow[i] = flow[tmp] < G[tmp][i] ? flow[tmp] : G[tmp][i];
                Q.push(i);
                path[i] = tmp;
            }
        }
    }
    if (path[en] == -1)
        return -1;
    return flow[en];
}
int Edmons_Karp()
{
    int max_flow = 0, step, now, pre;
    while ((step = bfs()) != -1)
    {
        max_flow += step;
        now = en;
        while (now != start)
        {
            pre = path[now];
            G[pre][now] -= step;
            G[now][pre] += step;
            now = pre;
        }
    }
    return max_flow;
}
int main()
{
    memset(G, 0, sizeof(G));
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        int fr, to, w;
        scanf("%d %d %d", &fr, &to, &w);
        G[fr][to] += w;
    }
    start = 1, en = m;
    printf("%d\n", Edmons_Karp());
    return 0;
}