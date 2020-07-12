#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 998244353;
ll n, maxn = 0;
ll a[2001];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], maxn = max(maxn, a[i]);
    int dp[n + 5][2 * maxn + 5], ans = 0;
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++)
    {
        for (int j = i - 1; j > 0; j--)
        {
            int cha = a[i] - a[j] + maxn;
            dp[i][cha] = (dp[i][cha] + (dp[j][cha] + 1)) % mod;
            ans = (ans + dp[j][cha] + 1) % mod;
        }
    }
    printf("%d", (ans + n) % mod);
    return 0;
}