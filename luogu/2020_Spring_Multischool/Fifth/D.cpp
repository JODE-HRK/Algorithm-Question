#include <bits/stdc++.h>
using namespace std;
#define N 100005
#define MOD 1000000007
#define mid (l + r >> 1)
#define ll long long
int n;
ll nw, ans, s[N], ds[N], c[N][2];
int id(ll x) { return lower_bound(ds + 1, ds + ds[0] + 1, x) - ds; }
struct SegTree
{
    struct Seg
    {
        ll v;
        bool tg;
    } sg[N << 2];
    void f(int p)
    {
        sg[p].v = 0;
        sg[p].tg = 1;
    }
    void pu(int p) { sg[p].v = sg[p << 1].v + sg[p << 1 | 1].v; }
    void pd(int p)
    {
        if (sg[p].tg)
            f(p << 1), f(p << 1 | 1), sg[p].tg = 0;
    }
    void upd1(int p, int l, int r, int x, ll v)
    {
        sg[p].v += v;
        if (l == r)
            return;
        pd(p);
        if (x <= mid)
            upd1(p << 1, l, mid, x, v);
        else
            upd1(p << 1 | 1, mid + 1, r, x, v);
        pu(p);
    }
    void upd2(int p, int l, int r, int qL, int qR)
    {
        if (qL > qR)
            return;
        if (l >= qL && r <= qR)
        {
            f(p);
            return;
        }
        pd(p);
        if (qL <= mid)
            upd2(p << 1, l, mid, qL, qR);
        if (qR > mid)
            upd2(p << 1 | 1, mid + 1, r, qL, qR);
        pu(p);
    }
    ll qSm(int p, int l, int r, int qL, int qR)
    {
        if (qL > qR)
            return 0;
        if (l >= qL && r <= qR)
            return sg[p].v;
        ll res = 0;
        pd(p);
        if (qL <= mid)
            res = qSm(p << 1, l, mid, qL, qR);
        if (qR > mid)
            res += qSm(p << 1 | 1, mid + 1, r, qL, qR);
        pu(p);
        return res;
    }
} ST[2];
int main()
{
    ds[0] = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &s[i]), s[i] += s[i - 1], ds[++ds[0]] = -s[i];//ds存的时前缀和的相反数
    sort(ds + 1, ds + ds[0] + 1);
    ds[0] = unique(ds + 1, ds + ds[0] + 1) - ds - 1;//数据离散
    for (int i = 1, x; i <= n; ++i)
    {
        ll t;
        x = id(-s[i - 1]);//找到离散之后的位置
        ST[0].upd1(1, 1, ds[0], x, 1);//
        ST[1].upd1(1, 1, ds[0], x, ds[x] % MOD);
        x = id(-s[i]);
        t = ST[0].qSm(1, 1, ds[0], x + 1, ds[0]);
        ST[0].upd1(1, 1, ds[0], x, t);
        ST[1].upd1(1, 1, ds[0], x, t * ds[x] % MOD);
        ST[0].upd2(1, 1, ds[0], x + 1, ds[0]);
        ST[1].upd2(1, 1, ds[0], x + 1, ds[0]);
        c[i][0] = (-nw - ST[1].qSm(1, 1, ds[0], 1, ds[0])) % MOD;
        nw = (nw + s[i]) % MOD;
    }
    ST[0].upd2(1, 1, ds[0], 1, ds[0]);
    ST[1].upd2(1, 1, ds[0], 1, ds[0]);
    ds[0] = 1;
    nw = ds[1] = 0;
    for (int i = n; i >= 1; --i)
        s[i] += s[i + 1] - s[i - 1], ds[++ds[0]] = -s[i];
    sort(ds + 1, ds + ds[0] + 1);
    ds[0] = unique(ds + 1, ds + ds[0] + 1) - ds - 1;
    for (int i = n, x; i >= 1; --i)
    {
        ll t;
        x = id(-s[i + 1]);
        ST[0].upd1(1, 1, ds[0], x, 1);
        ST[1].upd1(1, 1, ds[0], x, ds[x] % MOD);
        x = id(-s[i]);
        t = ST[0].qSm(1, 1, ds[0], x + 1, ds[0]);
        ST[0].upd1(1, 1, ds[0], x, t);
        ST[1].upd1(1, 1, ds[0], x, t * ds[x] % MOD);
        ST[0].upd2(1, 1, ds[0], x + 1, ds[0]);
        ST[1].upd2(1, 1, ds[0], x + 1, ds[0]);
        c[i][1] = (-nw - ST[1].qSm(1, 1, ds[0], 1, ds[0])) % MOD;
        nw = (nw + s[i]) % MOD;
    }
    for (int i = 1; i < n; ++i)
        ans = (ans + c[i][0] * c[i + 1][1] % MOD) % MOD;
    printf("%lld\n", (ans + MOD) % MOD);
    return 0;
}
