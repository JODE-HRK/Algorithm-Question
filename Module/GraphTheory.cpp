#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 7;
/*
最近公共祖先
单次查询的时间复杂度为log n
*/
struct LCA
{
    int n, m, s;
    int head[maxn], tot, lg[maxn], fa[maxn][22], depth[maxn];
    struct Edge
    {
        int fr, to, w, nxt;
    } edge[maxn];
    void init()
    {
        tot = 0;
        fill(head, head + 1 + n, -1);
    }
    void addEdge(int fr, int to, int w)
    {
        edge[tot] = (Edge){fr, to, w, head[fr]};
        head[fr] = tot++;
    }
    void dfs(int now, int father)
    { //dfs建树
        fa[now][0] = father, depth[now] = depth[father] + 1;
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
        dfs(s, 0);
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
    void getLCA()
    {
        scanf("%d %d %d", &n, &m, &s); //点的数量，询问数量、源点数量
        init();
        for (int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            addEdge(u, v, 0);
            addEdge(v, u, 0);
        }
        pre();
        while (m--)
        {
            int u, v;
            scanf("%d %d", &u, &v); //查询两个点的最近公共祖先
            printf("%d\n", getans(u, v));
        }
    }
};
/*
边权为点权的异或，异或最小生成树
时间复杂度为 mlogn
*/
struct XOR_MST
{
    int n, a[maxn];
    int trie[maxn * 30][2], tot = 0;
    ll ans = 0;
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
    int main()
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        sort(a + 1, a + 1 + n);
        dfs(1, n, 29);
        printf("%lld", ans);
        return 0;
    }
};
/*
最大生成树 取 LCA路径上的最小值
*/
struct MAST_LCA_route_minnum
{
    int n, m, tot = 0;
    int head[maxn], fa[maxn], depth[maxn];
    int sfa[maxn][15], mn[maxn][15];
    struct EEdge //最大生成树 边的排列
    {
        int fr, to, w;
        bool operator<(const EEdge x) const
        {
            return w > x.w;
        }
    } sedge[maxn];
    struct Edge //LCA边
    {
        int fr, to, w, nxt;
    } edge[maxn];
    void addEdge(int u, int v, int w)
    {
        edge[tot] = (Edge){u, v, w, head[u]};
        head[u] = tot++;
    }
    int fdfa(int x) //并查集
    {
        return fa[x] == x ? x : fa[x] = fdfa(fa[x]);
    }
    void dfs(int now, int pa)
    {
        for (int i = head[now]; ~i; i = edge[i].nxt)
        {
            int to = edge[i].to, w = edge[i].w;
            if (to == pa)
                continue;
            depth[to] = depth[now] + 1;
            sfa[to][0] = now;
            mn[to][0] = w;
            dfs(to, now);
        }
    }
    int lca(int u, int v)
    {
        if (depth[u] == -1 || depth[v] == -1)
            return -1;
        if (depth[u] > depth[v])
            swap(u, v);
        for (int i = 0; i < 15; i++)
            if ((depth[v] - depth[u]) & (1 << i))
                v = sfa[v][i];
        if (u == v)
            return u;
        for (int i = 14; i >= 0; i--)
            if (sfa[u][i] != sfa[v][i])
                u = sfa[u][i], v = sfa[v][i];
        return sfa[u][0];
    }
    int ask(int u, int st)
    {
        int ret = 0x7fffffff;
        for (int i = 0; i < 15; i++)
            if (st & (1 << i))
                ret = min(ret, mn[u][i]), u = sfa[u][i];
        return ret;
    }
    int main()
    {
        scanf("%d %d", &n, &m);
        fill(head, head + 1 + n, -1);
        fill(depth, depth + 1 + n, -1);
        for (int i = 1; i <= n; i++)
            fa[i] = i;
        for (int i = 1; i <= m; i++)
            scanf("%d %d %d", &sedge[i].fr, &sedge[i].to, &sedge[i].w);
        sort(sedge + 1, sedge + 1 + m);
        int k = 0;
        for (int i = 1; i <= m; i++)
        {
            if (k == n - 1)
                break;
            if (fdfa(sedge[i].fr) != fdfa(sedge[i].to))
            {
                int u = sedge[i].fr, v = sedge[i].to, w = sedge[i].w;
                addEdge(u, v, w);
                addEdge(v, u, w);
                fa[fdfa(v)] = fdfa(u);
                k++;
            }
        } //循环建立最大生成树
        depth[1] = 1;
        dfs(1, 0);
        // printf("YES\n");
        for (int i = 1; i < 15; i++)
            for (int j = 1; j <= n; j++)
            {
                sfa[j][i] = sfa[sfa[j][i - 1]][i - 1];                  //记录路径父亲节点
                mn[j][i] = min(mn[j][i - 1], mn[sfa[j][i - 1]][i - 1]); //记录路径边权最小值
            }
        int q;
        scanf("%d", &q);
        while (q--)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            int ffa = lca(u, v); //找不到LCA返回-1
            if (ffa != -1)       //两边的路径上最小值，再取最小值
                printf("%d\n", min(ask(u, depth[u] - depth[ffa]), ask(v, depth[v] - depth[ffa])));
            else
                printf("-1\n");
        }
        return 0;
    }
};