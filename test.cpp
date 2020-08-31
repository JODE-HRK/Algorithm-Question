#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn = 3e7 + 7;
ll n, sa, sb, sc, sd, mod;
ll a[maxn], b[maxn], ans = 0;
ll f(ll x)
{
	return (sa * x % mod * x % mod * x % mod + sb * x % mod * x % mod + sc * x % mod + sd) % mod;
}

int main()
{
	a[0] = 0;
	scanf("%lld %lld %lld %lld %lld %lld %lld", &n, &sa, &sb, &sc, &sd, &a[1], &mod);
	// printf("%lld %lld %lld %lld %lld %lld %lld\n", n, sa, sb, sc, sd, a[1], mod);
	ll maxh = a[1];
	for (ll i = 2; i <= n; i++)
	{
		a[i] = (f(a[i - 1]) + f(a[i - 2])) % mod;
		ans = max(ans, maxh - a[i]);
		maxh = max(maxh, a[i]);
	}
	// for (int i = 1; i <= n; i++)
	// 	printf("%lld ", a[i]);
	printf("%lld", ans / 2 + ans % 2);
	return 0;
}