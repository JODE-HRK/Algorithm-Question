#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 7;

struct Definition
{
    int n, q, tot = 0;
    int a[maxn];
};
/*
主席树求区间不同树的个数
主席树每次修改和查询的时间复杂度都是O(logn)
*/
struct ChairmanTree_Different_numbers : Definition //区间不同数的个数
{                                                  //主席树支持在线做法
    //主席树空间很大，注意，并且有时候跑起来时间也很慢
    int cmtree[maxn], ls[maxn], rs[maxn], sum[maxn];
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
    int main()
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
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
        }
        scanf("%d", &q);
        while (q--)
        {
            int l, r;
            scanf("%d %d", &l, &r);
            if (l > r)
                swap(l, r);
            printf("%d\n", cmtreequery(1, n, cmtree[r], l, r));
        }
        return 0;
    }
};

/*
区间不同数的个数树状数组版
么此查询的时间复杂度为O(logn)
*/
struct Lowbit_Different_numbers : Definition //区间不同数的个数
{                                            //树状数组只能离线查询
    int a[maxn], last[maxn], ans[maxn], val[maxn];
    struct Query
    {
        int l, r, id;
        bool operator<(const Query &x)
        {
            return r < x.r;
        }
    } que[maxn];
    int lowbit(int x)
    {
        return x & (-x);
    }
    void add(int pos, int c)
    {
        while (pos <= n)
        {
            val[pos] += c;
            pos += lowbit(pos);
        }
    }
    int getsum(int pos)
    {
        int res = 0;
        while (pos)
        {
            res += val[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
    int main()
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        scanf("%d ", &q);
        for (int i = 1; i <= q; i++)
        {
            scanf("%d %d", &que[i].l, &que[i].r);
            que[i].id = i;
        }
        sort(que + 1, que + 1 + q);
        int pre = 0;
        for (int i = 1; i <= q; i++)
        {
            if (que[i].r > pre)
            {
                for (int j = pre + 1; j <= que[i].r; j++)
                {
                    if (last[a[j]])
                        add(last[a[j]], -1);
                    add(j, 1);
                    last[a[j]] = j; //此处如果数很大的话，可以离散化或者用map来记录上一次的位置
                    pre = que[i].r;
                }
            }
            ans[que[i].id] = getsum(que[i].r) - getsum(que[i].l - 1);
        }
        for (int i = 1; i <= q; i++)
            printf("%d\n", ans[i]);
        return 0;
    }
};

/*
分块算法，也称莫队算法，将数据分为sqrt(n)个部分，操作时对每个部分进行操作
时间复杂度 为O（n * sqrt(n)）
以牛客 名哥的完全平方数为例
完全平方数有个将所有数转换成所有数量为奇数的因数的积
*/
struct Block
{
    int n, block, q;
    int a[maxn];
    int cnt[3000000];
    int zans[maxn];
    struct PRO
    {
        int l, r, id, sp;
        bool operator<(const PRO x)
        {
            if (sp == x.sp)
                return r < x.r;
            return sp < x.sp;
        }
    } pro[maxn];
    inline int read()
    {
        char c = getchar();
        int x = 0, fh = 0;
        while (c < '0' || c > '9')
        {
            fh |= c == '-';
            c = getchar();
        }
        while (c >= '0' && c <= '9')
        {
            x = (x << 1) + (x << 3) + (c ^ 48);
            c = getchar();
        }
        return fh ? -x : x;
    }
    int getnum(int x)
    { //将x转换成所有数量为奇数个的因数的乘积
        int tmp = 1;
        for (int i = 2; i * i <= abs(x); i++)
        {
            while (x % (i * i) == 0)
                x /= (i * i);
        }
        return x / tmp;
    }
    int calc(int x)
    {
        return x * (x - 1) / 2;
    }
    void work(int &ans, int val, int pos, int &cnt0)
    {
        if (a[pos] == 0)
            cnt0 += val;
        else
        {
            ans -= calc(cnt[a[pos] + 1000000]);
            cnt[a[pos] + 1000000] += val;
            ans += calc(cnt[a[pos] + 1000000]);
        }
    }
    int main()
    {
        n = read();
        for (int i = 1; i <= n; i++)
            a[i] = read(), a[i] = getnum(a[i]), cnt[a[i]] = 0;
        block = sqrt(n);
        q = read();
        pro[0].l = pro[0].r = 0;
        for (int i = 1; i <= q; i++)
        {
            pro[i].l = read(), pro[i].r = read();
            pro[i].id = i;
            pro[i].sp = (pro[i].l - 1) / block + 1;
        }
        sort(pro + 1, pro + 1 + q);
        int l = 1, r = 0, ans = 0, cnt0 = 0;
        for (int i = 1; i <= q; i++)
        {
            while (l > pro[i].l)
                work(ans, 1, --l, cnt0);
            while (r < pro[i].r)
                work(ans, 1, ++r, cnt0);
            while (l < pro[i].l)
                work(ans, -1, l++, cnt0);
            while (r > pro[i].r)
                work(ans, -1, r--, cnt0);
            zans[pro[i].id] = ans + cnt0 * (r - l) - calc(cnt0);
        }
        for (int i = 1; i <= q; i++)
            printf("%d\n", zans[i]);
        return 0;
    }
};
/*
Splay 平衡二叉树的用法——该用法不常用，STL set可以支持查找插入
但是Splay支持前驱后继还有第k大
每次操作的时间复杂度都为O(logn)
下例以洛谷P6136 普通平衡树 数据加强版
题意是将所有答案都异或之后再输出
*/
struct Splay_AVL
{
#define inf 2000000000
    static int val[maxn], n, m, root; //此处的static是为了在这里不报错采写的

    struct SPLAY_TREE
    {
#define lson s[x].ch[0]
#define rson s[x].ch[1]
        struct data
        {
            int v, size, ch[2], f;
        } s[maxn * 10];
        int tot;
        inline int newnode() { return ++tot; }
        inline int get(int x) { return s[s[x].f].ch[1] == x; }
        inline void pushup(int x) { s[x].size = s[lson].size + s[rson].size + 1; }
        inline void rotate(int x)
        {
            int old = s[x].f, fold = s[old].f, which = get(x);
            s[old].ch[which] = s[x].ch[which ^ 1];
            if (s[old].ch[which])
                s[s[old].ch[which]].f = old;
            s[x].ch[which ^ 1] = old, s[old].f = x, s[x].f = fold;
            if (fold)
                s[fold].ch[s[fold].ch[1] == old] = x;
            pushup(old), pushup(x);
        }
        void splay(int x, int &tar)
        {
            for (int u = s[tar].f, fa; (fa = s[x].f) != u; rotate(x))
                if (s[fa].f != u)
                    rotate(get(fa) == get(x) ? fa : x);
            tar = x;
        }
        void build(int l, int r, int &x)
        { //如果一开始有数据，就建树，并且返回x（根）
            x = newnode();
            int mid = (l + r) >> 1;
            s[x].v = val[mid];
            if (mid > l)
                build(l, mid - 1, lson), s[lson].f = x;
            if (r > mid)
                build(mid + 1, r, rson), s[rson].f = x;
            pushup(x);
        }
        void ins(int &x, int fa, int v)
        {
            if (!x)
                x = newnode(), s[x].f = fa, s[x].v = v;
            else
                ins(s[x].ch[v > s[x].v], x, v);
            pushup(x);
        }
        int find(int x, int v)
        {
            if (s[x].v == v)
                return x;
            else
                return find(s[x].ch[v > s[x].v], v);
        }
        int getpre(int x, int v)
        {
            if (!x)
                return 0;
            if (s[x].v < v)
            {
                int a = x, b = getpre(rson, v);
                return b == 0 ? a : b;
            }
            else
                return getpre(lson, v);
        }
        int getaft(int x, int v)
        {
            if (!x)
                return 0;
            if (s[x].v > v)
            {
                int a = x, b = getaft(lson, v);
                return b == 0 ? a : b;
            }
            else
                return getaft(rson, v);
        }
        void del(int v)
        {
            int x = find(root, v), l, r;
            splay(x, root), l = lson, r = rson;
            while (s[l].ch[1])
                l = s[l].ch[1];
            splay(l, s[x].ch[0]);
            s[r].f = l, s[l].f = 0, s[l].ch[1] = r, pushup(l), root = l;
        }
        int getrank(int v)
        {
            int x = getpre(root, v);
            splay(x, root);
            return s[lson].size + 1;
        }
        int getnum(int x, int kth)
        {
            if (kth == s[lson].size + 1)
                return x;
            else if (kth <= s[lson].size)
                return getnum(lson, kth);
            else
                return getnum(rson, kth - s[lson].size - 1);
        }
    } bst;

    int main()
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &val[i]), bst;
        sort(val + 1, val + 1 + n);
        val[0] = -inf, val[1 + n] = inf;

        bst.build(0, 1 + n, root);
        int lastans = 0, op, x, y, ans = 0;
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d %d", &op, &x);
            x ^= lastans, y = 0;
            if (op == 1)
                bst.ins(root, 0, x), y = bst.tot; //插入
            else if (op == 2)
                bst.del(x); //删除
            else if (op == 3)
                lastans = bst.getrank(x), ans ^= lastans; //获得x的排名，为x小的树的个数+1
            else if (op == 4)
                y = bst.getnum(root, x + 1), lastans = bst.s[y].v, ans ^= lastans; //查询排名为x的树
            else if (op == 5)
                y = bst.getpre(root, x), lastans = bst.s[y].v, ans ^= lastans; //获得前驱
            else if (op == 6)
                y = bst.getaft(root, x), lastans = bst.s[y].v, ans ^= lastans; //获得后继
            if (y && (i % 10 == 0))                                            //10次操作后splay旋转一下
                bst.splay(y, root);
        }
        printf("%d\n", ans);
        return 0;
    }
};
/*
Splay 区间操作全集合

*/