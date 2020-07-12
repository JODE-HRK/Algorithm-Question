#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <vector>
#define ll long long
using namespace std;
const int maxn = 1e4 + 7;
int t, id;
ll n, m;
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        ll dp[maxn];
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        scanf("%d %lld %lld", &id, &m, &n);
        for (int i = 1; i <= n; i *= m)
            for (int j = i; j <= n; j++)
                dp[j] += dp[j - i];
        // cout << dp[n];
        printf("%d %lld\n", id, dp[n]);
    }
    return 0;
}