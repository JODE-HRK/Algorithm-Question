#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 7;
int n;
struct Segment //由下向上扫描线段，即横向的线段
{
    ll l, r, h; //每一条线段的左端点、右端点，以及往下能到达的深度
    int val;    //val的意义就是在下底使这一个线段权值加1 表示扫描线向下扫的时候 保证这条线段的下方是覆盖的
    bool operator<(const Segment &x) const
    {
        return h < x.h;
    }
} Seg[maxn << 4];
struct Node
{
    int sum; //扫描线没来之前没有权值 权值变更是在扫描线到达某一条线段时修改
    ll len;
} tree[maxn << 4];
ll X[maxn << 4], ans = 0;
void build(int l, int r, int node)
{
    tree[node].sum = 0, tree[node].len = 0; //扫描线没到之前没有权值
    if (l == r)
        return;
    ll mid = (l + r) >> 1;
    build(l, mid, node << 1);
    build(mid + 1, r, node << 1 | 1);
}
void pushup(int l, int r, int node)
{
    if (tree[node].sum)
        tree[node].len = X[r + 1] - X[l]; //如果线段被扫描线扫到了 则更新扫到的线段长度
    else
        tree[node].len = tree[node << 1].len + tree[node << 1 | 1].len; //如果没被扫到 则从以前扫过的线段更新
}
void update(int l, int r, int node, int le, int ri, int val)
{
    if (X[r + 1] <= le || ri <= X[l])
        return;
    if (le <= X[l] && X[r + 1] <= ri)
    {
        tree[node].sum += val;
        pushup(l, r, node);
        return;
    }
    int mid = (l + r) >> 1;
    update(l, mid, node << 1, le, ri, val);
    update(mid + 1, r, node << 1 | 1, le, ri, val);
    pushup(l, r, node);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        ll xx, yy, x2, y2;
        scanf("%lld %lld %lld %lld", &xx, &yy, &x2, &y2); //输入矩形的两个端点，左下和右上两个端点
        X[i * 2 - 1] = xx, X[i * 2] = x2;                 //X数组仅保存x坐标
        Seg[i * 2 - 1] = (Segment){xx, x2, yy, 1};
        Seg[i * 2] = (Segment){xx, x2, y2, -1}; //保存两个线段，一个在上，一个在下
    }
    n <<= 1; //线段树是矩形的两倍
    sort(Seg + 1, Seg + 1 + n);
    sort(X + 1, X + 1 + n);
    int cnt = unique(X + 1, X + 1 + n) - X - 1; //离散化确定不同x坐标的数量
    build(1, cnt - 1, 1);                       //建树，保存的是线段的数量
    for (int i = 1; i <= n; i++)
    {
        update(1, cnt - 1, 1, Seg[i].l, Seg[i].r, Seg[i].val);
        ans += tree[1].len * (Seg[i + 1].h - Seg[i].h); //计算面积
    }
    printf("%lld", ans);
    return 0;
}