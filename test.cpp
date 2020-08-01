/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-13 21:35:45
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-30 21:02:15
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
	return 0;
}