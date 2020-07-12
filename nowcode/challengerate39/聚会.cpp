#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e5 + 7;
int t, n;
ll x[maxn];
ll getans1(ll a, ll b)
{
    int t = (a + b) >> 1, p = ((a + b) % 2 != 0);
    return max(abs(a - t) + p, abs(b - t) + p);
}
ll getans2(ll a, ll b)
{
    if (a < b)
        swap(a, b);
    ll mida = a >> 1;
    return min(mida, b);
}
int main()
{
    cin >> t;
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &x[i]);
        sort(x + 1, x + 1 + n);
        ll ans = 1000000001;
        if ((x[1] <= 0 && x[n] <= 0) || (x[1] >= 0 && x[n] >= 0))
            ans = getans1(x[1], x[n]);
        ans = min(ans, getans2(abs(x[1]), abs(x[n])));
        printf("%lld\n", ans);
    }
    return 0;
}