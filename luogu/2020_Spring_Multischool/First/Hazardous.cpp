#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 7;
int n, col[maxn], cnt = 0, tcnt = 0;
int curdepth;
int head[maxn], root[maxn], dep[maxn];
long long sc[maxn], delta;
struct Node
{
    int to, nxt, val;
} edge[maxn << 2];
struct ND
{
    int l, r, cnt;
    ll dep;
} T[maxn * 20];
void add(int fr, int to)
{
    edge[++cnt].to = to;
    edge[cnt].val = 1;
    edge[cnt].nxt = head[fr];
    head[fr] = cnt;
}
int Merge(int x, int y, int l, int r) //此处是合并操作，x是父亲，y是儿子
{
    if (!x || !y)
        return x | y;
    if (l == r)
    {
        delta += T[x].dep * T[y].cnt + T[y].dep * T[x].cnt - 2ll * curdepth * T[x].cnt * T[y].cnt;
        T[x].dep += T[y].dep;
        T[x].cnt += T[y].cnt;
    }
    else
    {
        int mid = (l + r) >> 1;
        T[x].l = Merge(T[x].l, T[y].l, l, mid);
        T[x].r = Merge(T[x].r, T[y].r, mid + 1, r);
    }
    return x;
}
int init(int c, int l, int r) //颜色，1，n
{
    int x = ++tcnt; //从给每个节点重新标号
    if (l < r)
    {
        int mid = (l + r) >> 1; //
        if (c <= mid)
            T[x].l = init(c, l, mid); //为什么要用颜色来做标准？未解决
        else
            T[x].r = init(c, mid + 1, r);
    }
    else
        T[x].dep = curdepth, T[x].cnt = 1; //标记当前深度(同类颜色的计数)
    return x;                              //重新标号后返回
}
void dfs(int x, int fa)
{
    curdepth = dep[x];                         // 当前深度
    root[x] = init(col[x], 1, n);              //树的初始化,root[i]是第i个节点的新编号
    for (int i = head[x]; ~i; i = edge[i].nxt) //向前星遍历
        if (edge[i].to != fa)
        {
            int to = edge[i].to;
            dep[to] = dep[x] + 1;                     //儿子的深度+1
            dfs(to, x);                               //对儿子进行深搜
            sc[x] += sc[to];                          //sc表示答案，所以肯定要加上儿子的
            delta = 0;                                //delta初始化，之后需要保存合并新添加的答案
            curdepth = dep[x];                        //有需要重新定义当前的深度
            root[x] = Merge(root[x], root[to], 1, n); //进行完所有init操作之后，再进行合并操作
            sc[x] += delta;
        }
}
int main()
{
    scanf("%d", &n);
    fill(head, head + 1 + n, -1); //向前星的head要初始化为 -1 便于后面的 调用时 使用 ~i判断
    for (int i = 1; i <= n; i++)
        scanf("%d", &col[i]);
    for (int i = 1; i < n; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        add(a, b);
        add(b, a);
    }
    dfs(1, 0); //既然是树不是图，深搜是有必要的
    for (int i = 1; i <= n; i++)
        printf("%lld ", sc[i]);
    return 0;
}