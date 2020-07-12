#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, k;
int T;
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &k);
        if (k == 1)
            printf("%d\n", n - 1);
        else
        {
            ll ans = (ll)n * k;
            if (ans & 1)
                ans = ans / 2 + 1;
            else
                ans = ans / 2;
            printf("%lld\n", ans);
        }
    }
    return 0;
}
