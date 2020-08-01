#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
long long n, m;
struct Flo
{
    int a, b, id;
} f[maxn], nf[maxn];
bool cmp(Flo x, Flo y)
{
    return x.b > y.b;
}
bool cmp1(Flo x, Flo y)
{
    return x.a > y.a;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= m; i++)
            scanf("%d %d", &f[i].a, &f[i].b), f[i].id = i, nf[i] = f[i];
        sort(f + 1, f + 1 + n, cmp);
        sort(nf + 1, nf + 1 + n, cmp1);
        int cnt = 0;
        long long sum = 0;
        while (1)
        {
            
        }
    }
    return 0;
}