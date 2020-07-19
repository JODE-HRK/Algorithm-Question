/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-12 09:21:54
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-17 21:18:32
 */
#include <bits/stdc++.h>
#define ll long long
#define inf 0x7fffffff
#define INF 1000000000000ll
#define pii pair<int, int>
#define pll pair<ll, ll>
const int maxn = 1e6 + 7;
const int mod = 998244353;
using namespace std;
vector<string> A;
string str;
bool cmp(const int &l1, const int &l2) //注意，重点在这，两字符串的比较方式
{
    string str1 = str.substr(0, l1), str2 = str.substr(0, l2);
    return str1 + str2 > str2 + str1 ? true : false;
}
int a[maxn];
ll b[maxn];
int main()
{
    // printf("%d\n", 1ll * 3313123312 % mod);
    cin >> str;
    int len = str.length();
    b[0] = 1;
    for (int i = 1; i <= len; i++)
        b[i] = b[i - 1] * 10 % mod, a[i - 1] = i;
    sort(a, a + len, cmp);
    ll sum = 0, multi = 1;
    for (int i = len - 1; i >= 0; i--)
    {
        string ss = str.substr(0, a[i]);
        cout << ss << endl;
        sum = (sum % mod + atoll(ss.c_str()) % mod * multi % mod) % mod;
        multi = multi * b[a[i]] % mod;
    }
    printf("%lld", sum);
    return 0;
}