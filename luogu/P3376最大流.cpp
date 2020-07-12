#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int n, m, s, t, cnt = 0;
int dis[maxn], head[maxn];
struct Edge
{
    int to, w, nxt;
} edge[maxn];
bool vis[maxn];
bool bfs() //bfs判断是否能继续走到汇点，就是建立到汇点的分层图
{
    fill(dis, dis + 1 + n, -1); //分配深度
    queue<int> Q;
    Q.push(s);
    dis[s] = 0;
    while (!Q.empty())
    {
        int now = Q.front();
        Q.pop();
        for (int i = head[now]; ~i; i = edge[i].nxt)
        {
            int v = edge[i].to;
            if (edge[i].w > 0 && dis[v] == -1)
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
int cur[maxn]; //弧优化，，cur数组记录上一次dfs增广时 u已经增广到了第几条边，从而优化时间
int dfs(int st, int flow)
{
    if (t == st)
        return flow;
    for (int i = cur[st]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (dis[v] == dis[st] + 1 && edge[i].w > 0)
        {
            int k = dfs(v, min(flow, edge[i].w)); //最多只能流，所以采用min函数
            if (k)
            {
                edge[i].w -= k;
                edge[i ^ 1].w += k; //使用异或的巧妙性：总会对着相反的边进行处理，因为奇数偶数的关系
                return k;
            }
        }
    }
    return 0;
}
void init()
{
    for (int i = 0; i <= cnt + 1; i++) //初始化cur数组，即将head数组赋给cur数组
        cur[i] = head[i];
}
int dinic()
{
    int ans = 0;  // 记录总流量
    while (bfs()) //bfs建立分层图，以便dfs增广
    {
        init();                    //每一次建立完分层图后都要把cur置为每一个点的第一条边，进行弧优化
        ans += dfs(s, 0x7fffffff); //dfs寻找增广路
    }
    return ans;
}
void add(int fr, int to, int ww)
{
    edge[cnt].to = to, edge[cnt].w = ww, edge[cnt].nxt = head[fr];
    head[fr] = cnt++;
}
int main()
{
    scanf("%d %d %d %d", &n, &m, &s, &t);
    fill(head, head + 2 + 2 * m, -1);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add(u, v, w);
        add(v, u, 0); //添加反向边是为了能够反悔，就如基本性质三的想法
    }
    printf("%d", dinic());
    return 0;
}