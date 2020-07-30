#include <bits/stdc++.h>
using namespace std;
#define dir(a, b) (a >> b)
const int Max = 1e6 + 7;
int root[Max], tot, val[Max];
struct node
{
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
	return 0;
}