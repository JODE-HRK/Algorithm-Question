#include <bits/stdc++.h>
using namespace std;
int n[2], cnt = 0;
string s;
int main()
{
    cin >> s;
    int p = 0, sp;
    n[0] = n[1] = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '<')
            p = 1, cnt++;
        if (s[i] == '>')
            p = 2, cnt++;
        if (s[i] == '+')
            sp = -1;
        if (s[i] == '-')
            sp = 1;
        if (s[i] >= '0' && s[i] <= '9')
            n[cnt] = n[cnt] * 10 + s[i] - '0';
    }
    long long ans = 0;
    if (p == 2)
        ans = 0x7fffffff - 1ll * n[1];
    else
        ans = 1ll * 0x7fffffff + 1ll * n[1] + 1;

    printf("%lld", ans);
    return 0;
}