<<<<<<< HEAD
#include <bits/stdc++.h>
=======
<<<<<<< HEAD
/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-09-11 19:12:21
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-09-15 17:17:59
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 7;
int n;
int a[maxn];
int cnt, lastcnt;
string str;
int main()
{
	scanf("%d", &n);
	while (n--)
	{
		cin >> str;
		lastcnt = 0;
		cnt = 1;
		int l = str.length();
		if (l == 0)
		{
			cout << endl;
			continue;
		}
		string ans;
		ans = "";
		ans += str[0];
		for (int i = 1; i < l; i++)
		{
			if (str[i] == str[i - 1])
			{
				++cnt;
			}
			else
			{
				lastcnt = cnt;
				cnt = 1;
			}
			if (cnt == 3)
			{
				cnt--;
			}
			else if (lastcnt == 2 && cnt == 2)
			{
				cnt--;
			}
			else
			{
				ans += str[i];
			}
		}
		cout << ans << endl;	
=======
<<<<<<< HEAD
=======
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>
>>>>>>> 5d6fbdb46ed2fbb3fe61d964965b9fc622d18146
using namespace std;
int n, k;
int dp[1010][1010];
bool judge(int col, int row, int i, int j)
{
	if (col & i == 0 && row & j == 0)
		return 1;
	return 0;
}
int main()
{
	scanf("%d %d", &n, &k);
	int state = (1 << n), ans = 0;
	memset(dp, 0, sizeof(dp));
	for (int col = 0; col < state; col++)
	{
		for (int row = 0; row < state; row++)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
					if (judge(col, row, i, j))
					{
						int ccol, rrow;
						ccol = col | i | max(i - 1, 0) | min(i + 1, n - 1);
						rrow = row | i | max(i - 1, 0) | min(i + 1, n - 1);
						dp[ccol][rrow] = max(dp[ccol][rrow], dp[col][row] + 1);
						if (dp[ccol][rrow] == k)
							ans++;
					}
			}
		}
>>>>>>> 21e5d29df6664aa0d801d89bbe6004c6b2f2360a
	}
	printf("%d", ans);
	return 0;
}