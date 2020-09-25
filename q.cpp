/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-09-02 21:41:35
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-09-23 21:38:13
 */
#include <bits/stdc++.h>
using namespace std;
int n;
deque<int> Q;
int a[110];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + 1 + n);
    a[0] = -1;
    for (int i = 1; i <= n; i++)
        if (i & 1)
            Q.push_front(a[i]);
        else
            Q.push_back(a[i]);
    while (!Q.empty())
    {
        printf("%d ", Q.front());
        Q.pop_front();
    }
    return 0;
}