#include <bits/stdc++.h>
using namespace std;
int n, s, a, b;
struct apple
{
    int h, strength;
    bool operator<(apple x)
    {
        return h < x.h;
    }
} app[100001];
bool cmp(apple x, apple y)
{
    return x.strength < y.strength;
}
int main()
{
    scanf("%d %d %d %d", &n, &s, &a, &b);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &app[i].h, &app[i].strength);
    sort(app + 1, app + 1 + n);
    int ans = 0, pos = n;
    for (int i = 1; i <= n; i++)
    {
        if (app[i].h > (a + b))
        {
            pos = i - 1;
            break;
        }
    }
    if (pos == 0)
    {
        cout << '0';
        return 0;
    }
    sort(app + 1, app + 1 + pos, cmp);
    for (int i = 1; i <= pos && s > 0; i++)
    {
        if (s >= app[i].strength)
            ans++;
        s -= app[i].strength;
    }
    cout << ans;
    return 0;
}