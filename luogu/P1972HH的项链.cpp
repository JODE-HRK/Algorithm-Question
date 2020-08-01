#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int n, q;
int a[maxn], last[maxn], ans[maxn], val[maxn];
struct Query
{
    int l, r, id;
    bool operator<(const Query &x)
    {
        return r < x.r;
    }
} que[maxn];
int lowbit(int x)
{
    return x & (-x);
}
void add(int pos, int c)
{
    while (pos <= n)
    {
        val[pos] += c;
        pos += lowbit(pos);
    }
}
int getsum(int pos)
{
    int res = 0;
    while (pos)
    {
        res += val[pos];
        pos -= lowbit(pos);
    }
    return res;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    scanf("%d ", &q);
    for (int i = 1; i <= q; i++)
    {
        scanf("%d %d", &que[i].l, &que[i].r);
        que[i].id = i;
    }
    sort(que + 1, que + 1 + q);
    int pre = 0;
    for (int i = 1; i <= q; i++)
    {
        if (que[i].r > pre)
        {
            for (int j = pre + 1; j <= que[i].r; j++)
            {
                if (last[a[j]])
                    add(last[a[j]], -1);
                add(j, 1);
                last[a[j]] = j; //此处如果数很大的话，可以离散化或者用map来记录上一次的位置
                pre = que[i].r;
            }
        }
        ans[que[i].id] = getsum(que[i].r) - getsum(que[i].l - 1);
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
    return 0;
}