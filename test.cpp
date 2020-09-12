/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-09-11 19:12:21
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-09-11 20:26:25
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 7;
int n;
int a[maxn];
ll ans = 0;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	printf("%lld", ans);
	return 0;
}