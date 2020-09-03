/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-09-02 21:41:35
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-09-03 09:43:01
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
int n, m, q, cntnode = n;
int b[maxn], h[maxn], fa[maxn], val[maxn], sz[maxn], dfn[maxn], tot = 0;
int root[maxn], cnt = 0, dep[maxn];
int f[maxn][32], num;
vector<int> G[maxn];
struct Edge
{
    int fr, to, w;
    bool operator<(const Edge &x) const
    {
        return w < x.w;
    }
} edge[maxn];
struct Tree
{
    int l, r, s;
} tree[maxn * 32];
int getfa(int x)
{
    return x == fa[x] ? x : fa[x] = getfa(fa[x]);
}
int insert(int x, int l, int r, int node)
{
    int newnode = ++cnt;
    tree[newnode] = tree[node];
    if (x == 0)
        return newnode;
    if (l == r)
    {
        tree[newnode].s++;
        return newnode;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        tree[newnode].l = insert(x, l, mid, tree[node].l);
    else
        tree[newnode].r = insert(x, mid + 1, r, tree[node].r);
    tree[newnode].s = tree[tree[newnode].l].s + tree[tree[newnode].r].s;
    return newnode;
}
int build(int l, int r)
{
    int newnode = ++cnt;
    tree[newnode].s = 0;
    if (l == r)
        return newnode;
    int mid = (l + r) >> 1;
    tree[newnode].l = build(l, mid);
    tree[newnode].r = build(mid + 1, r);
    return newnode;
}
void dfs(int now, int father)
{
    dep[now] = dep[father] + 1;
    fa[now] = father;
    f[now][0] = father;
    sz[now] = 1;
    dfn[now] = ++tot;
    for (int i = 1; (1 << i) <= dep[now]; i++)
        f[now][i] = f[f[now][i - 1]][i - 1];
    root[tot] = insert(h[now], 1, num, root[tot - 1]);
    int l = G[now].size();
    for (int i = 0; i < l; i++)
    {
        int to = G[now][i];
        if (to == father)
            continue;
        dfs(to, now);
        sz[now] += sz[to];
    }
}
int main()
{
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &h[i]), b[i] = h[i], fa[i] = i, val[i] = 0;
    sort(b + 1, b + 1 + n);
    num = unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 1; i <= n; i++)
        h[i] = lower_bound(b + 1, b + 1 + n, h[i]) - b;
    for (int i = 1; i <= m; i++)
        scanf("%d %d %d", &edge[i].fr, &edge[i].to, &edge[i].w);
    sort(edge + 1, edge + 1 + m);
    int cnt = 0;
    for (int i = 1; i <= m; i++)
    {
        int fr = getfa(edge[i].fr), to = getfa(edge[i].to);
        if (fr != to)
        {
            fa[getfa(fr)] = fa[getfa(to)] = ++cntnode;
            val[cntnode] = edge[i].w;
            G[fr].push_back(cntnode);
            G[to].push_back(cntnode);
            G[cntnode].push_back(fr);
            G[cntnode].push_back(to);
            cnt++;
        }
        if (cnt == n - 1)
            break;
    }
    root[0] = build(1, num);
    dep[0] = 0;
    dfs(cntnode, 0);

    for (int i = 1; i <= q; i++)
    {
        int v, x, k;
        scanf("%d %d %d", &v, &x, &k);
        for (int j = 20; j >= 0; j--)
            if (f[v][j] && val[f[v][j]] <= x)
                v = f[v][j]; //找到深度最小且点权不大于k的祖先
        if (sz[v] / 2 < k)
        {
            printf("-1\n");
            continue;
        }
        printf("%d\n", query());
    }
    return 0;
}