#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e3 + 1;
string str;
int sum[maxn], cnt = 0;
bool judge(int l, int r)
{
    if (sum[r] != 0)
        return 0;
    int s = 0;
    for (int i = l - 1; i < r; i++)
    {
        char v = str[i];
        if (v == '(')
            --s;
        else
            ++s;
        if (s < 0)
            return 0;
    }
    return 1;
}
int main()
{
    memset(sum, 0, sizeof(sum));
    cin >> str;
    for (auto v : str)
    {
        ++cnt;
        if (v == '(')
            sum[cnt] = sum[cnt - 1] + 1;
        else
            sum[cnt] = sum[cnt - 1] - 1;
    }
    for (int i = 1; i <= str.length(); i++)
            for (int j = i; j <= str.length(); j++)
                {
                    if (judge(i, j))
                    {
                        cout << "possible";
                        return 0;
                    }
                }
    cout << "impossible";
    return 0;
}