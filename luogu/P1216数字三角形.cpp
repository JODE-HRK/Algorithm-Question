#include <bits/stdc++.h>
using namespace std;
int n;
int main()
{
    int a[10001], dp[10001];
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        if (i == 1)
            scanf("%d", &a[i]), dp[i] = a[i];
        else
        {
            for (int j = 1; j <= i; j++)
                scanf("%d", &a[j]);
            for (int j = i; j > 0; j--)
            {
                if (j == 1)
                    dp[j] = dp[j] + a[j];
                else if (j == i)
                    dp[j] = dp[j - 1] + a[j];
                else if (j != i)
                {
                    dp[j] = max(dp[j] + a[j], dp[j - 1] + a[j]);
                }
            }
        }
    }
    int ans = dp[1];
    for (int i = 1; i <= n; i++)
        ans = max(ans, dp[i]);
    printf("%d", ans);
    return 0;
}