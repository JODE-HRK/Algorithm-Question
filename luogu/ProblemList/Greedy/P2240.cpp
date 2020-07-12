#include <bits/stdc++.h>
using namespace std;
int n, t;
struct op
{
    double m, v, Unit_Price;
} a[101];
bool cmp(op x, op y)
{
    return x.Unit_Price > y.Unit_Price;
};
int main()
{
    scanf("%d %d", &n, &t);
    for (int i = 1; i <= n; i++)
        scanf("%lf %lf", &a[i].m, &a[i].v), a[i].Unit_Price = a[i].v / a[i].m;
    sort(a + 1, a + 1 + n, cmp);
    double ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (t >= a[i].m)
        {
            t -= a[i].m;
            ans += a[i].v;
        }
        else
        {
            ans += (a[i].Unit_Price * t);
            t = 0;
            break;
        }
    }
    printf("%.2lf", ans);
    return 0;
}