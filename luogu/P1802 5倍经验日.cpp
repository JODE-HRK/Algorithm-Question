#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n, m;
int lose[1001], win[1001], used[1001];
ll dp[1002];
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &lose[i]);
        scanf("%d", &win[i]);
        scanf("%d", &used[i]);
    }
    fill(dp, dp + 1 + m, 0);
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 0; j--)
            if (j >= used[i])
                dp[j] = max(dp[j] + lose[i], dp[j - used[i]] + win[i]);
            else
                dp[j] += lose[i];
    printf("%lld", dp[m] * 5);
    return 0;
}