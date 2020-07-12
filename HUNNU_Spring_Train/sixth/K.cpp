#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
int cnt[26], tp[26], pos;
string str[30], s;
int n;
bool judge(int id)
{
    fill(cnt, cnt + 26, 0);
    for (int i = 0; i < str[id].length(); i++)
        cnt[int(str[id][i] - 'A')]++;
    for (int i = 1; i <= n; i++)
        if (i != id)
        {
            int p = 0;
            copy(cnt, cnt + 26, tp);
            for (int j = 0; j < str[i].length(); j++)
                tp[str[i][j] - 'A']--;
            for (int j = 0; j < str[i].length(); j++)
                if (tp[str[i][j] - 'A'] != 0)
                    p = 1;
            if (!p)
                return 0;
        }
    return 1;
}
char getans(int id1, int id2)
{
    char st;
    fill(cnt, cnt + 26, 0);
    for (int i = 0; i < str[id1].length(); i++)
        cnt[str[id1][i] - 'A']++;
    for (int i = 0; i < str[id2].length(); i++)
    {
        cnt[str[id2][i] - 'A']--;
        if (cnt[str[id2][i] - 'A'] < 0)
            st = str[id2][i];
    }
    for (int i = 0; i < str[id1].length(); i++)
    {
        if (cnt[str[id1][i] - 'A'] > 0)
            pos = i + 1;
    }
    return st;
}
int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <= n; i++)
            cin >> str[i];
        for (int i = 1; i <= n; i++)
        {
            if (judge(i))
            {
                char ans = getans(i, i + 1);
                cout << i << ' ' << pos << ' ' << ans << endl;
                break;
            }
        }
    }
    return 0;
}