<<<<<<< HEAD
/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-09-02 21:41:35
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-09-23 21:38:13
 */
#include <bits/stdc++.h>
using namespace std;
int n;
deque<int> Q;
int a[110];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + 1 + n);
    a[0] = -1;
    for (int i = 1; i <= n; i++)
        if (i & 1)
            Q.push_front(a[i]);
        else
            Q.push_back(a[i]);
    while (!Q.empty())
    {
        printf("%d ", Q.front());
        Q.pop_front();
    }
    return 0;
=======
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
const int M = 2e5 + 3;
#ifndef Judge
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
#endif
char buf[1 << 21], *p1 = buf, *p2 = buf;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            f = -1;
    for (; isdigit(c); c = getchar())
        x = x * 10 + c - '0';
    return x * f;
}
char sr[1 << 21], z[20];
int C = -1, Z;
inline void Ot() { fwrite(sr, 1, C + 1, stdout), C = -1; }
inline void print(int x, char chr = '\n')
{
    if (C > 1 << 20)
        Ot();
    if (x < 0)
        sr[++C] = 45, x = -x;
    while (z[++Z] = x % 10 + 48, x /= 10)
        ;
    while (sr[++C] = z[Z], --Z)
        ;
    sr[++C] = chr;
}
int n, m, a[M], len, lg[M << 2], pos[M], p[21][M], s[21][M];
// p 数组为区间最大子段和， s 数组为包含端点的最大子段和
inline int Max(int a, int b) { return a > b ? a : b; }
#define ls k << 1
#define rs k << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
void build(int k, int l, int r, int d)
{ //这里的边界是叶子结点
    //到达叶子后要记录一下 位置 l 对应的叶子结点编号
    if (l == r)
        return pos[l] = k, void();
    int prep, sm;
    // 处理左半部分
    p[d][mid] = s[d][mid] = prep = sm = a[mid], sm = Max(sm, 0);
    for (int i = mid - 1; i >= l; --i)
        prep += a[i], sm += a[i], s[d][i] = Max(s[d][i + 1], prep),
                                  p[d][i] = Max(p[d][i + 1], sm), sm = Max(sm, 0);
    // 处理右半部分
    p[d][mid + 1] = s[d][mid + 1] = prep = sm = a[mid + 1], sm = Max(sm, 0);
    for (int i = mid + 2; i <= r; ++i)
        prep += a[i], sm += a[i], s[d][i] = Max(s[d][i - 1], prep),
                                  p[d][i] = Max(p[d][i - 1], sm), sm = Max(sm, 0);
    build(lson, d + 1), build(rson, d + 1); //向下递归
}
inline int query(int l, int r)
{
    if (l == r)
        return a[l];
    int d = lg[pos[l]] - lg[pos[l] ^ pos[r]]; //得到 lca 所在层
    return Max(Max(p[d][l], p[d][r]), s[d][l] + s[d][r]);
}
int main()
{
    n = read(), len = 2;
    while (len < n)
        len <<= 1;
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    for (int i = 2, l = len << 1; i <= l; ++i)
        lg[i] = lg[i >> 1] + 1; //获得每一层的层级标号
    build(1, 1, len, 1);
    for (int m = read(), l, r; m; --m)
        l = read(), r = read(),
        print(query(l, r));
    return Ot(), 0;
>>>>>>> 21e5d29df6664aa0d801d89bbe6004c6b2f2360a
}