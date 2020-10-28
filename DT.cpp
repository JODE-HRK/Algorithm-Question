#include <bits/stdc++.h>
using namespace std;
const int maxn = 20020, inf = 0x7f7f7f7f;
int n, head[maxn * 2], num, tot, ans; //tot记录当前子树点数
int dis[maxn], flag[maxn], temp[maxn];
//dis记录子树每一点到根节点的距离，flag用于删除根节点，temp总汇到根节点的距离
int size[maxn], Max[maxn], root;
struct edge
{
    int next, to, len;
} G[maxn * 2];
void add(int from, int to, int len)
{
    G[++num].next = head[from];
    G[num].to = to;
    G[num].len = len;
    head[from] = num;
}
inline void input(void)
{
    for (int i = 1; i < n; i++)
    {
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        add(x, y, v), add(y, x, v);
    }
}

inline void dp(int fa, int cur) //求树的重心
{
    size[cur] = 1, Max[cur] = 0;
    for (int i = head[cur]; i; i = G[i].next)
    {
        int v = G[i].to;
        if (flag[v] || v == fa)
            continue;
        dp(cur, v);
        size[cur] += size[v];
        Max[cur] = max(Max[cur], size[v]);
    }
    Max[cur] = max(Max[cur], tot - size[cur]);
    if (Max[root] > Max[cur])
        root = cur;
}

inline void dfs(int fa, int cur)
{
    temp[++temp[0]] = dis[cur];
    for (int i = head[cur]; i; i = G[i].next)
    {
        int v = G[i].to;
        if (v == fa || flag[v])
            continue;
        dis[v] = dis[cur] + G[i].len;
        dfs(cur, v);
    }
}

int cc[2019];
inline int calc(int x, int len)
{
    dis[x] = len;
    temp[0] = 0; //temp[0]记录temp数组的长度
    dfs(0, x);
    memset(cc, 0, sizeof(cc));
    for (int i = 1; i <= temp[0]; i++)
        cc[temp[i] % 2019]++;

    cc[0]--;
    int res = cc[0] * (cc[0] + 1) / 2;
    for (int i = 1; i <= 1009; i++)
        res += cc[i] * cc[2019 - i];
    return res;
}

inline void divide(int x)
{
    flag[x] = true; //删去根节点
    ans += calc(x, 0);
    //cout<<"ans="<<ans<<"\n";
    for (int i = head[x]; i; i = G[i].next)
    {
        int y = G[i].to;
        if (flag[y])
            continue;
        ans -= calc(y, G[i].len); //点对在同一子树的情况
        tot = size[y], root = 0;
        dp(0, y);
        divide(root);
    }
}
inline void reset(void)
{
    num = 0;
    memset(head, 0, sizeof head);
    memset(flag, 0, sizeof flag);
    ans = 0, tot = n;
    root = 0, Max[0] = inf;
}
int main()
{
    scanf("%d", &n);
    reset();
    input();
    dp(0, 1);
    divide(root);
    printf("%d", ans);
    return 0;
}