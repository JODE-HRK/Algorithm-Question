<<<<<<< HEAD
=======
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
struct node
{
	int from;
	int to;
	int w;
	int next;
} e[150 * 150 * 150];
int a[150][150];
int b[150][150];
int divv[150 * 150];
int cur[150 * 150];
int head[150 * 150];
int n, t, ss, tt, cont;
void add(int from, int to, int w)
{
	e[cont].to = to;
	e[cont].w = w;
	e[cont].next = head[from];
	head[from] = cont++;
}
void Getmap()
{
	cont = 0;
	ss = n * n * 2 + 1;
	tt = ss + 1;
	memset(head, -1, sizeof(head));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] > 0)
			{
				add(ss, i * n + j + 1, a[i][j]);
				add(i * n + j + 1, ss, 0);
			}
			if (b[i][j] > 0)
			{
				add(n * n + i * n + j + 1, tt, b[i][j]);
				add(tt, n * n + i * n + j + 1, 0);
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] > 0)
			{
				for (int k = 0; k < n; k++)
				{
					for (int l = 0; l < n; l++)
					{
						if (b[k][l] > 0)
						{
							int u = i * n + j + 1;
							int v = n * n + k * n + l + 1;
							if (abs(i - k) + abs(j - l) <= t)
							{
								add(u, v, 0x3f3f3f3f);
								add(v, u, 0);
							}
						}
					}
				}
			}
		}
	}
}
int makedivv()
{
	memset(divv, 0, sizeof(divv));
	divv[ss] = 1;
	queue<int> s;
	s.push(ss);
	while (!s.empty())
	{
		int u = s.front();
		if (tt == u)
			return 1;
		s.pop();
		for (int i = head[u]; i != -1; i = e[i].next)
		{
			int v = e[i].to;
			int w = e[i].w;
			if (w && divv[v] == 0)
			{
				divv[v] = divv[u] + 1;
				s.push(v);
			}
		}
	}
	return 0;
}
int Dfs(int u, int maxflow, int tt)
{
	if (u == tt)
		return maxflow;
	int ret = 0;
	for (int &i = cur[u]; i != -1; i = e[i].next)
	{
		int v = e[i].to;
		int w = e[i].w;
		if (w && divv[v] == divv[u] + 1)
		{
			int f = Dfs(v, min(maxflow - ret, w), tt);
			e[i].w -= f;
			e[i ^ 1].w += f;
			ret += f;
			if (ret == maxflow)
				return ret;
		}
	}
	return ret;
}
void Dinic()
{
	int ans = 0;
	while (makedivv() == 1)
	{
		memcpy(cur, head, sizeof(head));
		ans += Dfs(ss, 0x3f3f3f3f, tt);
	}
	printf("%d\n", ans);
}
int main()
{
	while (~scanf("%d%d", &n, &t))
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				scanf("%d", &a[i][j]);
			}
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				scanf("%d", &b[i][j]);
			}
		}
		Getmap();
		Dinic();
	}
}
>>>>>>> 74c66ff6cc0e240f68f5a95a9d063118fd9f52b4
