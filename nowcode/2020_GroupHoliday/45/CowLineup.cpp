/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-06 09:46:33
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-06 10:34:30
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int n, k, tot = 0;
int a[maxn];
map<int, int> mp;
queue<int> Q;
int in[maxn];
int main()
{
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        if (mp[a[i]] == 0)
            mp[a[i]] = ++tot;
        a[i] = mp[a[i]]; //因为和数的大小没有关系，所以采用map进行离散化
    }
    int t = 1, sum = 0, ans = 0;
    while (t <= n)
    {
        while (t <= n && sum <= k)
        {
            Q.push(a[t]);
            if (in[a[t]] == 0)
                sum++;
            in[a[t]]++;
            ans = max(in[a[t++]], ans);
        }
        while (sum > k && t <= n)
        {
            if (!in[a[t]])
                break;
            Q.push(a[t]);
            in[a[t]]++;
            ans = max(ans, in[a[t++]]);
        }
        if (in[Q.front()] == 1)
            sum--;
        in[Q.front()]--;
        Q.pop();
    }
    printf("%d", ans);
    return 0;
}