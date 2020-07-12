#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int n, m, c;
char a, b;
char str[maxn];
int s[maxn];
int f[26][26], d[26][26], pre[26][maxn];
void floyd()
{
    for (int k = 0; k < 26; k++)
        for (int i = 0; i < 26; i++)
            for (int j = 0; j < 26; j++)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    for (int k = 0; k < 26; k++)
        for (int i = 0; i < 26; i++)
            for (int j = 0; j < 26; j++)
                d[i][j] = min(d[i][j], f[i][k] + f[j][k]); //d表示i,j变成相同的最小费用，重要。。想不到啊
}
int main()
{
    scanf("%d %d", &n, &m);
    scanf("%s", str + 1);
    for (int i = 0; i <= n; i++)
        s[i] = str[i] - 'a';
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            d[i][j] = f[i][j] = 100000007;
    for (int i = 0; i < 26; i++)
        d[i][i] = f[i][i] = 0;
    for (int i = 1; i <= m; i++)
    {
        scanf(" %c %c %d", &a, &b, &c);
        f[a - 'a'][b - 'a'] = min(f[a - 'a'][b - 'a'], c);
    }
    floyd(); //floyd计算字符间转换的最小费用
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 26; j++)
            pre[j][i] = pre[j][i - 1];
        pre[s[i]][i]++; //记录每个字符的前缀和
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        if (n - i + 1 >= i) //代表在整个字符串对称轴左边
            for (int j = 0; j < 26; j++)
                ans += (long long)(pre[j][n - i + 1] - pre[j][i - 1]) * d[s[i]][j] * i;
        else //在右边
            for (int j = 0; j < 26; j++)
                ans += (long long)(pre[j][i] - pre[j][n - i + 2 - 1]) * d[s[i]][j] * (n - i + 1);
    printf("%lld", ans);
    return 0;
}