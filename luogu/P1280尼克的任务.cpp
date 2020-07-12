#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, k;
ll dp[100001];
struct Node
{
    ll start, len;
} a[10001];
bool cmp(Node x, Node y)
{
    return x.start > y.start;
}
int main()
{
    scanf("%lld %lld", &n, &k);
    for (int i = 1; i <= k; i++)
        scanf("%lld %lld", &a[i].start, &a[i].len);
    sort(a + 1, a + 1 + k, cmp);
    dp[n + 1] = 0;
    int cnt = 1;
    for (int i = n; i > 0; i--)
    {
        if (cnt <= k && a[cnt].start == i)
        {
            while (cnt <= k && a[cnt].start == i)
            {
                dp[i] = max(dp[i], dp[i + a[cnt].len]);
                cnt++;
            }
        }
        else
            dp[i] = dp[i + 1] + 1;
    }
    printf("%lld", dp[1]);
    return 0;
}