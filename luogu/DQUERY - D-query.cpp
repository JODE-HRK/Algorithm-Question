/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-31 20:40:32
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-08-31 21:21:28
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e6 + 7;
int n, m, last[maxn], root[maxn], cnt = 0;
struct Tree
{
    int l, r, s;
} tree[maxn * 32];
int build(int l, int r)
{
    int newnode = ++cnt;
    tree[newnode].s = 0;
    if (l == r)
        return newnode;
    int mid = (l + r) >> 1;
    tree[newnode].l = build(l, mid);
    tree[newnode].r = build(mid + 1, r);
}
int insert(int pos, int node, int l, int r)
{
    int newnode = ++cnt;
    tree[newnode] = tree[node];
    if (l == r)
    {
        tree[newnode].s++;
        return newnode;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        tree[newnode].l = insert(pos, tree[node].l, l, mid);
    else
        tree[newnode].r = insert(pos, tree[node].r, mid + 1, r);
    tree[newnode].s = tree[tree[newnode].l].s + tree[tree[newnode].r].s;
    return newnode;
}
int query(int L, int R, int l, int r, int node1, int node2)
{
    if (r < L || l > R)
        return 0;
    if (l >= L && r <= R)
        return tree[node2].s - tree[node1].s;
    int mid = (l + r) >> 1;
    int ans = query(L, R, l, mid, tree[node1].l, tree[node2].l) + query(L, R, mid + 1, r, tree[node1].r, tree[node2].r);
    return ans;
}
int main()
{
    scanf("%d", &n);
    root[0] = build(1, n);
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        root[i] = insert(last[x] + 1, root[i - 1], 1, n);
        last[x] = i;
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", query(1, l, 1, n, root[l - 1], root[r]));
    }
    return 0;
}