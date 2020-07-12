#include <bits/stdc++.h>
using namespace std;
int n, x;
long long ans = 0;
int main()
{
    scanf("%d %d", &n, &x);
    int a[n + 1];
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 2; i <= n; i++)
        if (a[i] + a[i - 1] > x)
        {
            ans += a[i] + a[i - 1] - x;
            a[i] -= (a[i] + a[i - 1] - x);
        }
    printf("%lld", ans);
    return 0;
}