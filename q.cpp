<<<<<<< HEAD
/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-09-25 22:55:52
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-10-13 21:12:37
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 7;
ll a[maxn];
ll n, k, A, B;
ll merge(ll l, ll r)
{
    ll mid = (l + r) >> 1;
    ll tans = 0;
    ll cnt = upper_bound(a + 1, a + 1 + k, r) - lower_bound(a + 1, a + 1 + k, l);
    if (!cnt)
        tans = A;
    else
    {
        tans = B * cnt * (r - l + 1);
        if (r - l < 1)
            return tans;
        tans = min(tans, merge(l, mid) + merge(mid + 1, r));
    }
    return tans;
}
int main()
{
    scanf("%lld %lld %lld %lld", &n, &k, &A, &B);
    for (int i = 1; i <= k; i++)
        scanf("%lld", &a[i]);
    sort(a + 1, a + 1 + k);
    printf("%lld", merge(1ll, 1ll << n));
    return 0;
}
=======
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 7;
int s[maxn], z[maxn], bst[maxn];
int n, m;
int main()
{
    while (scanf("%d%d", &n, &m))
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &s[i]);
            s[i]--;
        }
        for (int i = 0; i < n / 2; i++)
            swap(s[i], s[n - i - 1]);
        for (int i = 1, j = 0; i < n; ++i)
        {
            if (i < j + z[j])
            {
                z[i] = min(j + z[j] - i, z[i - j]);
            }
            while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            {
                z[i]++;
            }
        }
        for (int i = 0; i < n; ++i)
        {
            bst[s[i]] = std::max(bst[s[i]], 1 + z[i + 1]);
        }
        ll three = 1;
        ll ans = 0;
        for (int i = 0; i < m; ++i)
        {
            three = 3LL * three % mod;
            ans ^= 1LL * three * (n + 1 - bst[i]) % mod;
            assert(bst[i] <= n + 1);
        }
        printf("%lld\n", ans);
    }
}
>>>>>>> b88f7f830f753cc2c23c0b171e899f678054c8ae
