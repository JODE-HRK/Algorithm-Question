#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;
int n, q;
struct Drop
{
    double x, v;
} drop[maxn];
pair<double, double> lp[maxn];
bool cmp(Drop x, Drop y)
{
    return x.x < y.x;
}
double r = 1e9, l = 0e0;
bool cmp2(pair<double, double> X, pair<double, double> Y)
{
    return fabs(X.first - Y.first) < 1e-6 ? X.second < Y.second : X.first < Y.first;
}
bool check(double ans)
{
    double p = 1e9, maxx = 0;
    for (int i = 1; i <= q; i++)
        lp[i] = {drop[i].x - drop[i].v * ans, drop[i].x + drop[i].v * ans};
    sort(lp + 1, lp + 1 + q, cmp2);
    lp[0] = {0, 0}, lp[q + 1] = {n, n};
    for (int i = 1; i <= q; i++)
    {
        if (lp[i].first > maxx)
            return 0;
        maxx = max(maxx, lp[i].second);
        p = min(p, lp[i].first);
    }
    if (p > 0 || maxx < n)
        return 0;
    return 1;
}
int main()
{
    scanf("%d %d", &n, &q);
    drop[0] = {0.0, 0.0}, drop[q + 1] = {n * 1.0, 0.0};
    for (int i = 1; i <= q; i++)
        scanf("%lf %lf", &drop[i].x, &drop[i].v);
    sort(drop + 1, drop + 1 + q, cmp);
    double time = 0.0;
    while (fabs(r - l) >= 0.00000001)
    {
        double mid = (l + r) / 2;
        if (check(mid))
            r = mid, time = mid;
        else
            l = mid + 0.00000001;
    }
    printf("%.7lf", time);
    return 0;
}