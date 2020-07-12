#include <bits/stdc++.h>
using namespace std;
int n;
const int maxn = 5001;
int dp[5001][maxn];
void js(int id)
{
    fill(dp[id], dp[id] + maxn, 0);
    int t = 0;
    for (int i = maxn - 1; i >= 0; i--)
        dp[id][i] = dp[id - 1][i] + dp[id - 2][i] + t, t = dp[id][i] / 10, dp[id][i] %= 10;
}
int main()
{
    scanf("%d", &n);
    if (n == 0)
    {
        cout << "0";
        return 0;
    }
    dp[1][maxn - 1] = 1, dp[2][maxn - 1] = 2;
    for (int i = 3; i <= n; i++)
        js(i);
    int p = 0;
    for (int i = 0; i <= maxn - 1; i++)
    {
        if (dp[n][i] > 0)
            p = 1;
        if (p)
            cout << dp[n][i];
    }
    return 0;
}