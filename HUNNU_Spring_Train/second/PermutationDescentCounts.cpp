#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int mod = 1001113;
int t, n, m, id;
int dp[101][101];
void pre()
{
    memset(dp, 0, sizeof(dp));
    dp[2][0] = dp[2][1] = 1;
    for (int i = 3; i <= 100; i++)
    {
        dp[i][0] = 1;
        for (int j = 1; j < i - 1; j++)
            dp[i][j] = (dp[i - 1][j - 1] * (i - j) % mod + dp[i - 1][j] * (j + 1) % mod) % mod;
        dp[i][i - 1] = 1;
    }
}
int main()
{
    pre();
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d %d", &id, &n, &m);
        printf("%d %d\n", id, dp[n][m]);
    }
    return 0;
}