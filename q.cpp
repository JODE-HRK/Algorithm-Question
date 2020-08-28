/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-18 23:21:16
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-08-28 09:40:03
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn = 2e5 + 7;
ll n, m, q;
ll f[maxn];
ll head[maxn], tot, cnt, ztot;
ll dfn[maxn], sz[maxn], dep[maxn], rdep[maxn], nsz[maxn], gef[maxn], siz;
ll seq[maxn], root[maxn];
ll fa[maxn][32];
ll lg;
struct Edge
{
    ll to, nxt;
} edge[maxn << 1];
struct Tree
{
    ll size, lnode, rnode;
} tree[32 * maxn];
void init()
{
    fill(head, head + 1 + n, -1);
    tot = cnt = siz = 0;
}
void addEdge(ll fr, ll to)
{
    edge[tot] = (Edge){to, head[fr]};
    head[fr] = tot++;
    edge[tot] = (Edge){fr, head[to]};
    head[to] = tot++;
}
void maintain(ll u)
{
    for (ll j = 1; j <= lg; j++)
        fa[u][j] = fa[fa[u][j - 1]][j - 1];
}
void dfs(ll now, ll father)
{
    nsz[now] = gef[now] = now;
    dfn[now] = ++cnt, seq[cnt] = now;
    f[now] = fa[now][0] = father, maintain(now);
    rdep[now] = dep[now] = dep[father] + 1, sz[now] = 1;
    for (ll i = head[now]; ~i; i = edge[i].nxt)
        if (edge[i].to != father)
        {
            ll v = edge[i].to;
            dfs(v, now);
            sz[now] += sz[v];
        }
}
void pushup(ll node)
{
    tree[node].size = tree[tree[node].lnode].size + tree[tree[node].rnode].size;
}
ll update(ll l, ll r, ll node, ll pos) //主席树的插入
{
    ll newnode = ++siz;
    tree[newnode] = tree[node];
    if (l == r)
    {
        tree[newnode].size++;
        return newnode;
    }
    ll mid = (l + r) >> 1;
    if (pos <= mid)
        tree[newnode].lnode = update(l, mid, tree[node].lnode, pos);
    else
        tree[newnode].rnode = update(mid + 1, r, tree[node].rnode, pos);
    pushup(newnode);
    return newnode;
}
ll bel(ll id)
{
    ll l = 1, r = ztot;
    while (r - l > 1)
    {
        ll mid = (l + r) >> 1;
        if (id <= nsz[mid])
            r = mid;
        else
            l = mid + 1;
    }
    if (id <= nsz[l])
        return l;
    return r;
} //查询id在大树上面的结点编号
ll Kth(ll u, ll v, ll l, ll r, ll k) //通过第k大来查询节点编号
{
    if (l == r)
        return l;
    ll mid = (l + r) >> 1, sum = tree[tree[v].lnode].size - tree[tree[u].lnode].size;
    if (k <= sum)
        return Kth(tree[u].lnode, tree[v].lnode, l, mid, k);
    else
        return Kth(tree[u].rnode, tree[v].rnode, mid + 1, r, k - sum);
}
ll getRef(ll now) //直接查询节点在小树的编号
{
    if (now <= n)
        return now;
    ll com = bel(now), fr = gef[com];                                                    //gef数组记录的是每一个大树节点内的根节点
    return Kth(root[dfn[fr] - 1], root[dfn[fr] + sz[fr] - 1], 1, n, now - nsz[com - 1]); //区间第k大
}
void balance(ll &u, ll step)
{
    for (ll i = 0; (i << i) <= step; i++)
        if (step & (1 << i))
            u = fa[u][i];
}
ll LCA(ll u, ll v)
{
    if (dep[u] > dep[v])
        balance(u, dep[u] - dep[v]);
    if (dep[v] > dep[u])
        balance(v, dep[v] - dep[u]);
    if (u == v)
        return u;
    for (ll i = lg; i >= 0; i--)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
ll query(ll u, ll l, ll r, ll segL, ll segR)
{
    if (!u)
        return 0;
    if (segL <= l && r <= segR)
    {
        return tree[u].size;
    }
    ll mid = (l + r) >> 1, ret = 0;
    if (mid >= segL)
        ret += query(tree[u].lnode, l, mid, segL, segR);
    if (mid < segR)
        ret += query(tree[u].rnode, mid + 1, r, segL, segR);
    return ret;
}
ll getDep(ll u)
{
    ll com = bel(u), tru = getRef(u);              //获得大树节点和小数节点
    return rdep[com] + rdep[tru] - rdep[gef[com]]; //大树节点的深度+（小数上面的深度 - 小数所属的大树节点的根节点深度）
}
ll getDis(ll fr, ll to)
{
    ll u = bel(fr), v = bel(to), ff, tt; //先分别取得在大树上的编号
    if (u == v)                          //如果在同一个大树节点上
    {
        ff = fr, tt = to; //要查询的就不变
    }
    else //否则需要做一些处理
    {
        if (dep[u] > dep[v])
            balance(u, dep[u] - dep[v]);
        if (dep[v] > dep[u])
            balance(v, dep[v] - dep[u]); //大树节点的平衡
        if (u == v)
        {
            u = bel(fr), v = bel(to);
            if (dep[u] > dep[v])
                balance(u, dep[u] - dep[v] - 1), ff = f[u], tt = to;
            if (dep[v] > dep[u])
                balance(v, dep[v] - dep[u] - 1), ff = fr, tt = f[v];
        }
        else
        {
            for (ll i = lg; i >= 0; i--)
                if (fa[u][i] != fa[v][i])
                    u = fa[u][i], v = fa[v][i];
            ff = f[u], tt = f[v];
        }
    }
    ll lca = LCA(getRef(ff), getRef(tt)), in = bel(ff); //先求出大树节点的lca
    lca = in <= n ? lca : query(root[dfn[gef[in]] + sz[gef[in]] - 1], 1, n, 1, lca) - query(root[dfn[gef[in]] - 1], 1, n, 1, lca) + nsz[in - 1];
    return getDep(fr) + getDep(to) - 2 * getDep(lca);
}
int main()
{
    scanf("%lld %lld %lld", &n, &m, &q);
    lg = log2(n), ztot = n;
    init();
    for (ll i = 1; i < n; i++)
    {
        ll u, v;
        scanf("%lld %lld", &u, &v);
        addEdge(u, v);
    }
    dfs(1, 0); //dfs将原来的树建立起来，并获取一些参数
    for (ll i = 1; i <= n; i++)
        root[i] = update(1, n, root[i - 1], seq[i]); //按照dfs序来建立主席树
    // prllf("YES\n");
    for (ll i = 1; i <= m; i++)
    {
        ll a, b;
        scanf("%lld %lld", &a, &b);
        gef[++ztot] = a, f[ztot] = b;
        nsz[ztot] = nsz[ztot - 1] + sz[a];
        ll com = bel(b);
        rdep[ztot] = rdep[com] + rdep[getRef(b)] - rdep[gef[com]] + 1;
        dep[ztot] = dep[com] + 1;
        fa[ztot][0] = com, maintain(ztot);
    }
    for (ll i = 1; i <= q; i++)
    {
        ll a, b;
        scanf("%lld %lld", &a, &b);
        printf("%lld\n", getDis(a, b));
    }
    return 0;
}
/*
6 2 1
1 2
1 3
2 4
2 5
3 6
2 3
4 6
4 9
*/