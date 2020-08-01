#include <bits/stdc++.h>
#define ll long long
const int mod = 998244573;
const int maxn = 1e6 + 7;
using namespace std;

/*
快速幂
*/
struct POW
{
    ll pow_mod(ll base, ll power)
    {
        ll ans = 1;
        while (power)
        {
            if (power & 1)
                ans = ans * base % (1ll * mod);
            power >>= 1;
            base = (base * base) % (1ll * mod);
        }
        return ans;
    }
};
/*
慢速乘(实际上很快)
防止有两个较大的数相乘而直接乘爆, 所以用快速乘, 
因为是加法, 怎么都不可能加爆. 所以目的就是为了防止爆范围. 
*/
struct SLOW_MUL
{
    ll mul(ll a, ll b)
    {
        ll ans = 0;
        if (b & 1)
            ans += a;
        a <<= 1;
        b >>= 1;
        return ans;
    }
    inline ll mult_mod(ll a, ll b, ll m)
    { //这是时间为O(1)的防爆乘，防止卡时间
        ll c = a * b - (ll)((long double)a * b / m + 0.5) * m;
        return c < 0 ? c + m : c; //就是算的a*b%m;
    }
};
/*
逆元
求解 a * x≡b（mod m） 方程
*/
struct INV
{
    void consecutive_inv() //线性求逆元 求1~n的逆元
    {
        ll inv[maxn], n, mmod;
        inv[1] = 1;
        scanf("%lld %lld", &n, &mmod);
        for (int i = 2; i <= n; i++)
        {
            printf("%lld\n", inv[i - 1]);
            inv[i] = (mmod - mmod / i) * inv[mmod % i] % mmod;
        }
    }
    ll getinv(ll base, ll power) //此处的power是 mod-2
    {
        ll ans = 1;
        while (power)
        {
            if (power & 1)
                ans = ans * base % (1ll * mod);
            power >>= 1;
            base = (base * base) % (1ll * mod);
        }
        return ans;
    }
    void consecutive_distinct_inv() //求任意给定n个数的逆元
    {
        ll s[maxn], sv[maxn], a[maxn], n, mod, inv[maxn];
        s[0] = 1;
        for (int i = 1; i <= n; i++)
            s[i] = s[i - 1] * a[i] % mod;
        sv[n] = getinv(s[n], mod - 2);
        for (int i = n; i >= 1; --i)
            sv[i - 1] = sv[i] * a[i] % mod;
        for (int i = 1; i <= n; i++)
            inv[i] = sv[i] * s[i - 1] % mod;
    }
};