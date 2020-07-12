#include <bits/stdc++.h>
using namespace std;
long long ans = 0;
int n, a[1001];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    a[0] = 0;
    sort(a, a + 1 + n);
    int l = 0, r = n, cnt = 0;
    while (l < r)
    {
        ans += (a[r] - a[l]) * (a[r] - a[l]);
        l += (cnt + 1) % 2;
        r -= cnt % 2;
        cnt++;
    }
    cout << ans;
    return 0;
}