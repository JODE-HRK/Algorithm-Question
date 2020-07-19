/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-16 16:57:48
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-16 17:28:11
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int n, m, tot, a, b, ans, s = 1, t = n, anscost, ansflow;
int cost[maxn], flow[maxn];
int head[maxn], eid[maxn], pre[maxn];
bool vis[maxn];
struct Edge
{
    int to, flow, cost, nxt;
} edge[maxn];
void init()
{
    tot = 0;
    fill(head, head + 1 + n, -1);
    fill(vis, vis + 1 + n, 0);
}
void addEdge(int fr, int to, int w)
{
    edge[tot] = (Edge){to, 1, w, head[fr]};
    head[fr] = tot++;
}
int spfa()
{
    fill(cost, cost + n + 1, 0x7fffffff);
    fill(flow, flow + 1 + n, 0x7fffffff);
    queue<int> Q;
    while (!Q.empty())
        Q.pop();
    Q.push(s);
    cost[s] = 0, pre[t] = 0;
    while (!Q.empty())
    {
        int now = Q.front();
        Q.pop();
        vis[now] = 0;
        for (int i = head[now]; ~i; i = edge[i].nxt)
        {
            if (edge[i].flow && cost[now] + edge[i].cost < cost[edge[i].to])
            {
                cost[edge[i].to] = cost[now] + edge[i].cost;
                pre[edge[i].to] = now;
                eid[edge[i].to] = i;
                flow[edge[i].to] = min(flow[now], edge[i].flow);
                if (!vis[edge[i].to])
                    Q.push(edge[i].to), vis[edge[i].to] = 1;
            }
        }
    }
    return pre[t];
}
void MCMF()
{
    ansflow = anscost = 0;
    while (spfa())
    {
        ansflow += flow[t];
        anscost += (flow[t] * cost[t]);
        for (int i = t; i != s; i = pre[i]) //根据pre记录回退更新边
        {
            edge[eid[i]].flow -= flow[t];
            edge[eid[i] ^ 1].flow += flow[t];
        }
    }
}
int main()
{
    while (~scanf("%d %d", &n, &m))
    {
        init();
        for (int i = 1; i <= m; i++)
        {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            addEdge(u, v, w);
            addEdge(v, u, -w);
        }
        int q;
        scanf("%d", &q);
        while (q--)
        {
            scanf("%d %d", &a, &b);
            ans = 0;
            MCMF();
            printf("%d/%d\n", ans, b);
        }
    }
    return 0;
}