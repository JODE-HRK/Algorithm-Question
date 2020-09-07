#include <bits/stdc++.h>
using namespace std;
int n, m;
int ans;
const int maxn = 2e5 + 7;
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
	return (a.blo ^ b.blo) ? a.l < b.l : a.r < b.r; //为了保证区间只增不减
}
int blo[maxn];
int main()
{
	scanf("%d %d", &n, &m);
	block = sqrt(n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		if (!M[a[i]])
			M[a[i]] = ++cnt;
		a[i] = M[a[i]];
	} //离散化完毕
	for (int i = 1; i <= n; i++)
		blo[i] = (i - 1) / block + 1;
	for (int i = 1; i <= m; i++)
		scanf("%d %d", &pro[i].l, &pro[i].r), pro[i].blo = (pro[i].l - 1) / block, pro[i].id = i;
	sort(pro + 1, pro + 1 + m, cmp); //问题排序完毕
	fill(mn1, mn1 + 1 + cnt, 0x7fffffff);
	fill(mn2, mn2 + 1 + cnt, 0x7fffffff);
	fill(mn3, mn3 + 1 + cnt, 0x7fffffff);
	for (int i = 1; i <= m; i++)
	{
		int l = pro[i].l, r = pro[i].r;
		if (blo[r] - blo[l] < 2)
		{
			for (int j = l; j <= r; j++)
			{
				mn3[a[j]] = min(mn3[a[j]], j);
				mx3[a[j]] = max(mx3[a[j]], j);
				res3 = max(res3, mx3[a[j]]);
			}
			ans[pro[i].id] = res3;
			for (int j = l; j <= r; j++)
				mn3[a[j]] = 0x7fffffff, mx3[a[j]] = 0;
			res3 = 0;
			continue;
		}
	}
	return 0;
}