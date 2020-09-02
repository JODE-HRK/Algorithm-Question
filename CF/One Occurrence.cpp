/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-27 12:40:47
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-08-30 22:55:12
 */
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e6 + 7;
int n, m, block;
int b[maxn], c[maxn];
struct PRO
{
    int l, r, id, blo;
} pro[maxn];
bool cmp(PRO a, PRO b)
{
    return (a.blo ^ b.blo) ? a.l < b.l : ((a.blo & 1) ? a.r < b.r : a.r > b.r); //奇偶排序优化
}
bool vis[maxn];
int heap[maxn], head = 0, pos[maxn];
int ans = 0;
void add(int x)
{
    ++c[x];
    if (c[x] == 1)
    {
        heap[++head] = x;
        pos[x] = head;
    }
    else if (c[x] == 2)
    {
        heap[pos[x]] = heap[head];
        pos[heap[head]] = pos[x];
        pos[x] = heap[head--] = 0;
    }
}
void del(int x)
{
    --c[x];
    if (c[x] == 1)
    {
        heap[++head] = x;
        pos[x] = head;
    }
    else if (c[x] == 0)
    {
        heap[pos[x]] = heap[head];
        pos[heap[head]] = pos[x];
        pos[x] = heap[head--] = 0;
    }
}
int zans[maxn];
inline int read()
{
    char c = getchar();
    int x = 0, fh = 0;
    while (c < '0' || c > '9')
    {
        fh |= c == '-';
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return fh ? -x : x;
}
void print(int x)
{
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
    n = read();
    block = 1000;
    for (register int i = 1; i <= n; i++)
        b[i] = read();
    // root[0] = build(1, n);
    m = read();
    for (register int i = 1; i <= m; i++)
        pro[i].l = read(), pro[i].r = read(), pro[i].id = i, pro[i].blo = (pro[i].l - 1) / block + 1;
    sort(pro + 1, pro + 1 + m, cmp);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++)
    {
        // printf("PRO:%intd %intd\n", pro[i].l, pro[i].r);
        while (r < pro[i].r)
            add(b[++r]);
        while (r > pro[i].r)
            del(b[r--]);
        while (l < pro[i].l)
            del(b[l++]);
        while (l > pro[i].l)
            add(b[--l]);
        // printf("YES\n");
        zans[pro[i].id] = heap[head];
        // printf("%intd\n", ans);
    }
    for (register int i = 1; i <= m; i++)
        print(zans[i]), printf("\n");
    return 0;
}
/*
10
1 9 1 3 4 1 5 7 2 1
10
1 2
1 7
1 9
1 8
1 1
2 4
1 3
1 4
1 5
2 5
*/