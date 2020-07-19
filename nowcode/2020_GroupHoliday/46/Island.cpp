/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-16 16:39:32
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-16 16:51:57
 */
uni]asda
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
inline int read()
{
    int x = 0;
    char c = getchar();
    while (c > '9' || c < '0')
        c = getchar();
    while (c >= '0' && c <= '9')
        x = x * 10 + c - '0', c = getchar();
    return x;
}
int n;
int h[maxn], tot = 0, minn = 0x7fffffff;
map<int, int> Map;
priority_queue<int, vector<int>, greater<int> > Q;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &h[i]);
        minn = min(minn, h[i]);
        Q.push(h[i]);
    }
    int now = Q.top();
    Q.pop();
    for (int i = 1;!Q.empty();i++){

    }
        return 0;
}