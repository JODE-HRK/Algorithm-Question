#include <bits/stdc++.h>
using namespace std;
const int maxn = 26;
int last[maxn], cnt[maxn];
string str;
int main()
{
    getline(cin, str);
    int l = str.length(), len = 0, ans = 0, st = 0;
    memset(last, 0, sizeof(last));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < l; i++)
    {
        int id = str[i];
        if (!cnt[id])
            len++, cnt[id] = 1, last[id] = i;
        else
        {

            ans = max(ans, len);
            if (last[id] >= st)
            {
                len = i - last[id];
                st = last[id] + 1;
            }
            else
                ++len;
            last[id] = i;
        }
        // cout << len << endl;
    }
    ans = max(ans, len);
    printf("%d", ans);
    return 0;
}
