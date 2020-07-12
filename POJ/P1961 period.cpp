#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int nxt[maxn], n;
void getnxt(string s)
{
    nxt[0] = -1;
    int i = 0, j = -1;
    while (i < n)
    {
        if (j == -1 || s[i] == s[j])
            nxt[++i] = ++j;
        else
            j = nxt[j];
    }
}
int main()
{
    int cnt = 0;
    string s;
    while (cin >> n)
    {
        if (n == 0)
            break;
        cin >> s;
        cout << "Test case #" << ++cnt << endl;
        getnxt(s);
        for (int i = 1; i <= n; i++)
            if (nxt[i] > 0 && i % (i - nxt[i]) == 0)
                cout << i << ' ' << i / (i - nxt[i]) << endl;
        cout << endl;
    }
    return 0;
}