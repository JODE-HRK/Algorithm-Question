#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5e5 + 7;
ll n;
int head[maxn], tot = 0;
ll dis[maxn][2], sum = 0, m;
ll ddis[maxn];
struct Edge
{
    ll to, w, nxt;
} edge[maxn << 2];
ll maxdis, node;
void addEdge(ll fr, ll to, ll w)
{
    edge[tot] = (Edge){to, w, head[fr]};
    head[fr] = tot++;
}
void dfs(int now, int fa, int p)
{
    for (ll i = head[now]; ~i; i = edge[i].nxt)
        if (edge[i].to != fa)
        {
            dis[edge[i].to][p] = dis[now][p] + edge[i].w;
            dfs(edge[i].to, now, p);
        }
    if (maxdis < dis[now][p])
        maxdis = max(maxdis, dis[now][p]), node = now;
}
int main()
{
    scanf("%d %lld", &n, &m);
    fill(head, head + 1 + n, -1);
    for (int i = 1; i < n; i++)
    {
        ll u, v, w;
        scanf("%lld %lld %lld", &u, &v, &w);
        sum += 2 * w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    maxdis = dis[1][0] = dis[1][1] = 0;
    dfs(1, 0, 0);
    // printf("%d\n", node);
    // printf("%lld\n", maxdis);
    maxdis = dis[node][0] = 0;
    dfs(node, 0, 0);
    // printf("%d\n", node);
    maxdis = dis[node][1] = 0;
    dfs(node, 0, 1);
    // for (int i = 1; i <= n; i++)
    // {
    //     printf("%lld %lld\n", dis[i][0], dis[i][1]);
    // }
    // printf("SUM:%lld\n", sum);
    for (int i = 1; i <= n; i++)
        ddis[i] = sum - max(dis[i][0], dis[i][1]);
    sort(ddis + 1, ddis + 1 + n);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (m >= ddis[i])
        {
            ans++;
            m -= ddis[i];
        }
        else
            break;
    }
    printf("%d\n", ans);
    return 0;
}