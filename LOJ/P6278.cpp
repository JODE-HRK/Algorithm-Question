#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 7;
int n, opt, l, r, block;
ll a[maxn], b[maxn], add[maxn], pos[maxn], sta[maxn], en[maxn], c;
void modify(int le, int rr, ll cc)
{
    int p = pos[le], q = pos[rr];
    if (p == q)
    {
        for (int i = sta[p]; i <= en[p]; i++)
        {
            a[i] += add[p];
            if (i >= le && i <= rr)
                a[i] += cc;
            b[i] = a[i];
        }
        add[p] = 0;
        sort(b + sta[p], b + en[p] + 1);
        return;
    }
    for (int i = sta[p]; i <= en[p]; i++)
    {
        a[i] += add[p];
        if (i >= le)
            a[i] += cc;
        b[i] = a[i];
    }
    add[p] = 0;
    sort(b + sta[p], b + en[p] + 1);
    for (int i = sta[q]; i <= en[q]; i++)
    {
        a[i] += add[q];
        if (i <= rr)
            a[i] += cc;
        b[i] = a[i];
    }
    add[q] = 0;
    sort(b + sta[q], b + en[q] + 1);
    for (int i = p + 1; i < q; i++)
        add[i] += cc;
}
ll query(int le, int rr, ll MAX)
{
    int p = pos[le], q = pos[rr];
    ll ans = 0;
    if (p == q)
    {
        for (int i = le; i <= rr; i++)
            ans += (a[i] + add[p] < MAX);
        return ans;
    }
    for (int i = le; i <= en[p]; i++)
        ans += (a[i] + add[p] < MAX);
    for (int i = sta[q]; i <= rr; i++)
        ans += (a[i] + add[q] < MAX);
    for (int i = p + 1; i < q; i++)
        ans += (lower_bound(b + sta[i], b + en[i] + 1, MAX - add[i]) - b - sta[i]);
    return ans;
}
int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    scanf("%d", &n);
    block = (int)sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]), b[i] = a[i];
        pos[i] = (i + block - 1) / block;
        if (!sta[pos[i]])
            sta[pos[i]] = i;
        en[pos[i]] = i;
    }
    for (int i = 1; i <= pos[n]; i++)
    {
        int x = block * (i - 1) + 1, y = min(block * i, n);
        sort(b + x, b + y + 1);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d %d %lld", &opt, &l, &r, &c);
        if (opt == 0)
            modify(l, r, 1ll * c);
        else
            printf("%lld\n", query(l, r, 1ll * c * c));
    }
    return 0;
}