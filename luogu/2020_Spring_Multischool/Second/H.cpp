#include <bits/stdc++.h>
using namespace std;
__int128_t a, b, h1, h2;
inline __int128_t read()
{
    __int128_t X = 0;
    int w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch))
        X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}
inline void print(__int128_t x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
    freopen(".in", "r", stdin);
    a = read(), b = read(), h1 = read(), h2 = read();
    print(a * b * h1 - a * b * (h1 - h2) / 2);
    return 0;
}