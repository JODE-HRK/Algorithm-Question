#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <vector>
#include <ctime>
using namespace std;
const int maxn = 1001;
int n, m;
int t[maxn], dis[maxn], w[maxn], vis[maxn];
struct Edge
{
    int to, w;
};
vector<Edge> e[maxn];
void dij()
{
    vis[1] = 1;
    dis[1] = 0;
    w[1] = t[1];
    queue<int> Q;
    Q.push(1);
    while (!Q.empty())
    {
        int now = Q.front();
        Q.pop();
        vis[now] = 0;
        for (int i = 0; i < e[now].size(); i++)
        {
            Edge v = e[now][i];
            int tto = v.to, ww = v.w;
            if (dis[tto] > dis[now] + ww)
            {
                dis[tto] = dis[now] + ww;
                w[tto] = w[now] + t[tto];
                if (!vis[tto])
                    Q.push(tto), vis[tto] = 1;
            }
            else if (dis[tto] == dis[now] + ww && w[tto] < w[now] + t[tto])
            {
                w[tto] = max(w[tto], w[now] + t[tto]);
                if (!vis[tto])
                    Q.push(tto), vis[tto] = 1;
            }
        }
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &t[i]), dis[i] = 100001, vis[i] = 0, w[i] = 0;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        int fr, to, ww;
        scanf("%d %d %d", &fr, &to, &ww);
        Edge x;
        x.to = to, x.w = ww;
        e[fr].push_back(x);
        x.to = fr, x.w = ww;
        e[to].push_back(x);
    }
    dij();
    if (dis[n] == 100001)
        cout << "impossible";
    else
        cout << dis[n] << ' ' << w[n];
    return 0;
}