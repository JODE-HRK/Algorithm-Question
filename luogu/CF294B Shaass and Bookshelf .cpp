#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000001;
int n, m;
int v[101], w[101];
int dp[maxn];
int thick;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &v[i], &w[i]), thick += v[i];
    // printf("%d\n", thick);
    fill(dp, dp + 1 + thick, 10000000);
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = thick; j >= v[i]; j--)
        {
            dp[j] = min(dp[j], dp[j - v[i]] + w[i]); //dp[j] 代表 厚度为j的情况下剩下的书的长度
        }
    }
    int ans = 0;
    for (int i = thick; i >= 0; i--)
    {
        if (thick - i >= dp[i]) //倒序查询，当存在一个厚度大于等于长度的时候即为答案
        {
            ans = thick - i;
            break;
        }
    }
    printf("%d", ans);
    return 0;
}