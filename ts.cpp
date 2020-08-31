#include <bits/stdc++.h>
#define ll long long
using namespace std;
<<<<<<< HEAD
const int maxn = 3e5 + 7;
int n, k;
int mp[maxn], sz[maxn], anc[maxn], sum, rt;
int node_len, edge_len;
int cnt_node[maxn], cnt_edge[maxn], del[maxn], dep[maxn];
int allcount[maxn];
bool vis[maxn];
vector<int> G[maxn];
struct Edge
{
    int to, nxt;
};
void init()
{
    for (int i = 1; i <= n; i++)
        G[i].clear(), vis[i] = 0, del[i] = 0, cnt_edge[i] = 0, cnt_node[i] = 0, allcount[i] = 0;
}
void addEdge(int u, int v)
{
    G[u].push_back(v);
}
void getrt(int now, int f)
{
    anc[now] = f;
    sz[now] = 1;
    mp[now] = 0; //siz数组数组树子树大小
    int l = G[now].size();
    for (int i = 0; i < l; i++)
    {
        int v = G[now][i];
        if (v == f || vis[v])
            continue;
        getrt(v, now);
        sz[now] += sz[v];
        if (sz[v] > mp[now])
            mp[now] = sz[v]; //mp数组是去掉u节点后，剩余部分的最大一部分。
    }
    mp[now] = max(mp[now], sum - sz[now]); //不要忘记上子树
    if (mp[now] < mp[rt])
        rt = now; //换根
}
void travel(int now)
{
    int O[maxn];
    int l = 0, r = -1, max_depmp[rt];
    O[++r] = now;
    while (l <= r)
    {
        int u = O[l++];
        allcount[dep[u]]++;
    }
}
void get(int now)
{
    del[now] = 1, dep[now] = 0;
    mp[now] = 0;
    travel(rt);
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &n, &k);
        node_len = k / 2;
        edge_len = (k - 1) / 2;
        init();
        for (int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        mp[0] = 0, sum = n;
        getrt(1, 0);
        getrt(rt, 0); //重新计算
        get(rt);
        int ans = n;
        for (int i = 1; i <= n; i++)
            ans = min(ans, cnt_node[i]);
        for (int i = 1; i < n; i++)
            ans = min(ans, cnt_edge[i]);
=======
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
>>>>>>> 8bac59c33f0fb0ec1bbd686f9b8446d6abcbf7e8
    }
    return 0;
}