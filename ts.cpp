#include <bits/stdc++.h>
using namespace std;
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
    }
    return 0;
}