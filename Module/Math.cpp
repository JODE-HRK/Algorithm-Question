#include <bits/stdc++.h>
#define ll long long
const int mod = 998244573;
using namespace std;

/*
快速幂
*/
struct POW
{
    ll pow_mod(int base, int power)
    {
        ll ans = 1;
        while (power)
        {
            if (power & 1)
                ans = ans * base % (1ll * mod);
            power >>= 1;
            base = (base * base) % (1ll * mod);
        }
        return ans;
    }
};