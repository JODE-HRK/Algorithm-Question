#include <bits/stdc++.h>
using namespace std;
int n, m;
const int maxn = 2e5 + 7;
int mn1[maxn], mn2[maxn], mn3[maxn];
int mx1[maxn], mx2[maxn], mx3[maxn];
int res1, res2, res3;
int ans[maxn];
struct PRO
{
    int l, r, id, blo;
} pro[maxn];
int a[maxn], cnt = 0, block;
int posfr[maxn], posto[maxn];
map<int, int> M;
bool cmp(PRO a, PRO b)
{
    return (a.blo != b.blo) ? a.l < b.l : a.r < b.r; //为了保证区间只增不减
} //左端点在同一块就按照右端点小的排序，不在同一块就按照左端点小的排序
int blo[maxn];
void addL(int i)
{
    mn2[a[i]] = min(mn2[a[i]], i);
    mx2[a[i]] = max(mx2[a[i]], i);
    res2 = max(res2, mx2[a[i]] - mn2[a[i]]);
}
void addR(int i)
{
    mn2[a[i]] = mn1[a[i]] = min(mn1[a[i]], i);
    mx2[a[i]] = mx1[a[i]] = max(mx1[a[i]], i);
    res2 = res1 = max(res1, mx1[a[i]] - mn1[a[i]]);
}
void del(int i)
{
    mn2[a[i]] = mn1[a[i]];
    mx2[a[i]] = mx1[a[i]];
    res2 = res1;
}
int main()
{
    scanf("%d", &n);
    block = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        if (!M[a[i]])
            M[a[i]] = ++cnt;
        a[i] = M[a[i]];
    } //离散化完毕
    // printf("CNT:%d\n", cnt);
    for (int i = 1; i <= n; i++)
        blo[i] = (i - 1) / block + 1;

    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d %d", &pro[i].l, &pro[i].r), pro[i].blo = (pro[i].l - 1) / block, pro[i].id = i;

    sort(pro + 1, pro + 1 + m, cmp); //问题排序完毕
    fill(mn1, mn1 + 1 + cnt, 0x7fffffff);
    fill(mn2, mn2 + 1 + cnt, 0x7fffffff);
    fill(mn3, mn3 + 1 + cnt, 0x7fffffff);
    fill(mx1, mx1 + 1 + cnt, 0);
    fill(mx2, mx2 + 1 + cnt, 0);
    fill(mx3, mx3 + 1 + cnt, 0);
    //初始化
    int nl = 1, nr = 0, nb = 0, nbr = 0; //nl和nr记录区间端点

    for (int i = 1; i <= m; i++)
    {
        int l = pro[i].l, r = pro[i].r;
        if (blo[r] - blo[l] < 1) //左右端点在同一个块的特殊处理
        {
            for (int j = l; j <= r; j++)
            {
                mn3[a[j]] = min(mn3[a[j]], j);
                mx3[a[j]] = max(mx3[a[j]], j);
                res3 = max(res3, mx3[a[j]] - mn3[a[j]]);
            }
            ans[pro[i].id] = res3;
            for (int j = l; j <= r; j++)
                mn3[a[j]] = 0x7fffffff, mx3[a[j]] = 0;
            res3 = 0;
            continue;
        }
        if (blo[l] != nb) //如果左端点换块了
        {
            for (int j = 1; j <= cnt; j++)
            {
                mn1[j] = mn2[j] = 0x7fffffff;
                mx1[j] = mx2[j] = 0;
            }
            res1 = res2 = 0;
            //全部预处理
            nb = blo[l];
            nbr = min(nb * block, n); //这是分界点
            nr = nbr;
            nl = nr + 1;
        }
        while (nr < r)
            addR(++nr);
        while (nl > l)
            addL(--nl);
        ans[pro[i].id] = res2;
        while (nl <= nbr) //撤回操作
            del(nl++);
        res2 = res1;
    }
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
    return 0;
}