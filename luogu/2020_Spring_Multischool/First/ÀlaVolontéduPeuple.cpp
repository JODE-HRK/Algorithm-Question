#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 7;
int n, m, dis[maxn];
struct Edge
{
    int to, w;
};
vector<Edge> edge[maxn];
void dij()
{
    bool vis[maxn];
    for (auto i = 1; i <= n; i++)
        dis[i] = 0x7fffffff, vis[i] = 0;
    dis[1] = 0;
    queue<int> Q;
    Q.push(1);
    while (!Q.empty())
    {
        auto nownode = Q.front();
        Q.pop();
        vis[nownode] = 0;
        for (auto i = 0; i < edge[nownode].size(); i++)
        {
            auto tto = edge[nownode][i].to, ww = edge[nownode][i].w;
            if (dis[tto] > dis[nownode] + ww)
            {
                dis[tto] = dis[nownode] + ww;
                if (!vis[tto])
                    Q.push(tto), vis[tto] = 1;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); //这两段加速C++输入输出流
    cin >> n >> m;
    for (auto i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edge[a].push_back({b, c});
        if (a != b)
            edge[b].push_back({a, c});
    }
    dij();
    //cout << dis[n];
    int ans = 0;
    for (auto i = 1; i <= n; i++)
    {
        auto p = 0;
        for (auto j = 0; j < edge[i].size(); j++)
        {
            auto tto = edge[i][j].to, ww = edge[i][j].w;
            if (dis[tto] + ww == dis[i])
                p++;
            else if (i >= tto && dis[i] + ww > dis[tto] && dis[tto] + ww > dis[i])
                ans++;
        }
        if (p > 1)
            ans++;
    }
    cout << ans;
    return 0;
}