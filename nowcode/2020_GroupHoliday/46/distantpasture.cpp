/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-12 09:21:54
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-16 12:28:22
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int n, A, B, id[35][35], ans, dis[1001], vis[1001], head[1001], tot = 0;
struct Edge
{
    int to, w, nxt;
} edge[maxn];
char mp[35][35];
void addEdge(int fr, int to, int w)
{
    edge[tot] = (Edge){to, w, head[fr]};
    head[fr] = tot++;
}
void dij(int s)
{
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[s] = 0;
    vis[s] = true;
    queue<int> Q;
    Q.push(s);
    while (!Q.empty())
    {
        int now = Q.front();
        Q.pop();
        vis[now] = false;
        for (int i = head[now]; ~i; i = edge[i].nxt)
        {
            int u = edge[i].to;
            if (dis[u] > dis[now] + edge[i].w)
            {
                dis[u] = dis[now] + edge[i].w;
                if (!vis[u])
                    vis[u] = true, Q.push(u);
            }
        }
    }
    for (int i = 1; i <= n * n; i++)
        ans = max(ans, dis[i]);
}
int main()
{
    scanf("%d %d %d", &n, &A, &B);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf(" %c", &mp[i][j]);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            id[i][j] = (i - 1) * n + j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < n; j++)
        {
            int d = mp[i][j] == mp[i][j + 1] ? A : B;
            addEdge(id[i][j], id[i][j + 1], d);
            addEdge(id[i][j + 1], id[i][j], d);
        }
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= n; j++)
        {
            int d = mp[i][j] == mp[i + 1][j] ? A : B;
            addEdge(id[i][j], id[i + 1][j], d);
            addEdge(id[i + 1][j], id[i][j], d);
        }
    ans = 0;
    for (int i = 1; i <= n * n; i++)
        dij(i);
    printf("%d", ans);
    return 0;
}