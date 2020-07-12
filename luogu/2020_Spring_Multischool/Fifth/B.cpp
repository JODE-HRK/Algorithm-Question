#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
using namespace std;
const int maxn = 1e6 + 7;
int n, x, a[maxn], b[maxn], ans = 0;
ll ax = 0;
bool p[maxn];
priority_queue<pii> MaxS;
priority_queue<pii, vector<pii>, greater<pii>> Q;
void check(ll &sum)
{
    while (!Q.empty())
    {
        pii now = Q.top();
        if (sum - now.first < max(MaxS.top().first, a[now.second]))
            return;
        Q.pop();
        sum -= now.first;
        p[now.second] = 0;
        MaxS.emplace(a[now.second], now.second);
    }
    return;
}
int main()
{
    scanf("%d %d", &n, &x);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]);
    for (int i = 1; i <= n; i++)
        if (i != x)
            MaxS.emplace(a[i] - b[i], i), Q.emplace(b[i], i), ax += b[i], p[i] = 1;
        else
            ax += a[i];
    if (ax < MaxS.top().first)
    {
        printf("The Soviet Union is doomed");
        return 0;
    }
    check(ax);
    ans = Q.size();
    int cnt = 0;
    while (!MaxS.empty())
    {
        ++cnt;
        pii now = MaxS.top();
        if (p[now.second])
            break;
        MaxS.pop(), ax += b[now.second], p[now.second] = 1;
        check(ax), ans = min(ans, cnt + (int)Q.size());
    }
    printf("%d", ans);
    return 0;
}