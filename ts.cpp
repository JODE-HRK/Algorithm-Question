<<<<<<< HEAD
/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-09-11 10:50:08
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-09-15 19:36:08
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e7 + 7;
const ll mod = 99997867;
int n, d;
int a[maxn], b[maxn];
int cnt[15];
bool p;
bool pd()
{
    int cc[15];
    for (int i = 1; i <= 9; i++)
        cc[i] = cnt[i];
    for (int i = 1; i <= 9; i++)
        if (cc[i] == 4)
            cc[i] = 1;
    for (int i = 1; i <= 9; i++)
    {
        // if (i == 7)
        // {
        //     printf("%d", cc[i]);
        //     cout << endl;
        //     cout << endl;
        // }
        if (cc[i] == 0)
        {
            continue;
        }
        else if (cc[i] == 3)
            cc[i] -= 3;
        else if (cc[i] <= 2)
        {
            if (i > 7)
                return 0;
            if (cc[i + 1] >= cc[i] && cc[i + 2] >= cc[i])
            {
                cc[i + 1] -= cc[i];
                cc[i + 2] -= cc[i];
            }
            else
                return 0;
        }
    }
    return 1;
}
bool judge()
{
    for (int i = 1; i <= 9; i++)
        if (cnt[i] >= 2)
        {
            cnt[i] -= 2;
            if (pd())
            {
                cnt[i] += 2;
                return 1;
            }
            cnt[i] += 2;
        }
    return 0;
}
int main()
{
    for (int i = 1; i <= 13; i++)
        scanf("%d", &a[i]), cnt[a[i]]++;
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 13; j++)
            b[j] = a[j];
        b[14] = i;
        cnt[i]++;
        sort(b + 1, b + 1 + 14);
        if (judge())
        {
            printf("%d ", i);
            p = 1;
        }
        cnt[i]--;
    }
    if (!p)
        printf("0");
=======
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
>>>>>>> 21e5d29df6664aa0d801d89bbe6004c6b2f2360a
    return 0;
}