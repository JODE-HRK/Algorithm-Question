#include <bits/stdc++.h>
using namespace std;
int n, rR[400 << 1], rB[400 << 1], lR[400 << 1], lB[400 << 1], ans;
char c[400 << 1];
int main()
{
    scanf("%d", &n);
    scanf("%s", c + 1);
    for (int i = 1; i <= n; ++i)
        c[i + n] = c[i];
    lB[0] = 0;
    lR[0] = 0;
    for (int i = 1; i <= n * 2; ++i)
    {
        if (c[i] == 'w')
        {
            lR[i] = lR[i - 1] + 1;
            lB[i] = lB[i - 1] + 1;
        }
        else if (c[i] == 'r')
            lR[i] = lR[i - 1] + 1;
        else if (c[i] == 'b')
            lB[i] = lB[i - 1] + 1;
    }
    for (int i = n * 2; i >= 1; --i)
    {
        if (c[i] == 'w')
        {
            rR[i] = rR[i + 1] + 1;
            rB[i] = rB[i + 1] + 1;
        }
        else if (c[i] == 'r')
            rR[i] = rR[i + 1] + 1;
        else if (c[i] == 'b')
            rB[i] = rB[i + 1] + 1;
    }
    for (int i = (n << 1) - 1; i >= 1; --i)
        ans = max(ans, max(lR[i], lB[i]) + max(rR[i + 1], rB[i + 1]));
    if (ans > n)
        ans = n;
    printf("%d", ans);
    return 0;
}