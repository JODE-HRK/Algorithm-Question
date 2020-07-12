#include <bits/stdc++.h>
#define ll long long
using namespace std;
string origin, aimstr;
ll dp[2001][2001];
ll func(int i, int j)
{
    if (dp[i][j] != -1)
        return dp[i][j]; //避免重复求解
    if (i == 0 || j == 0)
        return dp[i][j] = max(i, j);    //当有一边遍历完的时候，剩下的要么全部删除，要么全部添加
    int s = 1;                          //当前是否需要增加一次操作
    if (origin[i - 1] == aimstr[j - 1]) //相同的话就不用操作了
        s = 0;
    return dp[i][j] = min(min(func(i - 1, j) + 1, func(i, j - 1) + 1), func(i - 1, j - 1) + s);
    //分别对应            删除当前串的该字符        添加目标串的字符        修改当前串的字符
}
int main()
{
    memset(dp, -1, sizeof(dp));
    cin >> origin >> aimstr;
    int l1 = origin.length(), l2 = aimstr.length();
    func(l1, l2);
    printf("%lld", dp[l1][l2]);
    return 0;
}