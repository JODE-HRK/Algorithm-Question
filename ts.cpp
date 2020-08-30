#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn = 2e5 + 7;
ll n, s, m;
ll a[maxn], dep[maxn], dfn[maxn], cnt = 0, sz[maxn], b[maxn], num, tot = 0;
ll maxdep = 0, root[maxn];
bool vis[maxn];
vector<ll> G[maxn];
struct Tree
{
    ll l, r, minn;
} tree[maxn * 32];
void dfs(ll now, ll fa)
{
    sz[now] = 1;
    dep[now] = dep[fa] + 1;
    // D[dep[now]].push_back(now);
    maxdep = max(maxdep, dep[now]);
    dfn[now] = ++cnt;
    ll l = G[now].size();
    for (ll i = 0; i < l; i++)
    {
        ll to = G[now][i];
        if (to == fa)
            continue;
        dfs(to, now);
        sz[now] += sz[to];
    }
}
void pushup(ll node)
{
    tree[node].minn = min(tree[tree[node].l].minn, tree[tree[node].r].minn);
}
ll insert(ll x, ll val, ll node, ll l, ll r)
{
    // prllf("%d %d %d %d %d\n", x, val, node, l, r);
    ll newnode = ++tot;
    tree[newnode] = tree[node];
    if (l == r)
    {
        // prllf("L:%d\n", l);
        tree[newnode].minn = val;
        return newnode;
    }
    ll mid = (l + r) >> 1;
    // prllf("MID:%d\n", mid);
    if (x <= mid)
        tree[newnode].l = insert(x, val, tree[node].l, l, mid);
    else
        tree[newnode].r = insert(x, val, tree[node].r, mid + 1, r);
    pushup(node);
    return newnode;
}
void bfs()
{
    fill(vis, vis + 1 + n, 0);
    queue<ll> Q;
    Q.push(s);
    ll depth_now = 0;
    while (!Q.empty())
    {
        ll now = Q.front();
        vis[now] = 1;
        Q.pop();
        ll tmp = depth_now;
        if (dep[now] != depth_now)
            depth_now = dep[now], tmp = depth_now - 1;
        // prllf("Now:%d\n", tmp);
        root[depth_now] = insert(dfn[now], a[now], root[tmp], 1, n);
        ll l = G[now].size();
        for (ll i = 0; i < l; i++)
        {
            ll to = G[now][i];
            if (vis[to])
                continue;
            Q.push(to);
        }
    }
}
ll build(ll l, ll r)
{
    ll newnode = ++tot;
    tree[newnode].minn = 1e9 + 7;
    if (l == r)
        return newnode;
    ll mid = (l + r) >> 1;
    tree[newnode].l = build(l, mid);
    tree[newnode].r = build(mid + 1, r);
    return newnode;
}
ll query(ll L, ll R, ll node, ll l, ll r)
{
    if (L <= l && r <= R)
        return tree[node].minn;
    ll ans = 1e9 + 7;
    ll mid = (l + r) >> 1;
    if (L <= mid)
        ans = min(ans, query(L, R, tree[node].l, l, mid));
    if (mid < R)
        ans = min(ans, query(L, R, tree[node].r, mid + 1, r));
    return ans;
}
int main()
{
    scanf("%lld %lld", &n, &s);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for (ll i = 1; i < n; i++)
    {
        ll u, v;
        scanf("%lld %lld", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    root[0] = build(1, n);
    // prllf("ROOT:%d\n", root[0]);
    dep[0] = 0;
    dfs(s, 0);
    bfs();
    scanf("%lld", &m);
    ll lastans = 0;
    for (ll i = 1; i <= m; i++)
    {
        ll x, k;
        scanf("%lld %lld", &x, &k);
        x = (x + lastans) % n + 1, k = (k + lastans) % n;
        printf("X:%lld K:%lld\n", x, k);
        ll tmp = min(dep[x] + k, maxdep);
        lastans = query(dfn[x], dfn[x] + sz[x] - 1, root[tmp], 1, n);
        printf("%lld\n", lastans);
    }
    return 0;
}