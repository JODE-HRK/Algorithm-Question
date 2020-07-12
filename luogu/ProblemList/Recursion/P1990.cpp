#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int n;
int main()
{
    scanf("%d", &n);
    int dp[n + 1];
    dp[0] = 1, dp[1] = 1, dp[2] = 2, dp[3] = 5;
    for (int i = 4; i <= n; i++)
    {
        dp[i] = (dp[i - 1] + dp[i - 2] + 2 * (dp[i - 3] + dp[i - 4])) % 10000;
    }
    printf("%d", dp[n]);
    return 0;
}
