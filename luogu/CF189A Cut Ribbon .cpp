#include <bits/stdc++.h>
using namespace std;
int n, m;
int a[4], w[4];
int dp[5001];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= 3; i++)
    {
        scanf("%d", &a[i]);
        w[i] = 1;
    }
    fill(dp, dp + 1 + n, -1);
    dp[0] = 0;
    for (int j = 1; j <= 3; j++)
        for (int i = a[j]; i <= n; i++)
            if (dp[i - a[j]] != -1)
                dp[i] = max(dp[i], dp[i - a[j]] + 1);
    printf("%d", dp[n]);
    return 0;
}