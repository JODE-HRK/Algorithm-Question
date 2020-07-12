#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <queue>
#include <vector>
#include <map>
using namespace std;
const int maxn = 1e7 + 7;
int n, m, tot = 0;
int lg[maxn], fa[maxn][24], depth[maxn]; //fa[i][j],i节点往上2^j的父亲
struct op
{
    int t, nex;
} e[maxn << 1];
int head[maxn];
int a[maxn];
void add(int x, int y)
{
    e[++tot].t = y;
    e[tot].nex = head[x];
    head[x] = tot;
}
void dfs(int now, int fath)
{
    a[now] = 1;
    fa[now][0] = fath, depth[now] = depth[fath] + 1;
    for (int i = 1; i <= lg[depth[now]]; i++) //在建树的过程中，把该节点的所有2^0,2^1……上面的节点全部求出来
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    for (int i = head[now]; i; i = e[i].nex) //往下走
        if (e[i].t != fath)
            dfs(e[i].t, now), a[now] += a[e[i].t];
}
int LCA(int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b); //我们需要恒定一个大小关系，方便下一个循环
    while (depth[a] > depth[b])
        a = fa[a][lg[depth[a] - depth[b]] - 1]; //使两者的深度相同
    if (a == b)
        return a;
    for (int k = lg[depth[a]] - 1; k >= 0; k--) //在相同的深度情况下，就可以一起往上面跳了，此处是距离从大到小跳
        if (fa[a][k] != fa[b][k])               //lg[depth[a]]-1==log2(depth[a])，
            a = fa[a][k], b = fa[b][k];         //不相等就跳过去
    return fa[a][0];
}
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i < n; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        add(x, y);
        add(y, x);
    }
    for (int i = 1; i <= n; ++i) //预先算出log_2(i)+1的值，用的时候直接调用就可以了
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    dfs(1, 0); //接着把树建好
    for (int i = 1; i <= m; i++)
    {
        int xa, xb;
        scanf("%d %d", &xa, &xb);
        int fas = LCA(xa, xb);
        if (fas == xa)
            printf("%d\n", a[xb]);
        else if (fas == xb)
            printf("%d\n", n - a[xa]);
        else
            printf("%d\n", a[xb]);
    }
    return 0;
}