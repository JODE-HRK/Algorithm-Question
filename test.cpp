/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-12 09:21:54
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-17 20:52:13
 */
#include <bits/stdc++.h>
#define ll long long
#define inf 0x7fffffff
#define INF 1000000000000ll
#define pii pair<int, int>
#define pll pair<ll, ll>
const int maxn = 17;
const int mod = 998244353;
const int base = 127;
using namespace std;
vector<string> A;
string str;
int a[maxn], HASH[maxn], len, multi[maxn], sum[maxn];
int getAX(int lol, int l1, int l2)
{
	return HASH[lol];
}
int getXA(int lol, int l1, int l2)
{
	if (lol <= l2 - l1)
		return (HASH[l1 + lol] - HASH[l1] + mod) % mod;
	else
		return (((HASH[l2] - HASH[l1] + mod) % mod) * multi[lol - (l2 - l1)] % mod + HASH[lol - (l2 - l1)]) % mod;
}
bool cmp(int l1, int l2) //注意，重点在这，两字符串的比较方式
{
	int p = 0;
	if (l1 < l2)
		p = 1;
	else
		swap(l1, l2);
	int l = 1, r = max(l1, l2), mid;
	while (l < r)
	{
		mid = (l + r) >> 1;
		int AX = getAX(mid, l1, l2), XA = getXA(mid, l1, l2);
		if (AX == XA)
			l = mid;
		else
			r = mid;
	}
	return str[l] > str[l + l1] && p;
}
int main()
{
	cin >> str;
	len = str.length();
	HASH[0] = str[0] * base % mod;
	multi[0] = 1;
	a[0] = 1;
	sum[0] = str[0] - '0';
	for (int i = 1; i < len; i++)
	{
		HASH[i] = (HASH[i - 1] + str[i] * base % mod) % mod;
		multi[i] = multi[i - 1] * base % mod;
		sum[i] = (sum[i - 1] * 10 % mod + str[i] - '0') % mod;
		a[i] = i + 1;
	}
	sort(a, a + len, cmp);
	for (int i = 0; i < len; i++)
		cout << str.substr(0, a[i]) << endl;
	return 0;
}

/*
114514
*/