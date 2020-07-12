#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
int t;
uint A, B, C, D, E;
bool yes;
bool check(uint x)
{
    if (((B == 32 ? 0 : (x >> B)) ^ C) + ((D == 32 ? 0 : (x << D)) ^ E) + x != A)
        return 0;
    return 1;
}
void print(uint x)
{
    if (check(x))
        return;
    puts("YES");
    printf("%u\n", x);
    yes = 1;
}
int main()
{
    freopen(".out", "w", stdout);
    scanf("%d", &t);
    while (t--)
    {
        scanf("%u %u %u %u %u", &A, &B, &C, &D, &E);
        if (B == 32 && D == 32)
            print(A - C - E);
        else if (B != 32)
        {
            if (B <= 16)
            {
                uint xmn = ~0u;
                for (uint i = 0; i < (1ll << B); ++i)
                {
                    uint x = i, w = 0, flg = 1;
                    for (int j = 0; j < 32 && flg; ++j)
                    {
                        uint ny = ((x ^ (x >> B) ^ C ^ E ^ (D == 32 ? 0 : x << D) ^ A) >> j & 1) ^ (w & 1);
                        if (j + B >= 32 && ny)
                            flg = 0;
                        if (j + B < 32)
                            x |= ny << j + B;
                        w = ((x >> j & 1) + (((x >> B) ^ C) >> j & 1) + (((D == 32 ? 0 : x << D) ^ E) >> j & 1) + w - (A >> j & 1)) >> 1;
                    }
                    if (flg && check(x))
                    {
                        yes = 1;
                        xmn = min(xmn, x);
                    }
                }
                if (yes)
                {
                    if (xmn == ~0u)
                    {
                        yes = 0;
                        puts("NO");
                        continue;
                    }
                    puts("YES");
                    printf("%u\n", xmn);
                }
            }
            else
            {
                uint xmn = ~0u;
                for (uint i = 0; i < (1ll << 32 - B); ++i)
                {
                    uint x = i << B, w = 0, flg = 1;
                    for (int j = 0; j < 32 && flg; ++j)
                    {
                        uint ny = ((x ^ (x >> B) ^ C ^ E ^ (D == 32 ? 0 : x << D) ^ A) >> j & 1) ^ (w & 1);
                        if (j >= B && ny)
                            flg = 0;
                        if (j < B)
                            x |= ny << j;
                        w = ((x >> j & 1) + (((x >> B) ^ C) >> j & 1) + (((D == 32 ? 0 : x << D) ^ E) >> j & 1) + w - (A >> j & 1)) >> 1;
                    }
                    if (flg && check(x))
                    {
                        yes = 1;
                        xmn = min(xmn, x);
                    }
                }
                if (yes)
                {
                    if (xmn == ~0u)
                    {
                        yes = 0;
                        puts("NO");
                        continue;
                    }
                    puts("YES");
                    printf("%u\n", xmn);
                }
            }
        }
        else if (D != 32)
        {

            uint x = 0, w = 0;
            uint nA = A - C;
            for (uint i = 0; i < 32; ++i)
            {
                uint ny = ((x ^ nA ^ E ^ (x << D)) >> i & 1) ^ (w & 1);
                x |= ny << i;
                w = ((((x << D) ^ E) >> i & 1) + (x >> i & 1) + w - (nA >> i & 1)) >> 1;
            }
            print(x);
        }
        if (!yes)
            puts("NO");
    }
    return 0;
}