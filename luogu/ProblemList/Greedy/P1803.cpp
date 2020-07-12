#include <bits/stdc++.h>
using namespace std;
int n;
struct op
{
    int st, en;
    bool operator<(const op x)
    {
        return en < x.en;
    }
} a[1000001];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &a[i].st, &a[i].en);
    sort(a + 1, a + 1 + n);
    int last = -1, ans = 0;
    for (int i = 1; i <= n; i++)
        if (a[i].st >= last)
        {
            ans++, last = a[i].en;
        }
    printf("%d", ans);
    return 0;
}