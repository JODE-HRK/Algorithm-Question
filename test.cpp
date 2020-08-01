<<<<<<< HEAD
/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-13 21:35:45
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-30 21:02:15
 */
=======
>>>>>>> f3fd234286a3d85a228852b4228820f412d29d3b
#include <bits/stdc++.h>
using namespace std;
#define dir(a, b) (a >> b)
const int Max = 1e6 + 7;
int root[Max], tot, val[Max];
struct node
{
<<<<<<< HEAD
	int x = 0;
	char c = getchar();
	while (c > '9' || c < '0')
		c = getchar();
	while (c >= '0' && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x;
}
int n;
int a[maxn];
struct Node
{
	int s, id;
} b[maxn];
bool cmp(Node x, Node y)
{
	return x.s > y.s;
}
int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
		a[i] = read(), b[i].id = i, b[i].id = a[i];
	sort(b + 1, b + 1 + n, cmp);
=======
	int lef, rig, sum;
} msegtr[Max * 40];
map<int, int> mp;
void Init()
{
	tot = 0;
	msegtr[0].lef = msegtr[0].rig = msegtr[0].sum = 0;
	root[0] = 0;
	mp.clear();
	return;
}
void Create(int sta, int enn, int &x, int y, int pos, int aad)
{
	msegtr[++tot] = msegtr[y];
	msegtr[tot].sum += aad;
	x = tot;
	if (sta == enn)
		return;
	int mid = dir(sta + enn, 1);
	if (mid >= pos)
		Create(sta, mid, msegtr[x].lef, msegtr[y].lef, pos, aad);
	else
		Create(mid + 1, enn, msegtr[x].rig, msegtr[y].rig, pos, aad);
	return;
}
int Query(int sta, int enn, int x, int y) //只有左边有界限
{
	if (sta >= y)
		return msegtr[x].sum;
	int mid = dir(sta + enn, 1);
	if (mid >= y)
		return Query(sta, mid, msegtr[x].lef, y) + msegtr[msegtr[x].rig].sum;
	else
		return Query(mid + 1, enn, msegtr[x].rig, y);
}
int main()
{
	int n, m, temp;
	int lef, rig;
	while (~scanf("%d", &n))
	{
		Init();
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", &val[i]);
			if (!mp.count(val[i])) //直接加
			{
				Create(1, n, root[i], root[i - 1], i, 1); //注意是在i这个位置加1，不是权值线段树的val[i]位置加1
			}
			else
			{
				Create(1, n, temp, root[i - 1], mp[val[i]], -1); //先在原位置减去1
				Create(1, n, root[i], temp, i, 1);
			}
			mp[val[i]] = i;
		}
		scanf("%d", &m);
		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d", &lef, &rig);
			printf("%d\n", Query(1, n, root[rig], lef)); //在rig的历史版本上找(lef,rig)的值
		}
	}
>>>>>>> f3fd234286a3d85a228852b4228820f412d29d3b
	return 0;
}