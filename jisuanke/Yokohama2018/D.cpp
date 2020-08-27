/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-18 23:21:32
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-08-21 11:12:13
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 4e3 + 7;
int nxts[maxn][2], lens;
int nxtstr[maxn][2], lenstr;
char s[maxn], str[maxn];
int dp[maxn][maxn], fa[maxn][maxn];
int dfs(int x, int y)
{
    if (x == lenstr + 1 && y == lens + 1)
        return 0;
    if (dp[x][y])
        return dp[x][y];
    int t1 = dfs(nxtstr[x][0], nxts[y][0]);
    int t2 = dfs(nxtstr[x][1], nxts[y][1]);
    if (t1 <= t2)
        fa[x][y] = 0;
    else
        fa[x][y] = 1;
    return dp[x][y] = min(t1, t2) + 1;
}
void getans(int x, int y)
{
    if (x == lenstr + 1 && y == lens + 1)
        return;
    int res = fa[x][y] > 0;
    printf("%d", res);
    getans(nxtstr[x][res], nxts[y][res]);
    return;
}
int main()
{
    scanf("%s", str + 1);
    scanf("%s", s + 1);
    lens = strlen(s + 1);
    lenstr = strlen(str + 1);
    nxts[lens + 1][0] = nxts[lens + 1][1] = lens + 1;
    nxtstr[lenstr + 1][0] = nxtstr[lenstr + 1][1] = lenstr + 1;
    for (int i = lens; i >= 0; --i)
    {
        nxts[i][1] = nxts[i + 1][1];
        nxts[i][0] = nxts[i + 1][0];
        if (s[i + 1] == '1')
            nxts[i][1] = i + 1;
        else
            nxts[i][0] = i + 1;
    }
    for (int i = lenstr; i >= 0; --i)
    {
        nxtstr[i][1] = nxtstr[i + 1][1];
        nxtstr[i][0] = nxtstr[i + 1][0];
        if (str[i + 1] == '1')
            nxtstr[i][1] = i + 1;
        else
            nxtstr[i][0] = i + 1;
    }
    dfs(0, 0);
    // printf("YES\n");
    getans(0, 0);
    return 0;
}