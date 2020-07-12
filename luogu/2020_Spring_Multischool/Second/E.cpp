#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int n, m;
int fa[2][maxn], sum[2][maxn];
queue<pair<int, int>> M[2];
int find(int fa[], int x)
{
    return x == fa[x] ? x : fa[x] = find(fa, fa[x]);
}
void deal()
{ //对两张图进行判断
    while (!M[0].empty())
    {
        int u = M[0].front().first, v = M[0].front().second;
        if (find(fa[0], u) != find(fa[0], v))
            break;
        M[0].pop();
    }
    while (!M[1].empty())
    {
        int u = M[1].front().first, v = M[1].front().second;
        if (find(fa[1], u) != find(fa[1], v))
            break;
        M[1].pop();
    }
}
void pre()
{ //初始化
    for (int i = 1; i <= n; i++)
    {
        fa[0][i] = fa[1][i] = i;
        sum[0][i] = sum[1][i] = 1;
    }
}
void merge(int fa[], int s[], int u, int v)
{
    u = find(fa, u), v = find(fa, v);
    if (u == v)
        return;
    if (s[u] < s[v])
        swap(u, v);
    fa[v] = u;
    s[u] += s[v]; //这个始终以权重大的点为最终父节点
}
int main()
{
    scanf("%d %d", &n, &m);
    pre();
    for (int i = 1; i <= m; i++)
    {
        int u, v, id;
        scanf("%d %d %d", &id, &u, &v);
        M[id - 1].push({u, v});                     //在本图中加边
        merge(fa[!(id - 1)], sum[!(id - 1)], u, v); //在另一张图中进行处理
        deal();
        if (M[0].empty() && M[1].empty()) //如果两张图连通性相同，那么队列里面一定是空的
            printf("A\n");
        else
            printf("B\n");
    }
    return 0;
}