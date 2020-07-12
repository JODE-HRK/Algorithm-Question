#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5e7 + 7;
int n;
ll sum[maxn], s;
set<ll> S;
void init()
{
    sum[0] = 0;
    for (int i = 1; i <= maxn - 7; i++)
        sum[i] = sum[i - 1] + i;
    ll ss = 1;
    S.insert(ss);
    for (int i = 1; i <= 30; i++)
        ss *= 2, S.insert(ss);
}
int main()
{
    init();
    scanf("%d", &n);
    while (n--)
    {
        scanf("%lld", &s);
        if (S.find(s) != S.end())
        {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }
        ll i = 1, j = 2, tsum = 3;
        while (i <= s / 2 && i < maxn)
        {
            tsum = sum[j] - sum[i - 1];
            while (tsum != s && i <= s / 2 && i < maxn)
            {
                if (tsum > s)
                    i++;
                else
                    j++;
                tsum = sum[j] - sum[i - 1];
            }
            if (tsum == s)
                break;
        }
        if (tsum != s || i == j)
            cout << "IMPOSSIBLE";
        else
        {
            cout << s << " = ";
            for (int p = i; p <= j; p++)
            {
                cout << p;
                if (p != j)
                    cout << " + ";
            }
        }
        cout << endl;
    }
    return 0;
}