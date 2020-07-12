#include <bits/stdc++.h>
using namespace std;
int t;
__int128_t n, m, a, b;
void read(__int128_t &X)
{
    X = 0;
    int w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch))
        X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    if (w)
        X = -X;
}
void print(__int128 x)
{
    if (!x)
        return;
    if (x < 0)
        putchar('-'), x = -x;
    print(x / 10);
    putchar(x % 10 + '0');
}
bool judge()
{
    if (m == 0)
        return 1;
    if (n == 0)
        return 0;
    if (n * b < m)
        return 0;
    if (n * b == m)
        return 1;
    if ((n - 1) * b + b / 2 >= m)
        return 1;
    if ((n * b - m) % (b - a) == 0)
        if ((n * b - m) / (b - a) <= n)
            return 1;
        else
            return 0;
    return 0;
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        read(n), read(m), read(a), read(b);
        if (judge())
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}