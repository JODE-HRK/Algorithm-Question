/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-28 21:48:15
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-08-28 21:48:29
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
int in()
{
    int x = 0;
    char c = getchar();
    bool f = 0;
    while (c < '0' || c > '9')
        f |= c == '-', c = getchar();
    while (c >= '0' && c <= '9')
        x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? -x : x;
}
template <typename T>
inline void chk_min(T &_, T __) { _ = _ < __ ? _ : __; }

const int N = 2e5 + 5;

int blo, bl[N];

struct query
{
    int l, r, id;
} q[N];
int n, m;
int a[N], res[N];

inline bool cmp(const query &i, const query &j)
{
    if (bl[i.l] != bl[j.l])
        return bl[i.l] < bl[j.l];
    if (bl[i.l] & 1)
        return i.r < j.r;
    return i.r > j.r;
}

struct block_split
{
    int a[N], b[1000];
    inline void modify(int p, int k)
    {
        if (!a[p])
            ++b[bl[p]];
        a[p] += k;
        if (!a[p])
            --b[bl[p]];
    }
    int query()
    {
        int i;
        for (i = 1; i < bl[n]; ++i)
            if (b[i] < blo)
                break;
        for (int j = (i - 1) * blo; j <= std::min(n, i * blo - 1); ++j)
            if (!a[j])
                return j;
        return n;
    }
} B;

inline void add(const int p)
{
    B.modify(a[p], 1);
}

inline void rem(const int p)
{
    B.modify(a[p], -1);
}

int main()
{
    n = in(), m = in();
    for (int i = 1; i <= n; ++i)
        a[i] = in(), chk_min(a[i], n);
    for (int i = 1; i <= m; ++i)
        q[i] = (query){in(), in(), i};
    blo = (int)sqrt(n + 1);
    for (int i = 0; i <= n; ++i)
        bl[i] = i / blo + 1;
    std::sort(q + 1, q + 1 + m, cmp);
    for (int i = 1, l = 1, r = 0; i <= m; ++i)
    {
        for (; l > q[i].l; add(--l))
            ;
        for (; r < q[i].r; add(++r))
            ;
        for (; l < q[i].l; rem(l++))
            ;
        for (; r > q[i].r; rem(r--))
            ;
        res[q[i].id] = B.query();
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", res[i]);
    return 0;
}