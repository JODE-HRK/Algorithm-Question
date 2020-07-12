#include <bits/stdc++.h>
using namespace std;
string str;
int cnt[26], minn = 0x7fffffff, maxn = 0;
bool isprime(int x)
{
    if (x <= 1)
        return false;
    if (~x & 1 || x % 3 == 0)
        return x <= 3;
    for (int i = 5, j = 2; i * i <= x; i += j, j = j == 2 ? 4 : 2)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}
int main()
{
    memset(cnt, 0, sizeof(cnt));
    cin >> str;
    for (int i = 0; i < str.length(); i++)
        cnt[str[i] - 'a']++;
    for (int i = 0; i < 26; i++)
        if (cnt[i] > 0)
        {
            minn = min(minn, cnt[i]);
            maxn = max(maxn, cnt[i]);
        }
    int p = maxn - minn;
    if (isprime(p))
        printf("%s\n%d", "Lucky Word", p);
    else
        printf("%s\n%d", "No Answer", 0);
    return 0;
}