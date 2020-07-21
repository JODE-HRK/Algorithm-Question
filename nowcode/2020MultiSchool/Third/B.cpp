/*
 * @Descripttion:
 * @version:
 * @Author: JODEHRK
 * @Date: 2020-07-13 21:35:45
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-18 12:51:20
 */
#include <bits/stdc++.h>
#define ll long long
#define inf 0x7fffffff
#define INF 1000000000000ll
#define pii pair<int, int>
#define pll pair<ll, ll>
const int maxn = 1e6 + 7;
using namespace std;
string str;
int main()
{
    cin >> str;
    int len = str.length();
    int q, start = 0, tail = len - 1;
    scanf("%d", &q);
    while (q--)
    {
        char p;
        int x;
        scanf(" %c %d", &p, &x);
        if (p == 'M')
        {
            if (x < 0)
            {
                x = -x;
                start = (tail - x + 1 + len) % len;
                tail = (start - 1 + len) % len;
            }
            else
            {
                start = (start + x) % len;
                tail = (start - 1 + len) % len;
            }
        }
        else
        {
            int pos = (start + x + len - 1) % len;
            printf("%c\n", str[pos]);
        }
    }
    return 0;
}
/*
abscdrek
5
A 4
M 7
A 5
M 2
A 6
*/