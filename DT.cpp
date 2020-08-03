#pragma GCC optimize(2)
#include <iostream>
#define pii pair<int, int>
#define ll long long
using namespace std;
const int maxn = 1e6 + 7;
int n, m, tot;
int head[maxn], depth[maxn], lg[maxn], fa[maxn][32], mxlen;
int u[maxn], v[maxn]; //每条路径的两个端点
int tofa[maxn];       //记录从每个点到其父亲节点的经过次数
int dis[maxn];        //记录当前节点到根节点的距离
int Lca[maxn];        //记录每条路径的lca
int sum[maxn];        //记录每条路径的长度
int cnt[maxn];        //记录每条路径经过的次数
int tofaEdge[maxn];   //记录到父亲节点的边的编号
int pos, ttot;        //pos记录最长边的编号，ttot记录当前有多少条边大于此刻的二分答案
struct Edge
{
    int fr, to, w, nxt;
} edge[maxn];
inline void init()
{
    dis[0] = dis[1] = 0;
    tot = 0;
    fill(head, head + 1 + n, -1);
}
inline void addEdge(int fr, int to, int w)
{
    edge[tot] = (Edge){fr, to, w, head[fr]};
    head[fr] = tot++;
}
void dfs(int now, int father)
{ //dfs建树
    fa[now][0] = father, depth[now] = depth[father] + 1;
    for (register int i = 1; (1 << i) <= depth[now]; i++)
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    for (register int i = head[now]; ~i; i = edge[i].nxt)
        if (edge[i].to != father)
        {
            dis[edge[i].to] = dis[now] + edge[i].w;
            dfs(edge[i].to, now);
            tofaEdge[edge[i].to] = i;
        }
}
void pre()
{
    for (register int i = 1; i <= n; i++)
        lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
    depth[0] = 0;
    dfs(1, 0);
}
inline int getLCA(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);
    while (depth[u] > depth[v])
        u = fa[u][lg[depth[u] - depth[v]] - 1];
    if (u == v)
        return u;
    for (register int k = lg[depth[u]] - 1; k >= 0; k--)
        if (fa[u][k] != fa[v][k])
            u = fa[u][k], v = fa[v][k];
    return fa[u][0];
}
void dfs2(int now)
{
    for (register int i = head[now]; ~i; i = edge[i].nxt)
        if (edge[i].to != fa[now][0])
        {
            dfs2(edge[i].to);
            cnt[now] += cnt[edge[i].to];
        }
    if (pos == -1 || (cnt[now] == ttot && edge[tofaEdge[now]].w > edge[pos].w))
        pos = tofaEdge[now]; //当找到经过次数为边的条数且当前路径比已经找到的路径最大
}
inline bool check(int tans)
{
    ttot = 0;
    pos = tot;
    edge[tot].w = 0;
    fill(cnt, cnt + 1 + n, 0);
    for (register int i = 1; i <= m; i++)
    {
        if (sum[i] <= tans)
            continue;
        cnt[u[i]]++, cnt[v[i]]++;
        cnt[Lca[i]] -= 2; //不同于点差分
        ttot++;
    }
    dfs2(1);
    // if (pos == -1)
    //     return 0;
    return mxlen - edge[pos].w <= tans;
}
inline int read()
{
    char c = getchar();
    int x = 0, fh = 0;
    while (c < '0' || c > '9')
    {
        fh |= c == '-';
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return fh ? -x : x;
}
int main()
{
    n = read(), m = read();
    init();
    for (register int i = 1; i < n; i++)
    {
        int uu, vv, w;
        uu = read(), vv = read(), w = read();
        addEdge(uu, vv, w);
        addEdge(vv, uu, w);
    }
    pre();
    int l = 0, r = INT32_MIN;
    for (register int i = 1; i <= m; i++)
    {
        u[i] = read(), v[i] = read();
        Lca[i] = getLCA(u[i], v[i]);
        sum[i] = dis[u[i]] + dis[v[i]] - (dis[Lca[i]] << 1);
        r = max(r, sum[i]);
    }
    mxlen = r;
    int ans;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        // cout << mid << endl;
        check(mid) ? ans = mid, r = mid - 1 : l = mid + 1;
    }
    printf("%d", ans);
    return 0;
}