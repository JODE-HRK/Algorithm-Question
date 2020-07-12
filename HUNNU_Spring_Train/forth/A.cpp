#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <vector>
#include <ctime>
using namespace std;
int n, t;
string str[30] = {"@", "8", "(", "|)", "3", "#", "6", "[-]",
                  "|", "_|", "|<", "1", "[]\\/[]", "[]\\[]", "0", "|D", "(,)",
                  "|Z", "$", "']['", "|_|", "\\/", "\\/\\/", "}{", "`/", "2"};
int main()
{
    // freopen(".in", "r", stdin);
    // for(int i=0;i<26;i++)
    //     cout<<str[i]<<endl;
    string s;
    getline(cin, s);
    // while (~scanf("%s", s))
    // {
    for (int i = 0; s[i]; i++)
    {
        if (isalpha(s[i]))
        {
            s[i] = tolower(s[i]);
            cout << str[s[i] - 'a'];
        }
        else
            cout << s[i];
    }
    //     cout << " ";
    // }
    return 0;
}