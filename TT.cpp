#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;
const int maxn = 1e7 + 7;
int cnt = 0, hi[maxn], k, dp[maxn], f[maxn], ans = 1, ti = 1;
int n;
void getans()
{
    f[1] = dp[1] = hi[1];
    for (int i = 2; i <= cnt; i++)
    {
        if (f[ans] >= hi[i])
            f[++ans] = hi[i];
        else
        {
            int h = 1, d = ans;
            while (h < d)
            {
                int mid = (h + d) >> 1;
                if (f[mid] >= hi[i])
                    h = mid + 1;
                else
                    d = mid;
            }                        //二分在k数组里找第一个小于a[i]的数
            f[h] = max(f[h], hi[i]); //进行比较，贪心思想
        }
        if (dp[ti] < hi[i])
            dp[++ti] = hi[i];
        else
        {
            int x = 1, y = ti, mid;
            while (x < y)
            {
                mid = (x + y) >> 1;
                if (dp[mid] >= hi[i])
                    y = mid;
                else
                    x = mid + 1;
            }                          //二分在g数组里找第一个大于等于a[i]的数
            dp[x] = min(dp[x], hi[i]); //进行比较，贪心思想
        }
    }
}
int getUnsigned()
{
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();

    int ret = (int)(ch - '0');
    while ('0' <= (ch = getchar()) && ch <= '9')
        ret = ret * 10 + (int)(ch - '0');
    return ret;
}
int main()
{
    while (1)
    {
        n = getUnsigned();
        if (n == 0)
            break;
        ans = 1, ti = 1;
        cnt = n;
        for (int i = 1; i <= n; i++)
            hi[i] = getUnsigned();
        getans();
        if (n - ans <= 1 || n - ti <= 1)
            printf("Y\n");
        else
            printf("N\n");
    }
    return 0;
}