#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
char str[26][30] = {{'.', '-'}, {'-', '.', '.', '.'}, {'-', '.', '-', '.'}, {'-', '.', '.'}, {'.'}, {'.', '.', '-', '.'}, {'-', '-', '.'}, {'.', '.', '.', '.'}, {'.', '.'}, {'.', '-', '-', '-'}, {'-', '.', '-'}, {'.', '-', '.', '.'}, {'-', '-'}, {'-', '.'}, {'-', '-', '-'}, {'.', '-', '-', '.'}, {'-', '-', '.', '-'}, {'.', '-', '.'}, {'.', '.', '.'}, {'-'}, {'.', '.', '-'}, {'.', '.', '.', '-'}, {'.', '-', '-'}, {'-', '.', '.', '-'}, {'-', '.', '-', '-'}, {'-', '-', '.', '.'}};
int main()
{
    // freopen(".in", "r", stdout);
    string s;
    string ss;
    char c;
    while (cin >> ss)
    {
        for (int i = 0; i < ss.length(); i++)
        {
            c = ss[i];
            if (c == '.' || c == '-')
                s += c;
            else if (c == '/' || c == '\n')
            {
                if (s.empty())
                    cout << ' ';
                else
                {
                    for (int i = 0; i < 26; i++)
                        if (s == str[i])
                        {
                            cout << char('A' + i);
                            break;
                        }
                    s.clear();
                }
                if (c == '\n')
                    cout << endl;
            }
        }
        if (!s.empty())
        {
            for (int i = 0; i < 26; i++)
                if (s == str[i])
                {
                    cout << char('A' + i);
                    break;
                }
            s.clear();
        }
        cout<<endl;
    }
    return 0;
}