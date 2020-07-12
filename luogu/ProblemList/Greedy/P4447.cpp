#include <bits/stdc++.h>
using namespace std;
int n, a[100001];
bool cmp(int x, int y)
{
    return x > y;
}
struct op
{
    int tail, len;
} s[100007];
set<op> S;
bool cmps(op x, op y)
{
    if (x.tail == y.tail)
        return x.len < y.len;
    return x.tail < y.tail;
}
int f(int x, int t)
{
    int l = 1, r = t, ans = -1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (s[mid].tail > x)
            r = mid;
        else if (s[mid].tail <= x)
            l = mid + 1;
    }
    ans = l;
    return ans <= t && s[ans].tail - x == 1 ? ans : -1;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + 1 + n, cmp);
    int t = 0;
    for (int i = 1; i <= n; i++)
    {
        int p = f(a[i], t);
        if (p > 0)
            s[p].len++, s[p].tail = a[i];
        else
            s[++t] = (op){a[i], 1};
        sort(s + 1, s + 1 + t, cmps);
    }
    int ans = 0x7fffffff;
    for (int i = 1; i <= t; i++)
        ans = min(s[i].len, ans);
    cout << ans;
    return 0;
}