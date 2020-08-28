/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-18 23:21:16
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-08-27 21:07:50
 */
/*
倍增求k代祖先
每个点上建立主席树，求k代儿子中的第k小
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 7;
int n, m;
int a[maxn];
int root[maxn], tot = 0;
struct Tree
{
    int val, lnode, rnode;
} tree[32 * maxn];
int clone(int node)
{
    ++tot;
    tree[tot] = tree[node];
    return tot;
}
int build(int l, int r, int node)
{
    node = ++tot;
    if (l == r)
    {
        tree[node].val = a[l];
        return node;
    }
    int mid = (l + r) >> 1;
    tree[node].lnode = build(l, mid, tree[node].lnode);
    tree[node].rnode = build(mid + 1, r, tree[node].rnode);
    return node;
}
int update(int l, int r, int node, int x, int val)
{
    node = clone(node);
    if (l == r)
        tree[node].val = val;
    else
    {
        int mid = (l + r) >> 1;
        if (x <= mid)
            tree[node].lnode = update(l, mid, tree[node].lnode, x, val);
        else
            tree[node].rnode = update(mid + 1, r, tree[node].rnode, x, val);
    }
    return node;
}
int query(int l, int r, int node, int pos)
{
    if (l == r)
        return tree[node].val;
    int mid = (l + r) >> 1;
    if (pos > mid)
        return query(mid + 1, r, tree[node].rnode, pos);
    else
        return query(l, mid, tree[node].lnode, pos);
}
int main()
{
    scanf("%d %d ", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    root[0] = build(1, n, 1);
    for (int i = 1; i <= m; i++)
    {
        int rt, mode, x, y;
        scanf("%d %d %d", &rt, &mode, &x);
        if (mode == 1)
        {
            scanf("%d", &y);
            root[i] = update(1, n, root[rt], x, y); //保存版本
        }
        else
        {
            printf("%d\n", query(1, n, root[rt], x)); //输出
            root[i] = root[rt];                       //新建版本
        }
    }
    return 0;
}