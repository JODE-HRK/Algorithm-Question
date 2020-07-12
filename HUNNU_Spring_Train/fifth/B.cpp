#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;
int n, V1, V2;
double W;
ll getC(int n, int m)
{
    ll ans = 1, ans1 = 1;
    for (int i = n, j = m; i > n - m; i--, j--)
    {
        ans *= i;
        if (ans % j == 0)
            ans /= j;
        else
            ans1 *= j;
    }
    return ans / ans1;
}
bool getpro(int lhalf, int last)
{
    double s = 0.0;
    for (int i = lhalf; i <= last; i++)
        s += 1.0 * getC(last, i) * pow(0.5, last);
    if (s > W)
        return 1;
    return 0;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d %d %lf", &n, &V1, &V2, &W);
        int last = n - V1 - V2, lhalf = n / 2 + 1 - V1;
        W /= 100.0;
        if (V1 + last <= V2)
            printf("RECOUNT!\n");
        else if (V1 >= V2 + last)
            printf("GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!\n");
        else
        {
            if (getpro(lhalf, last))
                printf("GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!\n");
            else
                printf("PATIENCE, EVERYONE!\n");
        }
    }
    return 0;
}