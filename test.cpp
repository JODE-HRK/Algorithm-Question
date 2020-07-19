/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-13 21:35:45
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-18 15:20:21
 */
#include <bits/stdc++.h>
#define ll long long
#define inf 0x7fffffff
#define INF 1000000000000ll
#define pii pair<int, int>
#define pll pair<ll, ll>
const int maxn = 1e6 + 7;
using namespace std;
inline int read()
{
	int x = 0;
	char c = getchar();
	while (c > '9' || c < '0')
		c = getchar();
	while (c >= '0' && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x;
}
int n, m;
int head[maxn], tot, fa[maxn];
queue<int> Q[maxn];
struct Edge
{
	int fr, to, nxt;
} edge[maxn];
void init()
{
	tot = 0;
	fill(head, head + 1 + n, -1);
	for (int i = 0; i < n; i++)
		fa[i] = i, Q[i].push(i);
}
void addEdge(int x, int y)
{
	edge[tot] = (Edge){x, y, head[x]};
	head[x] = tot++;
}
int fdfa(int x)
{
	return fa[x] == x ? x : fa[x] = fdfa(fa[x]);
}
void add(int now)
{
	for (int i = head[now]; ~i; i = edge[i].nxt)
	{
		int tto = edge[i].to;
		fa[fdfa(tto)] = now;
		Q[now].push(tto);
	}
}
int main()
{
	// freopen(".in", "r", stdin);
	int t;
	t = read();
	while (t--)
	{
		n = read(), m = read();
		init();
		for (int i = 1; i <= m; i++)
		{
			int x, y;
			x = read(), y = read();
			addEdge(x, y);
			addEdge(y, x);
		}
		int q;
		q = read();
		while (q--)
		{
			int o;
			o = read();
			int f = fdfa(o);
			int s = Q[f].size();
			while (s--)
			{
				int x = Q[f].front();
				Q[f].pop();
				add(f);
			}
		}
		for (int i = 0; i < n; i++)
			printf("%d ", fdfa(i));
		cout << endl;
	}
	return 0;
}
/*

*/