#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    int k;
    cin >> s >> k;
    string ans;
    while (k)
    {
        int pos = 0;
        for (int i = 1; i <= k; i++)
            if (s[i] < s[pos])
                pos = i;
        ans += s[pos];
        s.erase(0, pos + 1);
        k -= pos;
    }
    ans += s;
    while (ans[0] == '0')
        ans.erase(0, 1);
    if (ans.size() > 0)
        cout << ans;
    else
        cout << '0';
    return 0;
}