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