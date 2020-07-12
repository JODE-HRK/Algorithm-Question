#include <bits/stdc++.h>
using namespace std;
stack<int> S;
stack<string> STR;
string str;
string getans(int &pos)
{
    int p = 0;
    string st;
    for (; pos < str.length(); pos++)
    {
        if (str[pos] >= '0' && str[pos] <= '9')
            p = p * 10 + str[pos] - '0';
        else if (str[pos] == '[')
        {
            pos++;
            string ss = getans(pos);
            st += ss;
        }
        else if (str[pos] == ']')
        {
            string sp;
            while (p--)
                sp += st;
            return sp;
        }
        else
            st += str[pos];
    }
    return st;
}
int main()
{
    cin >> str;
    int st = 0;
    string s = getans(st);
    cout << s;
    return 0;
}