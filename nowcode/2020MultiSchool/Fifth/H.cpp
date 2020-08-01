#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 7;
int n, q, lastans = 0, tot = 0;
int a[maxn], tree[maxn << 4];
int cmtree[maxn], ls[maxn << 9], rs[maxn << 9], sum[maxn << 9];
unordered_map<int, int> pre; //相对于map来说，元素无序，但查找迅速O(1)
void update(int l, int r, int node, int last, int p, int v)
{
    ls[node] = ls[last], rs[node] = rs[last];
    sum[node] = sum[last] + v;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (mid >= p)
        update(l, mid, ls[node] = ++tot, ls[last], p, v);
    else
        update(mid + 1, r, rs[node] = ++tot, rs[last], p, v);
}
int cmtreequery(int l, int r, int node, int ql, int qr)
{
    if (l >= ql && r <= qr)
        return sum[node];
    int mid = (l + r) >> 1;
    int ans = 0;
    if (mid >= ql)
        ans = cmtreequery(l, mid, ls[node], ql, qr);
    if (mid < qr)
        ans += cmtreequery(mid + 1, r, rs[node], ql, qr);
    return ans;
}
void build(int l, int r, int node)
{
    if (l == r)
    {
        tree[node] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, node << 1);
    build(mid + 1, r, node << 1 | 1);
    tree[node] = tree[node << 1] & tree[node << 1 | 1]; //记录所有区间与在一起的值
}
int query(int l, int r, int node, int ql, int qr)
{
    if (l >= ql && r <= qr)
        return tree[node];
    int mid = (l + r) >> 1, ans = (1 << 30) - 1;
    if (mid >= ql)
        ans &= query(l, mid, node << 1, ql, qr);
    if (mid < qr)
        ans &= query(mid + 1, r, node << 1 | 1, ql, qr);
    return ans;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    build(1, n, 1); //对于固定的左端点或者右端点，不同的值至多只有log个
    //单纯的线段树就是记录每一段区间的与和
    for (int i = 1; i <= n; i++)
    {
        if (pre[a[i]]) //如果这个数之前查过了，对上一个该数的位置进行-1更新
        {
            update(1, n, cmtree[i] = ++tot, cmtree[i - 1], pre[a[i]], -1);
            int now = ++tot;
            update(1, n, now, cmtree[i], i, 1);
            cmtree[i] = now;
        }
        else
            update(1, n, cmtree[i] = ++tot, cmtree[i - 1], i, 1);
        pre[a[i]] = i;
        //上面这一段与求区间不同数的个数相同
        int v = a[i], p = i;
        for (int j = 30; j; j--) //int只有31位
        {
            int l = 1, r = p - 1, mid, ans = 0;
            while (r >= l)
            {
                mid = (l + r) >> 1;
                if (query(1, n, 1, mid, i) < v)
                    ans = mid, l = mid + 1;
                else
                    r = mid - 1;
            }
            if (!ans)
                break;
            //因为与和只有可能变小，所以上面这个二分找的是最近的一个区间得到不同的数的位置
            //如果找不到就可以退出了，因为不会再有新的数了
            v = query(1, n, 1, ans, i); //求这段区间的与和再次对该位置进行添加和删除操作
            p = ans;
            int now;
            if (pre[v])
            {
                now = ++tot;
                update(1, n, now, cmtree[i], pre[v], -1);
                cmtree[i] = now;
            }
            now = ++tot;
            update(1, n, now, cmtree[i], p, 1);
            cmtree[i] = now;
            pre[v] = p;
        }
    }

    scanf("%d", &q);
    while (q--)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        l = (l ^ lastans) % n + 1;
        r = (r ^ lastans) % n + 1;
        if (l > r)
            swap(l, r);
        printf("%d\n", lastans = cmtreequery(1, n, cmtree[r], l, r));
    }
    return 0;
}