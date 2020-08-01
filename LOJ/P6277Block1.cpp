#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 7;
int n, opt, l, r, c, block;
ll a[maxn], B[maxn], add[maxn];
int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    scanf("%d", &n);
    block = (int)sqrt(n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d %d %d", &opt, &l, &r, &c);
        if (opt == 0)
        {
            int lblock = l % block == 0 ? (l / block) : (l / block + 1);
            int rblock = r % block == 0 ? (r / block) : (r / block + 1);
            if (lblock == rblock) //特殊情况，防止重复
            {
                for (int i = l; i <= r; i++)
                    a[i] += c;
                continue;
            }
            while (l % block != 1)
                a[l] += (1ll * c), ++l;
            while (r % block != 0)
                a[r] += (1ll * c), --r;
            for (int i = (l / block + 1); i <= r / block; i++)
                B[i] += (1ll * c);
        }
        else
        {
            int tmpblock;
            r % block == 0 ? tmpblock = r / block : tmpblock = r / block + 1;
            for (int i = (tmpblock - 1) * block + 1; i <= tmpblock * block; i++)
                a[i] += B[tmpblock];
            B[tmpblock] = 0;
            printf("%lld\n", a[r]);
        }
    }
    return 0;
}