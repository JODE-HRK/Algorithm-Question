#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int n, a[maxn], answer = 0, fa[maxn], son[maxn], sze[maxn];
vector<int> g[maxn];
void dfs1(int x, int pre)
{
    fa[x] = pre;
    sze[x] = 1;
    son[x] = 0;
    for (auto v : g[x])
        if (v != fa[x])
        {
            dfs1(v, x);
            sze[x] += sze[v];
            if (!son[x] || sze[son[x]] < sze[v])
                son[x] = v; //son[x]记录容量最大的儿子
        }
}
int pc = 1, ch[maxn * 40][2];
void clear()
{
    pc = 1, ch[1][0] = ch[1][1] = 0;
}
void insert(int x)
{
    int cur = 1;
    for (int i = 29; ~i; i--)
    {
        if (!ch[cur][x >> i & 1])
        {
            ch[cur][x >> i & 1] = ++pc;
            ch[pc][0] = ch[pc][1] = 0;
        }
        cur = ch[cur][x >> i & 1];
    }
}
int ask(int x)
{
    if (pc == 1)
        return x;
    int ans = 0, cur = 1;
    for (int i = 29; ~i; i--)
        if (ch[cur][!(x >> i & 1)])
        {
            ans |= 1 << i;
            cur = ch[cur][!(x >> i & 1)];
        }
        else
            cur = ch[cur][x >> i & 1];
    return ans;
}
void dfs3(int x, int cur)
{
    answer = max(answer, ask(cur));
    for (auto v : g[x])
        if (v != fa[x])
            dfs3(v, cur ^ a[v]);
}
void dfs4(int x, int cur)
{
    insert(cur);
    for (auto v : g[x])
        if (v != fa[x])
            dfs4(v, cur ^ a[v]);
}
void dfs2(int x, int cur, bool keep)
{
    answer = max(answer, cur);
    for (auto v : g[x])
        if (v != fa[x] && v != son[x])
            dfs2(v, cur ^ a[v], false);
    if (son[x])
        dfs2(son[x], cur ^ a[son[x]], true);
    else
        clear();
    for (auto v : g[x])
        if (v != fa[x] && v != son[x])
            dfs3(v, a[v]), dfs4(v, cur ^ a[v]);
    if (keep)
        insert(cur);
    else
        clear();
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1, u, v; i < n; i++)
    {
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, a[1], false);
    printf("%d", answer);
    return 0;
}