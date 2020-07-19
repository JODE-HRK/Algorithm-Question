/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-16 15:48:25
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-16 16:22:53
 */
#include <bits/stdc++.h>
#define rep(i, x, y, z) for (register int i = (x); i <= (y); i += (z))
#define ll long long
#define inf 0x7fffffff
#define INF 1000000000000ll
#define pii pair<int, int>
#define pll pair<ll, ll>
const int maxn = 1e6 + 7;
using namespace std;
int n, k;
ll ans, f[maxn];
int head[maxn], date[maxn], nxt[maxn], tot = 0;
int lim[maxn], minn[maxn];
map<ll, int> M;
struct S
{
    int s[maxn];
    ll opt;
    friend bool operator==(S a, S b)
    {
        rep(i, 1, k, 1) if (a.s[i] != b.s[i]) return 0;
        return 1;
    }
} sum[maxn];
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
void build()
{
    fill(lim, lim + 1 + n, inf);
    rep(i, 1, m, 1)
    {
        memset(minn, 0x3f, sizeof(minn));
        for (int j = n; j; j--)
        {
            minn
        }
    }
}
int main()
{
    n = read(), k = read();
    rep(i, 1, n, 1)
    {
        string str;
        scanf("%s", str + 1);
        rep(j, 1, k, 1)
            sum[j]
                .s[i] = sum[j - 1].s[i] + (str[j] == ')' ? -1 : 1); //（为1，）为-1，计算前缀和
    }
    build();
    return 0;
}