//ST表模板题  查询区间和
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int n, m, l, r;
int a[maxn];
int ST[maxn][20];
void pre()
{
    for (int i = 1; i <= n; i++)
        ST[i][0] = a[i]; //先将起点赋值
    for (int i = 1; (1 << i) <= n; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++) //此处j代表起点，i代表到达的2^i-1的长度
            ST[j][i] = max(ST[j][i - 1], ST[j + (1 << (i - 1))][i - 1]);
}
int getans(int l, int r)
{
    int k = (int)(log((double)(r - l + 1)) / log(2.0)); //获取你需要跨越的长度2^k-1
    return max(ST[l][k], ST[r - (1 << k) + 1][k]);
}
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    pre();
    while (m--)
    {
        scanf("%d %d", &l, &r);
        printf("%d\n", getans(l, r));
    }
    return 0;
}