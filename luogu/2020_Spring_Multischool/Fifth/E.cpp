#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 7;
int n, m;
int a[maxn], b[maxn];
int tree[maxn << 2], tl[maxn << 2], tr[maxn << 2], nxl[maxn << 2], nxr[maxn << 2];
int pd[maxn << 2];
bool pl[maxn << 2], pr[maxn << 2];
void pdown(int node, int l, int r)
{
    tree[node] = max(pd[node >> 1], node % 2 ? nxr[node >> 1] - (r - l + 1) : tree[node >> 1]);
    tl[node] = max(tl[node >> 1], tl[node]);
    tr[node] = max(tr[node >> 1 | 1], tr[node]);
    nxl[node] = max(nxl[node >> 1 | 1], nxl[node]);
    nxr[node] = max(nxr[node >> 1], nxr[node]);
    if (!pl[node])
        nxl[node] = max(tl[node + 1] - 1, nxl[node]);
    if (!pr[node])
        nxr[node] = max(tr[node - 1] - 1, nxr[node]);
    tree[node] = max(tree[node], max(nxl[node], nxr[node]));
}
void change(int l, int r, int node, int le, int ri, int cc)
{
    pdown(node, l, r);
    if (r < le || l > ri)
        return;
    if (le <= l && r <= ri)
    {
        pd[node] = max(pd[node], cc);
        tree[node] = max(max(tree[node], cc), max(nxl[node], nxr[node]));
        tl[node] = max(max(tl[node], cc), nxl[node] - (r - l + 1));
        tr[node] = max(max(tr[node], cc), nxr[node] - (r - l + 1));
        return;
    }
    int mid = (l + r) >> 1;
    change(l, mid, node << 1, le, ri, cc);
    change(mid + 1, r, node << 1 | 1, le, ri, cc);
    tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
    tl[node] = max(max(tl[node << 1], tl[node]), tl[node << 1 | 1] - (mid - l + 1));
    tr[node] = max(max(tr[node << 1 | 1], tr[node]), tr[node << 1] - (r - mid));
    if (!pl[node])
        nxr[node - 1] = max(nxr[node - 1], tl[node]);
    if (!pr[node])
        nxl[node + 1] = max(nxl[node + 1], tr[node]);
}
int fd(int l, int r, int node, int le, int ri)
{
    pdown(node);
    if (r < le || l > ri)
        return 0;
    if (l >= le && r <= ri)
        return tree[node];
    int mid = (l + r) >> 1, ans = 0;
    ans = fd(l, mid, node << 1, le, ri);
    ans = max(ans, fd(mid + 1, r, node << 1 | 1, le, ri));
    return ans;
}
void pre()
{
    memset(pl, 0, sizeof(pl));
    memset(pr, 0, sizeof(pr));
    int sum = 1;
    pl[1] = pr[1] = 1;
    for (int i = 1; i <= 21; i++)
    {
        if (sum >= maxn << 2)
            break;
        pl[sum] = 1;
        pr[sum - 1] = 1;
        sum *= 2;
    }
}
int main()
{
    pre();
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int id, a, b, c;
        scanf("%d", &id);
        if (id == 1)
        {
            scanf("%d %d %d", &a, &b, &c);
            change(1, n, 1, a, b, c);
        }
        else
        {
            scanf("%d %d", &a, &b);
            printf("%d\n", fd(1, n, 1, a, b));
        }
    }
    return 0;
}