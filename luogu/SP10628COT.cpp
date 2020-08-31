/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-27 12:40:47
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-08-30 10:56:00
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int n, m, u, v, k;
struct Tree
{
    int l, r, s;
} tree[maxn << 5];
vector<int> G[maxn];
int a[maxn], b[maxn];
int head[maxn], tot, lg[maxn], fa[maxn][22], depth[maxn], cnt, root[maxn], num;
struct Edge
{
    int fr, to, w, nxt;
} edge[maxn << 1];
void init()
{
    tot = cnt = 0;
    fill(head, head + 1 + n, -1);
}
void addEdge(int fr, int to, int w)
{
    edge[tot] = (Edge){fr, to, w, head[fr]};
    head[fr] = tot++;
}
int insert(int l, int r, int node, int val)
{
    int newnode = ++cnt;
    tree[newnode] = tree[node];
    tree[newnode].s++;
    if (l == r)
        return newnode;
    int mid = (l + r) >> 1;
    if (val <= mid)
        tree[newnode].l = insert(l, mid, tree[node].l, val);
    else
        tree[newnode].r = insert(mid + 1, r, tree[node].r, val);
    return newnode;
}
void dfs(int now, int father)
{ //dfs建树
    fa[now][0] = father, depth[now] = depth[father] + 1;
    // printf("REWS\n");
    root[now] = insert(1, num, root[fa[now][0]], a[now]);
    for (int i = 1; (1 << i) <= depth[now]; i++)
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    for (int i = head[now]; ~i; i = edge[i].nxt)
        if (edge[i].to != father)
            dfs(edge[i].to, now);
}
void pre()
{
    for (int i = 1; i <= n; i++)
        lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
    depth[0] = 0;
    dfs(1, 0);
}
int getans(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);
    while (depth[u] > depth[v])
        u = fa[u][lg[depth[u] - depth[v]] - 1];
    if (u == v)
        return u;
    for (int k = lg[depth[u]] - 1; k >= 0; k--)
        if (fa[u][k] != fa[v][k])
            u = fa[u][k], v = fa[v][k];
    return fa[u][0];
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
int fd(int l, int r, int node1, int node2, int node3, int node4, int nk)
{
    if (l == r)
        return l;
    int sum = tree[tree[node1].l].s + tree[tree[node2].l].s - tree[tree[node3].l].s - tree[tree[node4].l].s;
    int mid = (l + r) >> 1;
    if (sum >= nk)
        return fd(l, mid, tree[node1].l, tree[node2].l, tree[node3].l, tree[node4].l, nk);
    else
        return fd(mid + 1, r, tree[node1].r, tree[node2].r, tree[node3].r, tree[node4].r, nk - sum);
}
int main()
{
    scanf("%d %d", &n, &m);
    init();
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), b[i] = a[i];
    sort(b + 1, b + 1 + n);
    num = unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 1; i <= n; ++i)
        a[i] = lower_bound(b + 1, b + 1 + num, a[i]) - b;
    for (int i = 1; i < n; i++)
    {
        scanf("%d %d", &u, &v);
        addEdge(u, v, 1);
        addEdge(v, u, 1);
    }
    root[0] = build(1, num);
    pre();
    for (int i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &u, &v, &k);
        int lca = getans(u, v);
        printf("%d\n", b[fd(1, num, root[u], root[v], root[lca], root[fa[lca][0]], k)]);
    }
    return 0;
}