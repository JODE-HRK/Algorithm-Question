#include <bits/stdc++.h>
using namespace std;
set<string> S;
int dp[20000001];
int maxl = 0;
string s;
int main()
{
    // freopen(".in", "r", stdin);
    while (cin >> s)
    {
        if (s == ".")
            break;
        // cout << s << endl;
        S.insert(s);
        maxl = max(maxl, (int)s.length());
    }
    string str;
    str = " ";
    while (cin >> s)
        str += s;
    int ans = -1;
    dp[0] = 1;
    for (int i = 1; i < str.size(); i++)
        for (int j = min(i, maxl); j >= 1; j--)
        {
            string ts = str.substr(i - j + 1, j);
            // cout << ts << endl;
            if (S.count(ts) == 1 && dp[i - j] == 1)
            {
                dp[i] = 1;
                ans = i;
                break;
            }
        }
    printf("%d", max(ans, 0));
    return 0;
}