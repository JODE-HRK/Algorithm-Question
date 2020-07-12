#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int n, m, in[maxn], out[maxn], id[maxn];
bool vis[maxn];
vector<int> edge[maxn];
void add(int x, int y)
{
    edge[x].push_back(y);
}
bool cmp(int x, int y)
{
    if (in[x] == in[y])
        return out[x] > out[y];
    return in[x] < in[y];
}
queue<int> Q;
queue<int> S;
int ans = 0;
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        out[u]++, in[v]++;
        add(u, v);
    }
    int ans = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++)
        if (!in[i])
            Q.push(i);
    while (!Q.empty())
    {
        int now = Q.front();
        S.push(now);
        Q.pop();
        for (auto v : edge[now])
            if (--in[v] == 0) //注意这个地方，拓扑排序一定要是这个，不然会炸
                Q.push(v);
    }
    while (!S.empty())
    {
        int now = S.front();
        S.pop();
        if (!vis[now])
            ans++, vis[now] = 1;
        else
            continue;
        for (auto v : edge[now])
            vis[v] = 1;
    }
    printf("%d", ans);
    return 0;
}