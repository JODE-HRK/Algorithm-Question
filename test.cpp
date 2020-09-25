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
	}
	return 0;
}