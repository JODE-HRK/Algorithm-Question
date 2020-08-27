#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5e5 + 7;
int n;
int head[maxn], tot = 0;
ll dis[maxn];
struct Edge
{
    ll to, w, nxt;
} edge[maxn << 2];
ll maxdis, node;
ll ans = INT64_MIN;
void addEdge(ll fr, ll to, ll w)
{
    edge[tot] = (Edge){to, w, head[fr]};
    head[fr] = tot++;
}
void dfs(int now, int fa)
{
    ll dis1 = INT64_MIN, dis2 = INT64_MIN;
    for (ll i = head[now]; ~i; i = edge[i].nxt)
        if (edge[i].to != fa)
        {
            dfs(edge[i].to, now);
            ll d = dis[edge[i].to] + edge[i].w;
            if (dis1 <= d)
            {
                dis2 = dis1;
                dis1 = d;
            }
            else
                dis2 = max(dis2, d);
            dis[now] = max(dis[now], dis[edge[i].to] + edge[i].w);
        }
    ans = max(ans, dis1 + dis2);
}
int main()
{
    scanf("%d", &n);
    fill(head, head + 1 + n, -1);
    for (int i = 1; i < n; i++)
    {
        ll u, v, w;
        scanf("%lld %lld %lld", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    dis[1] = 0;
    dfs(1, 0);
    printf("%lld\n", ans);
    return 0;
}