/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-28 21:48:40
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-08-28 21:48:52
 */
#include <bits/stdc++.h>

#define ed end()
#define bg begin()
#define mp make_pair
#define pb push_back
#define all(x) x.bg, x.ed
#define newline puts("")
#define si(x) ((int)x.size())
#define rep(i, n) for (int i = 1; i <= n; ++i)
#define rrep(i, n) for (int i = 0; i < n; ++i)
#define srep(i, s, t) for (int i = s; i <= t; ++i)
#define drep(i, s, t) for (int i = t; i >= s; --i)

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int Maxn = 2e5 + 10;
const int Inf = 0x7f7f7f7f;
const ll Inf_ll = 1ll * Inf * Inf;
const int Mod = 199999;
const double eps = 1e-7;

ll mypow(ll a, ll b)
{
    ll inv = 1;
    while (b > 0)
    {
        if (b & 1)
            inv = inv * a % Mod;
        a = a * a % Mod;
        b >>= 1;
    }
    return inv;
}

ll calc(int n)
{
    return 1ll * (n + 1) * (n + 1) % Mod * (n + 2) % Mod * (n + 3) % Mod * (3 * n + 4) % Mod * mypow(24, Mod - 2) % Mod;
}

char s[Maxn];
ll Ans[Maxn];

int main()
{
    Ans[1] = 1;
    for (int i = 2; i <= Maxn - 10; i++)
        Ans[i] = Ans[i - 1] * calc(i - 1) % Mod;
    // for(int i=1;i<=5;i++)  cout<<Ans[i]<<" ";newline;
    int T;
    scanf("%d", &T);
    for (int _ = 1; _ <= T; _++)
    {
        scanf("%s", &s);
        int len = strlen(s);
        if (len > 6)
        {
            puts("0");
            continue;
        }
        int x = 0;
        for (int i = 0; i < len; i++)
            x = x * 10 + s[i] - '0';
        ll ans = 0;
        if (x >= Mod)
        {
            puts("0");
            continue;
        }
        printf("%lld\n", Ans[x]);
    }
    return 0;
}