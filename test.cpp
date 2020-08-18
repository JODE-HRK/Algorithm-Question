/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-01 22:50:04
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-08-13 21:57:04
 */
#include <bits/stdc++.h>
#include <cstring>
#define ll long long
using namespace std;
string solve(string str)
{
	// write code here
	int l = str.length();
	if (l == 1)
		return str;
	string ans;
	char add;
	for (int i = 0; i < l; i++)
	{
		add = str[i];
		while (true)
		{
			if (ans.length() == 0)
			{
				ans += add;
				break;
			}
			if (ans[ans.length() - 1] == '0' && add == '0')
			{
				ans.pop_back();
				add = '1';
			}
			else if (ans[ans.length() - 1] == '1' && add == '1')
			{
				ans.pop_back();
				break;
			}
			else
				ans += add;
		}
	}
	return ans;
}
int main()
{
	solve("00110001");
	return 0;
}
