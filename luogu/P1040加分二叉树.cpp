#include <bits/stdc++.h>
#define ll long long
using namespace std;
string origin, aimstr;
ll dp[31][31], root[40][40];
ll n;
void dfs(ll node, ll i, ll j)
{
    if (i > j)
        return;
    printf("%lld ", node);
    dfs(root[i][node - 1], i, node - 1);
    dfs(root[node + 1][j], node + 1, j);
}
int main()
{
    memset(dp, 0, sizeof(dp));
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &dp[i][i]), dp[i][i - 1] = 1, root[i][i] = i; //空树为1
    for (int len = 1; len <= n; len++)                              //枚举长度
        for (int i = 1; i + len <= n; i++)                          //因为是中序遍历，所以可以这样循环做dp
        {
            int j = i + len;
            dp[i][j] = dp[i][i] + dp[i + 1][j]; //初始化
            root[i][j] = i;                     //初始化
            for (int k = i + 1; k <= j; k++)
            {
                if (dp[i][j] < dp[i][k - 1] * dp[k + 1][j] + dp[k][k])
                {
                    dp[i][j] = dp[i][k - 1] * dp[k + 1][j] + dp[k][k];
                    root[i][j] = k;
                }
            }
        }
    printf("%lld\n", dp[1][n]);
    dfs(root[1][n], 1, n);
    return 0;
}