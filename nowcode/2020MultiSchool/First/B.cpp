/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-11 21:06:32
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-11 21:45:37
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int n, x, ans = 0;
int a[maxn], b[maxn];
int f[maxn], dp[maxn], posa[maxn], posb[maxn];
int ppos = 1;
vector<int> G;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        G.push_back(x);
    }
    for (int i = 0; i < G.size(); i++)
        a[i + 1] = G[i], b[n - i] = G[i];
    f[1] = a[1], posa[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (f[ppos] < a[i])
        {
            f[++ppos] = a[i];
            posa[i] = ppos;
        }
        else
        {
            int tmp = lower_bound(f + 1, f + 1 + ppos, a[i]) - f;
            f[tmp] = a[i];
            posa[i] = tmp;
        }
    }
    dp[1] = a[1], posb[1] = 1;
    ppos = 1;
    for (int i = 2; i <= n; i++)
    {
        if (dp[ppos] < b[i])
        {
            dp[++ppos] = b[i];
            posb[i] = ppos;
        }
        else
        {
            int tmp = lower_bound(dp + 1, dp + 1 + ppos, b[i]) - dp;
            dp[tmp] = a[i];
            posb[i] = tmp;
        }
    }
    for (int i = 1; i <= n; i++)
        ans = max(ans, posa[i] + posb[n - i + 1] - 1);
    printf("%d", ans);
    return 0;
}