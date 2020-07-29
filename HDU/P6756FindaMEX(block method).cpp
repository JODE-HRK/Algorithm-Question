#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e5 + 10;
const int block = 1000;
int n, m, q, tot, cnt;
int head[maxn], in[maxn], id[maxn], a[maxn];
int num[110][maxn];
bool st[maxn];
set<int> s[maxn];
vector<int> now[maxn];
struct Edge
{
    int to, nxt;
} edge[maxn];
inline void addEdge(int fr, int to)
{
    edge[tot] = (Edge){to, head[fr]};
    head[fr] = tot++;
}
inline void init()
{
    tot = 0, cnt = 0;
    for (int i = 0; i <= n; i++)
        now[i].clear(), st[i] = 0, head[i] = -1, in[i] = 0;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &n, &m);
        init();
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        for (int i = 1; i <= m; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            in[u]++, in[v]++;
            addEdge(u, v);
            addEdge(v, u);
        }
        for (int i = 1; i <= n; i++)
            if (in[i] >= block)
            {
                id[i] = ++cnt;
                s[cnt].clear();
                for (int j = 0; j <= in[i]; j++)
                    s[cnt].insert(j), num[cnt][j] = 0;
            }
        for (int i = 1; i <= n; i++)
        {
            for (int j = head[i]; ~j; j = edge[j].nxt)
            {
                int to = edge[j].to;
                if (in[to] >= block)
                {
                    if (a[i] <= in[to])
                        if (++num[id[to]][a[i]] == 1)
                            s[id[to]].erase(a[i]);
                    now[i].push_back(to);
                }
            }
        }
        scanf("%d", &q);
        while (q--)
        {
            int opt;
            scanf("%d", &opt);
            if (opt == 1)
            {
                int x, y;
                scanf("%d %d", &x, &y);
                for (auto tmp : now[x])
                {
                    if (y <= in[tmp])
                        if (++num[id[tmp]][y] == 1)
                            s[id[tmp]].erase(y);
                    if (a[x] <= in[tmp])
                        if (--num[id[tmp]][a[x]] == 0)
                            s[id[tmp]].insert(a[x]);
                }
                a[x] = y;
            }
            else
            {
                int x;
                scanf("%d", &x);
                if (in[x] >= block)
                    printf("%d\n", *s[id[x]].begin());
                else
                {
                    for (int i = head[x]; ~i; i = edge[i].nxt)
                    {
                        int v = edge[i].to;
                        if (a[v] <= in[x])
                            st[a[v]] = 1;
                    }
                    int ans = 0;
                    while (st[ans])
                        ans++;
                    printf("%d\n", ans);
                    for (int i = head[x]; ~i; i = edge[i].nxt)
                    {
                        int v = edge[i].to;
                        if (a[v] <= in[x])
                            st[a[v]] = 0;
                    }
                }
            }
        }
    }
    return 0;
}