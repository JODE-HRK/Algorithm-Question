#include <bits/stdc++.h>
using namespace std;
int n, w, a[30001];
int main()
{
    scanf("%d %d", &w, &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + 1 + n);
    int ans = 0, l = 1, r = n;
    while (l < r)
    {
        while (l < r && a[l] + a[r] > w)
            r--, ans++;
        if (l < r)
            ans++, l++, r--;
    }
    if (l == r)
        ans++;
    cout << ans;
    return 0;
}