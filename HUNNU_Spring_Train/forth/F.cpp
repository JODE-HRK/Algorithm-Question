#pragma GCC optimize(2)
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
typedef long long ll;
const int mod = 1e9 + 7;
int main()
{
    string str;
    ll z = 0;
    cin >> str;
    for (int i = 0; i < str.length(); i++)
        z = (z * 10 % mod + str[i] - '0') % mod;
    ll sum = 1;
    for (int i = 1; i <= 2000000; i++)
    {
        sum = (sum % mod) * (i % mod) % mod;
        if (sum == z)
        {
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}