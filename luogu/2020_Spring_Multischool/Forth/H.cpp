#include <bits/stdc++.h>
using namespace std;

int h, r, d;
const long double pi = acosl(-1);

long double get1(int H)
{
    H = min(max(H, 0), r);
    return pi * H * H * (r - H / 3.0L);
}
long double get2(int H)
{
    H = min(max(H, 0), h);
    return pi * r * r * H;
}

int main()
{
    scanf("%d%d%d", &h, &r, &d);
    int k = (h + 2 * r) / d + !!((h + 2 * r) % d);
    for (int i = 0; i < k; i++)
    {
        int s = i * d, t = (i + 1) * d;
        long double ans = get1(t) - get1(s) + get2(t - r) - get2(s - r) + get1(h + 2 * r - s) - get1(h + 2 * r - t);
        printf("%.10lf\n", (double)ans);
    }
}
