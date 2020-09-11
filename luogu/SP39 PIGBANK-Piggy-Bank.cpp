#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e6 + 7;
int n, m;
int w;
int wei[maxn], val[maxn];
int dp[maxn];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int w1, w2;
        scanf("%d %d", &w1, &w2);
        w = w2 - w1;
        fill(dp + 1, dp + 1 + w, 1000000000);
        dp[0] = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d %d", &val[i], &wei[i]);
        for (int i = 1; i <= n; i++)
            for (int j = wei[i]; j <= w; j++)
                if (dp[j - wei[i]] != 1000000000)
                    dp[j] = min(dp[j], dp[j - wei[i]] + val[i]);
        if (dp[w] == 1000000000)
            printf("This is impossible.\n");
        else
            printf("The minimum amount of money in the piggy-bank is %d.\n", dp[w]);
    }
    return 0;
}