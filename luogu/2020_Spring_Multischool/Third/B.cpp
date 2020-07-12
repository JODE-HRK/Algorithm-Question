#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int n, t, rel[maxn];
string a, b;
int main()
{
    //   freopen(".in","r",stdin);
    scanf("%d %d", &n, &t);
    cin >> a;
    cin >> b;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int sum = 0;
    for (int i = 0; i < n; i++)
        if (a[i] != b[i])
            sum++; //表示相同的位置不同符号
    if (sum == 0)
    {
        cout << sum;
        return 0;
    }
    for (int i = 1; i <= t; i++)
    {
        scanf("%d", &rel[i]);
        if (a[rel[i]] != b[rel[i]])       //第i次反转的是不同的地方
            sum--, a[rel[i]] = b[rel[i]]; //
        else
            sum++, a[rel[i]] = !b[rel[i]];
        if (i == sum || i == sum + 1)
        {
            cout << i;
            return 0;
        }
    }
    printf("icu\n");
    return 0;
}