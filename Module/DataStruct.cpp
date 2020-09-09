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
伸展树解决区间问题
1 pos val：将val插入到pos位置
2 start end：将[start, end]之间的元素删除。
3 start end：返回[start, end]的区间和。
4 start end：返回[start, end]的区间最小值。
5 start end：返回[start, end]的区间最大值。
6 start end：将[start, end]区间翻转
7 start end delta：将[start, end]区间全部增加delta。
8 start end newValue：将[start, end]区间全部设置为newValue。
9 start end k：将[start, end]区间的元素循环右移k位。注意，如果k小于零，则是循环左移。
10 start end pos：将[start, end]区间移动到从pos开头的位置。
*/
struct Splay_Interval
{
    static const int SIZE = 200100;
    static const int LEFT = 0;
    static const int RIGHT = 1;
    struct Node
    {
        int parent;         //父节点
        int son[2];         //子节点
        int sn;             //本节点的排行
        int size;           //size域
        int value;          //值
        int peak;           //最大值
        int valley;         //最小值
        ll sum;             //和值，只有和值有可能超过int32
        int lazyd;          //delta的延迟标记和数值
        int lazys;          //set的延迟数值，为0不一定表示没有
        unsigned char flip; //第0位表示翻转的延迟标记，第1位表示set的延迟标记
    } node[SIZE];
    int toUsed = 0;
    inline void _pushUp(int t)
    {
        node[t].size = 1;
        node[t].sum = node[t].peak = node[t].valley = node[t].value;

        int son = node[t].son[LEFT];
        if (son)
        {
            node[t].size += node[son].size;
            node[t].sum += node[son].sum;
            node[t].peak = max(node[t].peak, node[son].peak);
            node[t].valley = min(node[t].valley, node[son].valley);
        }
        son = node[t].son[RIGHT];
        if (son)
        {
            node[t].size += node[son].size;
            node[t].sum += node[son].sum;
            node[t].peak = max(node[t].peak, node[son].peak);
            node[t].valley = min(node[t].valley, node[son].valley);
        }
    }
    inline void _pushDown(int t)
    {
        if (t && (node[t].flip & 1))
        { //首先处理翻转
            swap(node[t].son[LEFT], node[t].son[RIGHT]);

            int son = node[t].son[LEFT];
            if (son)
                node[son].sn = LEFT, node[son].flip ^= 1;

            son = node[t].son[RIGHT];
            if (son)
                node[son].sn = RIGHT, node[son].flip ^= 1;

            node[t].flip ^= 1;
        }
        if (t && (node[t].flip & 2))
        { //再处理set
            int &lazy = node[t].lazys;

            int son = node[t].son[LEFT];
            if (son)
            {
                node[son].flip |= 2; //打set延迟标记
                node[son].lazyd = 0;
                node[son].value = node[son].lazys = node[son].peak = node[son].valley = lazy;
                node[son].sum = (ll)lazy * (ll)node[son].size;
            }

            son = node[t].son[RIGHT];
            if (son)
            {
                node[son].flip |= 2; //打set延迟标记
                node[son].lazyd = 0;
                node[son].value = node[son].lazys = node[son].peak = node[son].valley = lazy;
                node[son].sum = (ll)lazy * (ll)node[son].size;
            }

            node[t].flip ^= 2; //清除set标记
        }
        if (t && node[t].lazyd)
        { //最后处理delta的
            int &lazy = node[t].lazyd;

            int son = node[t].son[LEFT];
            if (son)
            {
                node[son].value += lazy;
                node[son].lazyd += lazy;
                node[son].peak += lazy;
                node[son].valley += lazy;
                node[son].sum += (ll)lazy * (ll)node[son].size;
            }

            son = node[t].son[RIGHT];
            if (son)
            {
                node[son].value += lazy;
                node[son].lazyd += lazy;
                node[son].peak += lazy;
                node[son].valley += lazy;
                node[son].sum += (ll)lazy * (ll)node[son].size;
            }

            lazy = 0;
        }
    }
    //分配一个新节点
    inline int _newnode(int value = 0)
    {
        memset(node + (++toUsed), 0, sizeof(Node));
        //其他域不用管，在各自函数中处理
        node[toUsed].value = value;
        return toUsed;
    }
    //将parent的sn儿子设置为son
    inline void _link(int parent, int sn, int son)
    {
        node[son].parent = parent;
        node[son].sn = sn;
        node[parent].son[sn] = son;
    }
    //旋转操作,t不能是树根
    void _rotate(int t)
    {
        int p = node[t].parent;
        int sn = node[t].sn;
        int osn = sn ^ 1;
        //如果保证splay紧跟kth调用，则不需要pushDown
        //重新确定三对父子关系
        _link(p, sn, node[t].son[osn]);
        _link(node[p].parent, node[p].sn, t);
        _link(t, osn, p);
        //只维护p即可，t暂时不维护
        _pushUp(p);
    }
    //在root树中，将t伸展为p的儿子,p为0则伸展为树根
    void _splay(int &root, int p, int t)
    {
        int pp;
        while ((pp = node[t].parent) != p)
        {
            if (node[pp].parent != p)
                node[pp].sn == node[t].sn ? _rotate(pp) : _rotate(t);
            _rotate(t);
        }
        _pushUp(t); //最后维护t
        if (0 == p)
            root = t; //改根
    }
    //在t子树上查找第k个元素，从0开始，参数一定合法
    int _kth(int t, int k)
    {
        _pushDown(t);
        int son = node[t].son[LEFT];
        int s = son ? node[son].size : 0;
        if (k < s)
            return _kth(son, k); //去左子树找
        return s < k ? _kth(node[t].son[RIGHT], k - s - 1) : t;
    }
    //在第pos位置插入一个值value，参数一定合法，pos从1开始
    void insert(int &root, int pos, int const &value)
    {
        int t = _kth(root, pos - 1);
        _splay(root, 0, t); //将pos-1旋到树根
        int tt = _kth(root, pos);
        _splay(root, root, tt); //将pos旋到根的右儿子
        //把新节点挂到根的右儿子的左儿子
        t = _newnode(value);
        node[t].peak = node[t].valley = node[t].sum = value;
        node[t].size = 1;
        _link(tt, LEFT, t);
        _pushUp(tt);
        _pushUp(root);
    }
    //删除区间[s,e]，参数一定合法
    void remove(int &root, int s, int e)
    {
        int t = _kth(root, s - 1);
        _splay(root, 0, t);
        int tt = _kth(root, e + 1);
        _splay(root, root, tt);

        node[tt].son[LEFT] = 0;
        _pushUp(tt);
        _pushUp(root);
    }
    //[s,e]区间全部增加delta
    void modifyD(int &root, int s, int e, int const &delta)
    {
        int t = _kth(root, s - 1);
        _splay(root, 0, t);
        int tt = _kth(root, e + 1);
        _splay(root, root, tt);
        //根的左儿子的右儿子打标记
        int son = node[tt].son[LEFT];
        node[son].value += delta;
        node[son].peak += delta;
        node[son].valley += delta;
        node[son].sum += (ll)delta * (ll)node[son].size;
        node[son].lazyd += delta;
        _pushUp(tt);
        _pushUp(root);
    }
    //[s,e]区间全部设置为newValue
    void modifyS(int &root, int s, int e, int const &newValue)
    {
        int t = _kth(root, s - 1);
        _splay(root, 0, t);
        int tt = _kth(root, e + 1);
        _splay(root, root, tt);
        //根的左儿子的右儿子打标记
        int son = node[tt].son[LEFT];
        node[son].flip |= 2; //打set延迟标记
        node[son].value = node[son].peak = node[son].valley = node[son].lazys = newValue;
        node[son].sum = (ll)newValue * (ll)node[son].size;
        node[son].lazyd = 0;
        _pushUp(tt);
        _pushUp(root);
    }
    //[s,e]区间右移循环移位k
    void rotate(int &root, int s, int e, int k)
    {
        if (0 == (k %= (e - s + 1)))
            return;
        if (k < 0)
            k = e - s + 1 + k;
        //首先删除[e-k+1,e]
        int t = _kth(root, e - k);
        _splay(root, 0, t);
        int tt = _kth(root, e + 1);
        _splay(root, root, tt);
        int son = node[tt].son[LEFT];
        node[tt].son[LEFT] = 0;
        _pushUp(tt);
        _pushUp(root);
        //再把son插入到s位置
        t = _kth(root, s - 1);
        _splay(root, 0, t);
        tt = _kth(root, s);
        _splay(root, root, tt);
        _link(tt, LEFT, son);
        _pushUp(tt);
        _pushUp(root);
    }
    //[s,e]区间进行翻转
    void reverse(int &root, int s, int e)
    {
        int t = _kth(root, s - 1);
        _splay(root, 0, t);

        int tt = _kth(root, e + 1);
        _splay(root, root, tt);

        int ttt = node[tt].son[LEFT];
        node[ttt].flip ^= 1;
    }
    //将[s,e]区间移动到从pos位置开始
    void move(int &root, int s, int e, int pos)
    {
        int t = _kth(root, s - 1);
        _splay(root, 0, t);

        int tt = _kth(root, e + 1);
        _splay(root, root, tt);

        int son = node[tt].son[LEFT];
        node[tt].son[LEFT] = 0;
        _pushUp(tt);
        _pushUp(root);

        //找pos位置
        if (pos > e)
            pos -= e - s + 1;
        t = _kth(root, pos - 1);
        _splay(root, 0, t);

        tt = _kth(root, pos);
        _splay(root, root, tt);

        _link(tt, LEFT, son);
        _pushUp(tt);
        _pushUp(root);
    }
    ll sum(int &root, int s, int e)
    {
        int t = _kth(root, s - 1);
        _splay(root, 0, t);

        int tt = _kth(root, e + 1);
        _splay(root, root, tt);

        int son = node[tt].son[LEFT];
        return node[son].sum;
    }
    int Max(int &root, int s, int e)
    {
        int t = _kth(root, s - 1);
        _splay(root, 0, t);

        int tt = _kth(root, e + 1);
        _splay(root, root, tt);

        int son = node[tt].son[LEFT];
        return node[son].peak;
    }
    int Min(int &root, int s, int e)
    {
        int t = _kth(root, s - 1);
        _splay(root, 0, t);

        int tt = _kth(root, e + 1);
        _splay(root, root, tt);

        int son = node[tt].son[LEFT];
        return node[son].valley;
    }
    //利用全局数组建树
    void build(int &t, int parent, int sn, int s, int e, int const a[])
    {
        int mid = (s + e) >> 1;

        t = _newnode(a[mid]);
        node[t].parent = parent;
        node[t].sn = sn;

        if (s < mid)
            build(node[t].son[LEFT], t, LEFT, s, mid - 1, a);
        if (mid < e)
            build(node[t].son[RIGHT], t, RIGHT, mid + 1, e, a);

        _pushUp(t);
    }
    inline bool empty(int root)
    {
        return node[root].size <= 2;
    }
    inline int size(int root)
    {
        return node[root].size - 2;
    }
    int Root;
    int A[SIZE];
};
/*
线段树与扫描线
计算多个相交 的矩形覆盖的面积
以洛谷P5490为例
时间复杂度为nlogn
*/
struct Scan_Line
{
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
};
/*
回滚莫队
特征：其右端点呈不下降序列，左端点则位于同一个大小为N为√N的块内
常规的莫队算法弊端有很多，比如需要同时支持快速插入/删除一个值
而回滚莫队以解决一些只能支持插入，不能支持直接删除，但支持撤回操作的问题
回滚莫队，将问题的区间分为两个部分，一个在左端点的块内，另一个在左端点所在块的右边
撤回操作，将左端点块内的所有全部删除，在下一个问题时重新加入
*/
struct Roll_Back_Block
{
    int n, m;
    int mn1[maxn], mn2[maxn], mn3[maxn];
    int mx1[maxn], mx2[maxn], mx3[maxn];
    int res1, res2, res3;
    int ans[maxn];
    struct PRO
    {
        int l, r, id, blo;
    } pro[maxn];
    int a[maxn], cnt = 0, block;
    int posfr[maxn], posto[maxn];
    map<int, int> M;
    bool cmp(PRO a, PRO b)
    {
        return (a.blo != b.blo) ? a.l < b.l : a.r < b.r; //为了保证区间只增不减
    }                                                    //左端点在同一块就按照右端点小的排序，不在同一块就按照左端点小的排序
    int blo[maxn];
    void addL(int i)
    {
        mn2[a[i]] = min(mn2[a[i]], i);
        mx2[a[i]] = max(mx2[a[i]], i);
        res2 = max(res2, mx2[a[i]] - mn2[a[i]]);
    }
    void addR(int i)
    {
        mn2[a[i]] = mn1[a[i]] = min(mn1[a[i]], i);
        mx2[a[i]] = mx1[a[i]] = max(mx1[a[i]], i);
        res2 = res1 = max(res1, mx1[a[i]] - mn1[a[i]]);
    }
    void del(int i)
    {
        mn2[a[i]] = mn1[a[i]];
        mx2[a[i]] = mx1[a[i]];
        res2 = res1;
    }
    int main()
    {
        scanf("%d", &n);
        block = sqrt(n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
            if (!M[a[i]])
                M[a[i]] = ++cnt;
            a[i] = M[a[i]];
        } //离散化完毕
        // printf("CNT:%d\n", cnt);
        for (int i = 1; i <= n; i++)
            blo[i] = (i - 1) / block + 1;

        scanf("%d", &m);
        for (int i = 1; i <= m; i++)
            scanf("%d %d", &pro[i].l, &pro[i].r), pro[i].blo = (pro[i].l - 1) / block, pro[i].id = i;

        sort(pro + 1, pro + 1 + m, cmp); //问题排序完毕
        fill(mn1, mn1 + 1 + cnt, 0x7fffffff);
        fill(mn2, mn2 + 1 + cnt, 0x7fffffff);
        fill(mn3, mn3 + 1 + cnt, 0x7fffffff);
        fill(mx1, mx1 + 1 + cnt, 0);
        fill(mx2, mx2 + 1 + cnt, 0);
        fill(mx3, mx3 + 1 + cnt, 0);
        //初始化
        int nl = 1, nr = 0, nb = 0, nbr = 0; //nl和nr记录区间端点

        for (int i = 1; i <= m; i++)
        {
            int l = pro[i].l, r = pro[i].r;
            if (blo[r] - blo[l] < 1) //左右端点在同一个块的特殊处理
            {
                for (int j = l; j <= r; j++)
                {
                    mn3[a[j]] = min(mn3[a[j]], j);
                    mx3[a[j]] = max(mx3[a[j]], j);
                    res3 = max(res3, mx3[a[j]] - mn3[a[j]]);
                }
                ans[pro[i].id] = res3;
                for (int j = l; j <= r; j++)
                    mn3[a[j]] = 0x7fffffff, mx3[a[j]] = 0;
                res3 = 0;
                continue;
            }
            if (blo[l] != nb) //如果左端点换块了
            {
                for (int j = 1; j <= cnt; j++)
                {
                    mn1[j] = mn2[j] = 0x7fffffff;
                    mx1[j] = mx2[j] = 0;
                }
                res1 = res2 = 0;
                //全部预处理
                nb = blo[l];
                nbr = min(nb * block, n); //这是分界点
                nr = nbr;
                nl = nr + 1;
            }
            while (nr < r)
                addR(++nr);
            while (nl > l)
                addL(--nl);
            ans[pro[i].id] = res2;
            while (nl <= nbr) //撤回操作
                del(nl++);
            res2 = res1;
        }
        for (int i = 1; i <= m; i++)
            printf("%d\n", ans[i]);
        return 0;
    }
};