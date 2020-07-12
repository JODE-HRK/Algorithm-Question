#include <bits/stdc++.h>
using namespace std;
long long n;
char getans(string str)
{
    long long l = str.length();
    long long tmp = str.length();
    while (tmp <= n)
        tmp <<= 1;
    n -= 1;
    while (tmp >= l)
    {
        if (n >= tmp)
        {
            n -= tmp;
            if (!n)
                n = tmp - 1;
            else
                n -= 1;
        }
        tmp >>= 1;
    }
    return str[n];
}
int main()
{
    string s;
    cin >> s >> n;
    cout << getans(s);
    return 0;
}