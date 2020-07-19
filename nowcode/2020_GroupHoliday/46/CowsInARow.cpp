/*
    * @Descripttion: 
    * @version: 
    * @Author: JODEHRK
    * @Date: 2020-07-12 09:21:54
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-15 14:26:41
    */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int n;
int a[maxn];
int ans = 0;
int sum = 0;
queue<int> Q;
int main()
{
    memset(a, 0, sizeof(a));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        Q.push(x);
        if (!a[x])
            sum++;
        a[x]++;
        while (sum > 2)
        {
            a[Q.front()]--;
            if (!a[Q.front()])
                sum--;
            Q.pop();
        }
        ans = max(ans, a[x]);
    }
    while (!Q.empty())
    {
        ans = max(ans, a[Q.front()]--);
        Q.pop();
    }
    printf("%d", ans);
    return 0;
}