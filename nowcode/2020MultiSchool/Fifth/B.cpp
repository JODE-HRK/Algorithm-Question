/*
XOR-MST
异或最小生成树
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 7;
int n, a[maxn];
int trie[maxn * 30][2], tot = 0, cnt = 0;
int head[maxn];
ll ans = 0;
struct Edge
{
    int fr, to, w, nxt;
} edge[maxn];
void add(int fr, int to, int w)
{
    edge[cnt] = (Edge){fr, to, w, head[fr]};
    head[fr] = cnt++;
}
void Insert(int x)
{
    int root = 0;
    for (int i = 29; i >= 0; i--)
    {
        int now = (x >> i) & 1;
        if (!trie[root][now])
            trie[root][now] = ++tot;
        root = trie[root][now];
    }
}
int Search(int x)
{
    int tans = 0, root = 0;
    for (int i = 29; i >= 0; i--)
    {
        int now = (x >> i) & 1;
        if (trie[root][now])
            root = trie[root][now];
        else
            root = trie[root][now ^ 1], tans |= (1 << i);
    }
    return tans;
}
void dfs(int l, int r, int depth)
{
    if (depth == -1 || l >= r)
        return;
    int mid = l - 1;
    while (mid < r && ((a[mid + 1] >> depth) & 1) == 0)
        mid++;
    dfs(l, mid, depth - 1);
    dfs(mid + 1, r, depth - 1);
    if (mid == l - 1 || mid == r)
        return;
    for (int i = l; i <= mid; i++)
        Insert(a[i]);
    int tmp = INT32_MAX;
    for (int i = mid + 1; i <= r; i++)
        tmp = min(tmp, Search(a[i]));
    ans += 1ll * tmp;
    for (int i = 0; i <= tot; i++)
        trie[i][0] = trie[i][1] = 0;
    tot = 0;
}
void build(int now, int fa)
{
    for (int i = head[now]; ~i; i = edge[i].nxt)
    {
        int to = edge[i].to, w = edge[i].w;
        if (to == fa)
            continue;
        a[to] = (w ^ a[now]);
        build(to, now);
    }
}
int main()
{
    scanf("%d", &n);
    fill(head, head + 1 + n, -1);
    for (int i = 1; i < n; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add(u + 1, v + 1, w);
        add(v + 1, u + 1, w);
    }
    a[1] = 0;
    // cout << "yes" << endl;
    build(1, 0);
    sort(a + 1, a + 1 + n);
    dfs(1, n, 29);
    printf("%lld", ans);
    return 0;
}