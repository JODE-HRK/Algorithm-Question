<<<<<<< HEAD
#include <bits/stdc++.h>
=======
<<<<<<< HEAD
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
=======
#include <cstdio>
#include <iostream>
>>>>>>> 5d6fbdb46ed2fbb3fe61d964965b9fc622d18146
#define ll long long
using namespace std;
const int maxn = 3010;
int n, k;
int a[maxn];
int main()
{
<<<<<<< HEAD
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + 1 + n);
    
=======
    n = read(), len = 2;
    while (len < n)
        len <<= 1;
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    for (int i = 2, l = len << 1; i <= l; ++i)
        lg[i] = lg[i >> 1] + 1; //获得每一层的层级标号
    build(1, 1, len, 1);
    for (int m = read(), l, r; m; --m)
        l = read(), r = read(),
        print(query(l, r));
    return Ot(), 0;
>>>>>>> 21e5d29df6664aa0d801d89bbe6004c6b2f2360a
>>>>>>> 5d6fbdb46ed2fbb3fe61d964965b9fc622d18146
}