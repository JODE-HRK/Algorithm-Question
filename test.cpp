#include <bits/stdc++.h>
#define ll long long
const int maxn = 1e6 + 7;
using namespace std;
#define inf 2000000000
int val[maxn], n, m, root; //此处的static是为了在这里不报错采写的
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
int pos[maxn], c[maxn];
int lowbit(int x)
{
	return x & (-x);
}
void add(int pos, int x)
{
	while (pos <= n)
	{
		c[pos] += x;
		pos += lowbit(pos);
	}
}
int getsum(int pos)
{
	int res = 0;
	while (pos)
	{
		res += c[pos];
		pos -= lowbit(pos);
	}
	return res;
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &val[i]), add(i, 1);
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
		if (y && (i % 10 == 0))											   //10次操作后splay旋转一下
			bst.splay(y, root);
	}
	printf("%d\n", ans);
	return 0;
}