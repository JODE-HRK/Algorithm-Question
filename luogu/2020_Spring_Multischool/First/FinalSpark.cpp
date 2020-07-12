#include <bits/stdc++.h>
using namespace std;
int T, w, t, s, d;
double theata;
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d %d %d", &w, &t, &s, &d);
        int wt = w + t;
        int p = wt >= s ? 1 : 0;
        if (wt >= 2 * s)
        {
            printf("1.000000000\n");
            continue;
        }
        if (wt == 0)
        {
            printf("0.000000000\n");
            continue;
        }
        theata = acos((double)(s - wt) / (double)(s)); //
        printf("%.9lf\n", theata / acos(-1));
    }
    return 0;
}