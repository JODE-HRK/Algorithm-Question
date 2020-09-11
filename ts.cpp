<<<<<<< HEAD
/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-31 20:40:32
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-09-11 10:47:43
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 7;
int n, m, k, st, en;
struct Edge
{
    int to, nxt;
    ll flow;
} edge[maxn << 1];
int head[maxn], tot = 0;
int u[maxn], v[maxn], cost[maxn], f[maxn];
int dis[maxn], cur[maxn];
ll ansflow, anscost;
void addEdge(int fr, int to, ll fl)
{
    edge[tot].to = to, edge[tot].flow = fl, edge[tot].nxt = head[fr];
    head[fr] = tot++;
}
void init()
{
    for (int i = 0; i <= tot; i++)
        cur[i] = head[i];
}
bool bfs()
{
    fill(dis, dis + 1 + 2 * n, -1);
    queue<int> Q;
    while (!Q.empty())
        Q.pop();
    Q.push(st);
    dis[st] = 0;
    while (!Q.empty())
    {
        int now = Q.front();
        Q.pop();
        for (int i = head[now]; ~i; i = edge[i].nxt)
        {
            int v = edge[i].to;
            if (edge[i].flow && dis[v] == -1)
            {
                dis[v] = dis[now] + 1;
                if (v == en)
                    return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}
ll dfs(int s, ll flow)
{
    if (s == en)
        return flow;
    ll _flow = 0, __flow;
    for (int i = cur[s]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (dis[v] == dis[s] + 1 && edge[i].flow)
        {
            __flow = dfs(v, min(flow, edge[i].flow));
            flow -= __flow;
            edge[i].flow -= __flow;
            _flow += __flow;
            edge[i ^ 1].flow += __flow;
            if (!flow)
                break;
        }
    }
    if (!_flow)
        dis[s] = -1;
    return _flow;
}
ll Dinic()
{
    ll ans = 0;
    while (bfs())
    { //bfs构建层次网络 判断是否存在一条到en的点
        // printf("YES\n");
        init();
        ans += dfs(st, 0x7fffffff); //一次dfs完成所有增广
    }
    return ans;
}
struct E
{
    int to, w;
};
vector<E> G[maxn], NG[maxn];
int D[maxn];
bool vis[maxn];
void dij()
{
    fill(D, D + 1 + n, 0x7fffffff);
    fill(vis, vis + 1 + n, 0);
    queue<int> Q;
    Q.push(1);
    D[1] = 0;
    while (!Q.empty())
    {
        int x = Q.front();
        Q.pop();
        if (x == n)
            continue;
        vis[x] = 0;
        int l = G[x].size();
        for (int i = 0; i < l; i++)
        {
            E tp = G[x][i];
            int to = tp.to, ww = tp.w;
            if (D[to] >= D[x] + ww)
            {
                if (D[to] > D[x] + ww)
                    NG[to].clear();
                NG[to].push_back((E){x, ww});
                D[to] = D[x] + ww;
                if (!vis[to])
                    Q.push(to), vis[to] = 1;
            }
        }
    }
}
int main()
{
    scanf("%d %d", &n, &m);
    fill(head, head + 1 + 2 * n, -1);
    for (int i = 1; i <= m; i++)
    {
        int fr, to, w;
        scanf("%d %d %d", &fr, &to, &w);
        G[fr].push_back((E){to, w});
        G[to].push_back((E){fr, w});
    }
    dij();
    // printf("%d\n", D[n]);
    int x;
    scanf("%d", &x);
    for (int i = 2; i < n; i++)
    {
        scanf("%d", &x);
        addEdge(i, n + i, x);
        addEdge(n + i, i, 0);
    }
    scanf("%d", &x);
    int l = NG[n].size();
    for (int i = 0; i < l; i++)
    {
        int to = NG[n][i].to;
        addEdge(n, to, 0x7fffffff);
        addEdge(to, n, 0);
    }
    for (int i = 2; i < n; i++)
    {
        l = NG[i].size();
        for (int j = 0; j < l; j++)
        {
            int to = NG[i][j].to;
            addEdge(i + n, to, 0x7fffffff);
            addEdge(to, i + n, 0);
        }
=======
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <tr1/unordered_map>
#include <cmath>

using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 4e5 + 5;

int gc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)) ? EOF : *p1++;
    //return getchar();
}

int geti()
{
    char ch = gc();
    int f = 1, x = 0;
    while (ch < '0' || ch > '9')
        f = (ch == '-' ? -1 : 1), ch = gc();
    while (ch >= '0' && ch <= '9')
        x = x * 10 + ch - '0', ch = gc();
    return f * x;
}

void wri(int x)
{
    if (x > 9)
        wri(x / 10);
    putchar(x % 10 + '0');
}

int n, m, N;
int a[MAXN];
int b[MAXN];
tr1::unordered_map<int, int> ref;

struct Query
{
    int l, r, id;
};

Query qs[MAXN];
int ans[MAXN];
int min1[MAXN], min2[MAXN], max1[MAXN], max2[MAXN], min3[MAXN], max3[MAXN];
int res1, res2, res3;
int block, blo[MAXN];

int Comp(Query a, Query b)
{
    if (blo[a.l] != blo[b.l])
        return a.l < b.l;
    return a.r < b.r;
}

void Prework()
{
    for (int i = 1; i <= n; i++)
        b[i] = a[i];
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++)
    {
        if (!ref[b[i]])
            ref[b[i]] = ++N;
    }
    for (int i = 1; i <= n; i++)
        b[i] = ref[a[i]];
    block = sqrt(n);
    for (int i = 1; i <= n; i++)
        blo[i] = (i - 1) / block + 1;
}

void AddR(int i)
{
    min2[b[i]] = min1[b[i]] = min(min1[b[i]], i);
    max2[b[i]] = max1[b[i]] = max(max1[b[i]], i);
    res2 = res1 = max(res1, max1[b[i]] - min1[b[i]]);
}

void AddL(int i)
{
    min2[b[i]] = min(min2[b[i]], i);
    max2[b[i]] = max(max2[b[i]], i);
    res2 = max(res2, max2[b[i]] - min2[b[i]]);
}

void Del(int i)
{
    min2[b[i]] = min1[b[i]];
    max2[b[i]] = max1[b[i]];
    res2 = res1;
}

void CaptainMo()
{
    int nl = 1, nr = 0, nb = 0, nbr = 0;
    memset(min1, 0x3f, sizeof(min1));
    memset(min2, 0x3f, sizeof(min2));
    memset(min3, 0x3f, sizeof(min3));
    sort(qs + 1, qs + m + 1, Comp);
    for (int i = 1; i <= m; i++)
    {
        int l = qs[i].l, r = qs[i].r, id = qs[i].id;
        if (blo[r] - blo[l] < 2)
        {
            for (int j = l; j <= r; j++)
            {
                min3[b[j]] = min(min3[b[j]], j);
                max3[b[j]] = max(max3[b[j]], j);
                res3 = max(res3, max3[b[j]] - min3[b[j]]);
            }
            ans[id] = res3;
            for (int j = l; j <= r; j++)
                min3[b[j]] = INF, max3[b[j]] = 0;
            res3 = 0;
            continue;
        }
        if (blo[l] != nb)
        {
            for (int j = 1; j <= N; j++)
            {
                min1[j] = INF;
                min2[j] = INF;
                max1[j] = 0;
                max2[j] = 0;
            }
            res1 = res2 = 0;
            nb = blo[l];
            nbr = min(nb * block, n);
            nr = nbr;
            nl = nr + 1;
        }
        while (nr < r)
            AddR(++nr);
        while (nl > l)
            AddL(--nl);
        ans[id] = res2;
        while (nl <= nbr)
            Del(nl++);
        res2 = res1;
    }
}

int main()
{
    // freopen(".in", "r", stdin);
    n = geti();
    // printf("%d\n", n);
    for (int i = 1; i <= n; i++)
        a[i] = geti();
    m = geti();
    // printf("%d\n", m);
    for (int i = 1; i <= m; i++)
    {
        qs[i].id = i;
        qs[i].l = geti();
        qs[i].r = geti();
    }
    // printf("YES\n");
    Prework();
    CaptainMo();
    for (int i = 1; i <= m; i++)
    {
        printf("%d\n", ans[i]);
        //wri(ans[i]);
        //putchar('\n');
>>>>>>> 7accd82a617af53dbbadef28dc4ad90e56a2e3c4
    }
    st = n,
    en = 1;
    printf("%lld ", Dinic());
    return 0;
}