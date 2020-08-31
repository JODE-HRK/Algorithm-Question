#include <bits/stdc++.h>
typedef long long ll;

using namespace std;
const int maxn = 6e5 + 7;
int u[maxn], v[maxn], val[maxn];
struct Edge
{
    int fr, to, val;
} edge[maxn << 1];
int L[maxn];
unsigned int SA,
    SB,
    SC;
int n, m, q, LIM;
bool cmp(Edge x, Edge y)
{
    return x.val < y.val;
}
unsigned int rng61()
{
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    unsigned int t = SA;
    SA = SB;
    SB = SC;
    SC ^= t ^ SA;
    return SC;
}
void gen()
{
    scanf("%d%d%d%u%u%u%d", &n, &m, &q, &SA, &SB, &SC, &LIM);
    for (int i = 1; i <= m; i++)
    {
        edge[i].fr = rng61() % n + 1;
        edge[i].to = rng61() % n + 1;
        edge[i].val = rng61() % LIM;
    }
    for (int i = 1; i <= q; i++)
    {
        L[i] = rng61() % LIM;
    }
}
int sz[maxn], fa[maxn];
int fd(int x)
{
    return fa[x] == x ? x : fa[x] = fd(fa[x]);
}
vector<ll> sum, num;
ll z[maxn];

ll las;
ll calc(int x)
{
    return 1ll * x * (x - 1) / 2;
}
int main()
{
    gen();
    /*
    int n, m, q;
    scanf("%d %d %d",&n,&m,&q);
    for(int i=1;i<=m;i++)
    {
        int u, v, w;
        scanf("%d %d %d",&u,&v,&w);
        edge[i].fr = u;
        edge[i].to = v;
        edge[i].val = w;
    }
    for(int i=1;i<=q;i++)  scanf("%d",&L[i]);
*/

    fill(sz, sz + 1 + n, 0);
    sort(edge + 1, edge + 1 + m, cmp);
    for (int i = 1; i <= n; i++)
        fa[i] = i, sz[i] = 1;
    for (int i = 1; i <= m; i++)
    {
        // printf("%d %d %d\n", edge[i].fr, edge[i].to, edge[i].val);
        int fr = fd(edge[i].fr), to = fd(edge[i].to);
        if (fr != to)
        {
            // printf("YUES\n");
            fa[fr] = to;
            las -= calc(sz[to]) + calc(sz[fr]);
            sz[to] += sz[fr];
            las += calc(sz[to]);
            sum.push_back(las);
            num.push_back(edge[i].val);
        }
    }
    int Size = sum.size();
    // for (int i = 0; i < Size; i++)
    // printf("%lld ", sum[i]);
    // cout << endl;
    for (int i = 0; i < Size; i++)
        z[i] = sum[i];
    ll Ans = 0;
    for (int i = 1; i <= q; i++)
    {
        if (L[i] < num[0])
        {
            continue;
        }
        int l = 0, r = Size - 1, ans = 0;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (num[mid] <= L[i])
                l = mid + 1, ans = mid;
            else
                r = mid - 1;
        }
        // printf("%lld\n",z[ans]);
        Ans ^= z[ans];
    }
    printf("%lld\n", Ans);
    return 0;
}
/*
6 5 8
1 2 1
2 3 2
6 5 1
4 5 2
3 4 5
1
2
3
4
5
6
7
8
*/
