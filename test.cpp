#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5e5 + 7;
int n;
ll m;
int head[maxn], tot = 0;
ll cnt = 0;
ll dis[maxn];
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
void dfs(int now, int fa)
{
	for (ll i = head[now]; ~i; i = edge[i].nxt)
		if (edge[i].to != fa)
		{
			dis[edge[i].to] = dis[now] + edge[i].w;
			dfs(edge[i].to, now);
		}
	if (maxdis < dis[now])
		maxdis = max(maxdis, dis[now]), node = now, cnt = 0;
	else if (maxdis == dis[now])
		cnt++;
}
int main()
{
	scanf("%d %lld", &n, &m);
	fill(head, head + 1 + n, -1);
	fill(dis, dis + 1 + n, INT64_MIN);
	ll sum = 0;
	for (int i = 1; i < n; i++)
	{
		ll u, v, w;
		scanf("%lld %lld %lld", &u, &v, &w);
		sum += 2 * w;
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	dis[1] = 0;
	dfs(1, 0);
	fill(dis, dis + 1 + n, INT64_MIN);
	dis[node] = 0;
	dfs(node, 0);
	printf("%lld", sum / m);
	return 0;
}