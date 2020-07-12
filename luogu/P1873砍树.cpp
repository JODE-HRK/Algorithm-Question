#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e6 + 7;
ll n, m, l = 0x7F, r = -0x7F;
ll a[maxn];
bool check(ll h)
{
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans += max(a[i] - h, 1ll * 0);
    return ans >= m ? 1 : 0;
}
int main()
{
    scanf("%lld %lld", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]), l = min(l, a[i]), r = max(r, a[i]);
    ll ans;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }
    printf("%lld", ans);
    return 0;
}