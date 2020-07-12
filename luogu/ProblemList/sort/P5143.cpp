#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 7;
int n;
struct op
{
    int x, y, h;
} a[maxn];
bool cmp(op x, op y)
{
    return x.h < y.h;
}
double getans(int i, int j)
{
    return sqrt(pow(a[i].h - a[j].h, 2) + pow(a[i].x - a[j].x, 2) + pow(a[i].y - a[j].y, 2));
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].h);
    sort(a + 1, a + 1 + n, cmp);
    double ans = 0;
    for (int i = 2; i <= n; i++)
        ans += getans(i, i - 1);
    printf("%.3lf", ans);
    return 0;
}
