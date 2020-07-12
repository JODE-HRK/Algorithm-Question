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
int n, l1, a1, l2, a2, lt, at;
int main()
{
    scanf("%d", &n);
    while (n--)
    {
        int p = 0, ans1 = 0, ans2 = 0;
        scanf("%d %d %d %d %d %d", &l1, &a1, &l2, &a2, &lt, &at);
        for (int i = 1; i <= min(lt / l1, at / a1); i++)
        {
            int ls1 = l1 * i, as1 = a1 * i;
            if ((lt - ls1) % l2 == 0 && (at - as1) % a2 == 0 && (lt - ls1) / l2 == (at - as1) / a2 && (lt - ls1) / l2 != 0)
                ans1 = i, ans2 = (lt - ls1) / l2, p++;
        }
        if (!p || p > 1)
            cout << "?" << endl;
        else
            cout << ans1 << ' ' << ans2 << endl;
    }
    return 0;
}