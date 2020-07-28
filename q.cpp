#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll int
using namespace std;
const int maxn = 5e6 + 7;
ll s[maxn], sv[maxn], a[maxn], n, mod, inv[maxn], k;
inline ll read()
{
    ll s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        s = ((s << 3) + (s << 1)) + ch - '0', ch = getchar();
    return s * w;
}
ll getinv(ll base, ll power) //此处的power是 mod-2
{
    ll ans = 1;
    while (power)
    {
        if (power & 1)
            ans = ans * base % mod;
        power >>= 1;
        base = (base * base) % mod;
    }
    return ans;
}
void consecutive_distinct_inv() //求任意给定n个数的逆元
{
    s[0] = 1;
    for (register int i = 1; i <= n; ++i)
        s[i] = s[i - 1] * a[i] % mod;
    sv[n] = getinv(s[n], mod - 2);
    for (register int i = n; i >= 1; --i)
        sv[i - 1] = sv[i] * a[i] % mod;
    for (register int i = 1; i <= n; ++i)
        inv[i] = sv[i] * s[i - 1] % mod;
}
int main()
{
    scanf("%lld %lld %lld", &n, &mod, &k);
    for (register int i = 1; i <= n; ++i)
        a[i] = read();
    consecutive_distinct_inv();
    ll multi = 1, ans = 0;
    for (register int i = 1; i <= n; ++i)
    {
        multi = (multi * k) % mod;
        ans = (ans + multi * inv[i] % mod) % mod;
    }
    printf("%lld", ans);
    return 0;
}