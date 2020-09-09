#include <bits/stdc++.h>
#define bit bitset<14>
using namespace std;
const int maxn = 1e5 + 7;
int n, m, k;
bit a[maxn];
int blo[maxn], block;
struct PRO
{
	int l, r, id;
} pro[maxn];

bool judge(bit x, bit y)
{
	bit z = x ^ y;
	if (z.count() == k)
		return 1;
	return 0;
}
bool cmp(PRO x, PRO y)
{
	return (blo[x.l] ^ blo[y.l]) ? x.l < y.l : x.r < y.r;
}
void pre()
{
	for (int i = 1; i <= n; i++)
		blo[i] = (i - 1) / block + 1;
	sort(pro + 1, pro + 1 + m, cmp);
	
}
int main()
{
	scanf("%d %d %d", &n, &m, &k);
	block = sqrt(n);
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		a[i] = (bit)x;
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d", &pro[i].l, &pro[i].r);
		pro[i].id = i;
	}
	pre();
	return 0;
}