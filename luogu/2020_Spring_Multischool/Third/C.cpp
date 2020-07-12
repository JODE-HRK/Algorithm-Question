#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int n, a[maxn];
int ans = 0;
bool judge(int x, int y)
{
    while (y)
    {
        int tmp = y;
        y = x % y;
        x = tmp;
    }
    if (x == 1)
        return 0;
    else
        return 1;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 2; i <= n; i++)
    {
        if (judge(a[i - 1], a[i]))
            ans++, i++;
    }
    printf("%d", ans);
    return 0;
}